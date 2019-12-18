#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int has_reset; } ;
typedef  TYPE_1__ twdt_task_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  TaskHandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EXIT_CRIT_RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_1__* find_task_in_twdt_list (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_hw_timer () ; 
 int /*<<< orphan*/ * twdt_config ; 
 int /*<<< orphan*/  twdt_spinlock ; 
 int /*<<< orphan*/  xTaskGetCurrentTaskHandle () ; 

esp_err_t esp_task_wdt_reset(void)
{
    portENTER_CRITICAL(&twdt_spinlock);
    //TWDT must already be initialized
    ASSERT_EXIT_CRIT_RETURN((twdt_config != NULL), ESP_ERR_INVALID_STATE);

    TaskHandle_t handle = xTaskGetCurrentTaskHandle();
    twdt_task_t *target_task;
    bool all_reset;

    //Check if task exists in task list, and if all other tasks have reset
    target_task = find_task_in_twdt_list(handle, &all_reset);
    //Return error if trying to reset task that is not on the task list
    ASSERT_EXIT_CRIT_RETURN((target_task != NULL), ESP_ERR_NOT_FOUND);

    target_task->has_reset = true;    //Reset the task if it's on the task list
    if(all_reset){     //Reset if all other tasks in list have reset in
        reset_hw_timer();
    }

    portEXIT_CRITICAL(&twdt_spinlock);
    return ESP_OK;
}