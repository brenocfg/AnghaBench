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
 int /*<<< orphan*/ * spp_task_task_handle ; 
 int /*<<< orphan*/ * spp_task_task_queue ; 
 int /*<<< orphan*/  vQueueDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vTaskDelete (int /*<<< orphan*/ *) ; 

void spp_task_task_shut_down(void)
{
    if (spp_task_task_handle) {
        vTaskDelete(spp_task_task_handle);
        spp_task_task_handle = NULL;
    }
    if (spp_task_task_queue) {
        vQueueDelete(spp_task_task_queue);
        spp_task_task_queue = NULL;
    }
}