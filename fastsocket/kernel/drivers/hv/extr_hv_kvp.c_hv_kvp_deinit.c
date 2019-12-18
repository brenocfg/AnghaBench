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
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cn_del_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvp_id ; 
 int /*<<< orphan*/  kvp_sendkey_work ; 
 int /*<<< orphan*/  kvp_work ; 

void hv_kvp_deinit(void)
{
	cn_del_callback(&kvp_id);
	cancel_delayed_work_sync(&kvp_work);
	cancel_work_sync(&kvp_sendkey_work);
}