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
struct TYPE_5__ {int has_reset; struct TYPE_5__* next; int /*<<< orphan*/  task_handle; } ;
typedef  TYPE_1__ twdt_task_t ;
typedef  int /*<<< orphan*/  TaskHandle_t ;
struct TYPE_6__ {TYPE_1__* list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_EXIT_CRIT_RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_RETURN ; 
 TYPE_1__* calloc (int,int) ; 
 TYPE_1__* find_task_in_twdt_list (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reset_hw_timer () ; 
 TYPE_2__* twdt_config ; 
 int /*<<< orphan*/  twdt_spinlock ; 
 int /*<<< orphan*/  xTaskGetCurrentTaskHandle () ; 

void esp_task_wdt_feed(void)
{
    portENTER_CRITICAL(&twdt_spinlock);
    //Return immediately if TWDT has not been initialized
    ASSERT_EXIT_CRIT_RETURN((twdt_config != NULL), VOID_RETURN);

    //Check if task is on list
    TaskHandle_t handle = xTaskGetCurrentTaskHandle();
    bool all_reset;
    twdt_task_t *target_task = find_task_in_twdt_list(handle, &all_reset);

    //reset the task if it's on the list, then return
    if(target_task != NULL){
        target_task->has_reset = true;
        if(all_reset){
            reset_hw_timer();       //Reset hardware timer if all other tasks have reset
        }
        portEXIT_CRITICAL(&twdt_spinlock);
        return;
    }

    //Add task if it's has not on list
    target_task = calloc(1, sizeof(twdt_task_t));
    ASSERT_EXIT_CRIT_RETURN((target_task != NULL), VOID_RETURN);   //If calloc failed
    target_task->task_handle = handle;
    target_task->has_reset = true;
    target_task->next = NULL;

    if (twdt_config->list == NULL) {    //Adding to empty list
        twdt_config->list = target_task;
    } else {    //Adding to tail of list
        twdt_task_t *task;
        for (task = twdt_config->list; task->next != NULL; task = task->next){
            ;   //point task to current tail of wdt task list
        }
        task->next = target_task;
    }

    portEXIT_CRITICAL(&twdt_spinlock);
}