//**Task Minder - The Task Management Companion**//
#include <iostream>
#include <string>
#include <limits>

const int MAX_TASKS = 10;

class Task {
public:
    Task() : title(""), description(""), date(""), time(""), completed(false) {}

    void create(const std::string& title, const std::string& description, const std::string& date, const std::string& time) {
        this->title = title;
        this->description = description;
        this->date = date;
        this->time = time;
        completed = false;
    }

    void display() const {
        std::cout << "Title: " << title << std::endl;
        std::cout << "Description: " << description << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << "Time: " << time << std::endl;
        std::cout << "Status: " << (completed ? "Completed" : "Pending") << std::endl;
    }

    void edit(const std::string& title, const std::string& description, const std::string& date, const std::string& time) {
        this->title = title;
        this->description = description;
        this->date = date;
        this->time = time;
    }

    void markAsCompleted() {
        completed = true;
    }

    bool isCompleted() const {
        return completed;
    }

    const std::string& getDate() const {
        return date;
    }

private:
    std::string title;
    std::string description;
    std::string date;
    std::string time;
    bool completed;
};

class TaskScheduler {
public:
    TaskScheduler() : taskCount(0) {
        addDefaultTasks();
    }

    void createTask() {
        if (taskCount < MAX_TASKS) {
            std::string title, description, date, time;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Enter task title: ";
            std::getline(std::cin, title);
            std::cout << "Enter task description: ";
            std::getline(std::cin, description);
            std::cout << "Enter task date: ";
            std::getline(std::cin, date);
            std::cout << "Enter task time (HH:MM AM/PM): ";
            std::getline(std::cin, time);

            if (taskCount < MAX_TASKS) {
                tasks[taskCount].create(title, description, date, time);
                taskCount++;
                std::cout << "Task created successfully!" << std::endl;
            } else {
                std::cout << "Task list is full. Delete some tasks to make space." << std::endl;
            }
        } else {
            std::cout << "Task list is full. Delete some tasks to make space." << std::endl;
        }
    }

    void displayTasks() const {
        std::cout << "Upcoming Tasks:" << std::endl;
        for (int i = 0; i < taskCount; i++) {
            if (!tasks[i].isCompleted()) {
                tasks[i].display();
                std::cout << "------------------------" << std::endl;
            }
        }
    }

    void editTask(const std::string& inputDate) {
        bool found = false;
        for (int i = 0; i < taskCount; i++) {
            if (!tasks[i].isCompleted() && tasks[i].getDate() == inputDate) {
                std::string title, description, time;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter new title: ";
                std::getline(std::cin, title);
                std::cout << "Enter new description: ";
                std::getline(std::cin, description);
                std::cout << "Enter new time (HH:MM AM/PM): ";
                std::getline(std::cin, time);

                tasks[i].edit(title, description, inputDate, time);
                std::cout << "Task edited successfully!" << std::endl;
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "No task found for editing on the specified date." << std::endl;
        }
    }

    void markTaskAsCompleted(const std::string& inputDate) {
        bool found = false;
        for (int i = 0; i < taskCount; i++) {
            if (!tasks[i].isCompleted() && tasks[i].getDate() == inputDate) {
                tasks[i].markAsCompleted();
                std::cout << "Task marked as completed!" << std::endl;
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "No task found for marking as completed on the specified date." << std::endl;
        }
    }

private:
    void addDefaultTasks() {
        Task wakeUpTask;
        wakeUpTask.create("Wake Up", "Time to start your day!", "Daily", "06:00 AM");
        tasks[taskCount++] = wakeUpTask;

        Task exerciseTask;
        exerciseTask.create("Exercise", "Time to get fit!", "Daily", "07:00 PM - 08:00 PM");
        tasks[taskCount++] = exerciseTask;

        Task breakfastTask;
        breakfastTask.create("Breakfast", "Time to have a nutritious meal!", "Daily", "08:00 AM - 08:30 AM");
        tasks[taskCount++] = breakfastTask;

        Task lunchTask;
        lunchTask.create("Lunch", "Time to have a delicious meal!", "Daily", "12:30 PM - 01:00 PM");
        tasks[taskCount++] = lunchTask;

        Task dinnerTask;
        dinnerTask.create("Dinner", "Time to have a satisfying meal!", "Daily", "08:30 PM - 09:00 PM");
        tasks[taskCount++] = dinnerTask;

        Task bedTimeTask;
        bedTimeTask.create("Bed Time", "Time to get a good night's sleep!", "Daily", "10:30 PM");
        tasks[taskCount++] = bedTimeTask;
    }

    Task tasks[MAX_TASKS];
    int taskCount;
};

int main() {
    TaskScheduler scheduler;
    int choice;
    while (true) {
        std::cout << "Task Scheduler Menu:" << std::endl;
        std::cout << "1. Create Task" << std::endl;
        std::cout << "2. Display Tasks" << std::endl;
        std::cout << "3. Edit Task" << std::endl;
        std::cout << "4. Mark Task as Completed" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "------------------------" << std::endl;
        if (choice == 1) {
            scheduler.createTask();
        } else if (choice == 2) {
            scheduler.displayTasks();
        } else if (choice == 3) {
            std::string dateToEdit;
            std::cout << "Enter date of the task to edit: ";
            std::getline(std::cin, dateToEdit);
            scheduler.editTask(dateToEdit);
        } else if (choice == 4) {
            std::string dateToComplete;
            std::cout << "Enter date of the task to mark as completed: ";
            std::getline(std::cin, dateToComplete);
            scheduler.markTaskAsCompleted(dateToComplete);
        } else if (choice == 5) {
            return 0;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }

    return 0;
}
