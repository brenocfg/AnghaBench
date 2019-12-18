#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ task_handle; int has_reset; struct TYPE_4__* next; } ;
typedef  TYPE_1__ twdt_task_t ;
typedef  scalar_t__ TaskHandle_t ;
struct TYPE_5__ {TYPE_1__* list; } ;

/* Variables and functions */
 TYPE_2__* twdt_config ; 

__attribute__((used)) static twdt_task_t *find_task_in_twdt_list(TaskHandle_t handle, bool *all_reset)
{
    twdt_task_t *target = NULL;
    *all_reset = true;
    for(twdt_task_t *task = twdt_config->list; task != NULL; task = task->next){
        if(task->task_handle == handle){
            target = task;   //Get pointer to target task list member
        }else{
            if(task->has_reset == false){     //If a task has yet to reset
                *all_reset = false;
            }
        }
    }
    return target;
}