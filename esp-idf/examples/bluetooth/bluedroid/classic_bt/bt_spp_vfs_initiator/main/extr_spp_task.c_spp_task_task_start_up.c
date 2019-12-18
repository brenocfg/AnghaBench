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
typedef  int /*<<< orphan*/  spp_task_msg_t ;

/* Variables and functions */
 int /*<<< orphan*/  spp_task_task_handle ; 
 int /*<<< orphan*/  spp_task_task_handler ; 
 int /*<<< orphan*/  spp_task_task_queue ; 
 int /*<<< orphan*/  xQueueCreate (int,int) ; 
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void spp_task_task_start_up(void)
{
    spp_task_task_queue = xQueueCreate(10, sizeof(spp_task_msg_t));
    xTaskCreate(spp_task_task_handler, "SPPAppT", 2048, NULL, 10, &spp_task_task_handle);
    return;
}