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
typedef  int /*<<< orphan*/  spp_wr_task_cb_t ;

/* Variables and functions */
 int /*<<< orphan*/  xTaskCreate (int /*<<< orphan*/ ,char*,int,void*,int,int /*<<< orphan*/ *) ; 

void spp_wr_task_start_up(spp_wr_task_cb_t p_cback, int fd)
{
    xTaskCreate(p_cback, "write_read", 2048, (void *)fd, 5, NULL);
}