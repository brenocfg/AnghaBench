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
 int /*<<< orphan*/  kset_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog_sys_shutdown () ; 
 int /*<<< orphan*/  o2cb_kset ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 

void o2cb_sys_shutdown(void)
{
	mlog_sys_shutdown();
	sysfs_remove_link(NULL, "o2cb");
	kset_unregister(o2cb_kset);
}