#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  taskYIELD () ; 
 size_t tskIDLE_PRIORITY ; 
 size_t uxTaskPriorityGet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskPrioritySet (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void yield_to_all_priorities(void)
{
    // Lower the test-task priority before testing to ensure other tasks got executed on forced context switch
    size_t test_task_prio_before = uxTaskPriorityGet(NULL);
    vTaskPrioritySet(NULL, tskIDLE_PRIORITY);
    taskYIELD(); // Let the RTOS to switch context
    vTaskPrioritySet(NULL, test_task_prio_before);
}