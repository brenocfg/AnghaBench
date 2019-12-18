#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int has_reset; struct TYPE_5__* next; int /*<<< orphan*/ * task_handle; } ;
typedef  TYPE_1__ twdt_task_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/ * TaskHandle_t ;
struct TYPE_6__ {TYPE_1__* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EXIT_CRIT_RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  esp_register_freertos_idle_hook_for_cpu (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* find_task_in_twdt_list (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  idle_hook_cb ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int portNUM_PROCESSORS ; 
 int /*<<< orphan*/  reset_hw_timer () ; 
 TYPE_2__* twdt_config ; 
 int /*<<< orphan*/  twdt_spinlock ; 
 int /*<<< orphan*/ * xTaskGetCurrentTaskHandle () ; 
 int /*<<< orphan*/ * xTaskGetIdleTaskHandleForCPU (int) ; 

esp_err_t esp_task_wdt_add(TaskHandle_t handle)
{
    portENTER_CRITICAL(&twdt_spinlock);
    //TWDT must already be initialized
    ASSERT_EXIT_CRIT_RETURN((twdt_config != NULL), ESP_ERR_INVALID_STATE);

    twdt_task_t *target_task;
    bool all_reset;
    if (handle == NULL){    //Get handle of current task if none is provided
        handle = xTaskGetCurrentTaskHandle();
    }
    //Check if tasks exists in task list, and if all other tasks have reset
    target_task = find_task_in_twdt_list(handle, &all_reset);
    //task cannot be already subscribed
    ASSERT_EXIT_CRIT_RETURN((target_task == NULL), ESP_ERR_INVALID_ARG);

    //Add target task to TWDT task list
    target_task = calloc(1,sizeof(twdt_task_t));
    ASSERT_EXIT_CRIT_RETURN((target_task != NULL), ESP_ERR_NO_MEM);
    target_task->task_handle = handle;
    target_task->has_reset = true;
    target_task->next = NULL;
    if (twdt_config->list == NULL) {    //Adding to empty list
        twdt_config->list = target_task;
    } else {    //Adding to tail of list
        twdt_task_t *task;
        for (task = twdt_config->list; task->next != NULL; task = task->next){
            ;   //point task to current tail of TWDT task list
        }
        task->next = target_task;
    }

    //If idle task, register the idle hook callback to appropriate core
    for(int i = 0; i < portNUM_PROCESSORS; i++){
        if(handle == xTaskGetIdleTaskHandleForCPU(i)){
            ESP_ERROR_CHECK(esp_register_freertos_idle_hook_for_cpu(idle_hook_cb, i));
            break;
        }
    }

    if(all_reset){     //Reset hardware timer if all other tasks in list have reset in
        reset_hw_timer();
    }

    portEXIT_CRITICAL(&twdt_spinlock);       //Nested critical if Legacy
    return ESP_OK;
}