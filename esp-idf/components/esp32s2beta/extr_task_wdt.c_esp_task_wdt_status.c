#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * task_handle; struct TYPE_3__* next; } ;
typedef  TYPE_1__ twdt_task_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/ * TaskHandle_t ;
struct TYPE_4__ {TYPE_1__* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EXIT_CRIT_RETURN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NOT_FOUND ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 TYPE_2__* twdt_config ; 
 int /*<<< orphan*/  twdt_spinlock ; 
 int /*<<< orphan*/ * xTaskGetCurrentTaskHandle () ; 

esp_err_t esp_task_wdt_status(TaskHandle_t handle)
{
    if(handle == NULL){
        handle = xTaskGetCurrentTaskHandle();
    }

    portENTER_CRITICAL(&twdt_spinlock);
    //Return if TWDT is not initialized
    ASSERT_EXIT_CRIT_RETURN((twdt_config != NULL), ESP_ERR_INVALID_STATE);

    twdt_task_t *task;
    for(task = twdt_config->list; task!=NULL; task=task->next){
        //Return ESP_OK if task is found
        ASSERT_EXIT_CRIT_RETURN((task->task_handle != handle), ESP_OK);
    }

    //Task could not be found
    portEXIT_CRITICAL(&twdt_spinlock);
    return ESP_ERR_NOT_FOUND;
}