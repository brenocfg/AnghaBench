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
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cn_del_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vss_id ; 
 int /*<<< orphan*/  vss_send_op_work ; 

void hv_vss_deinit(void)
{
	cn_del_callback(&vss_id);
	cancel_work_sync(&vss_send_op_work);
}