#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * rootdir; int /*<<< orphan*/ * fw_statistics; } ;
struct TYPE_3__ {int /*<<< orphan*/ * fw_stats; } ;
struct wl1251 {TYPE_2__ debugfs; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1251_debugfs_delete_files (struct wl1251*) ; 

void wl1251_debugfs_exit(struct wl1251 *wl)
{
	wl1251_debugfs_delete_files(wl);

	kfree(wl->stats.fw_stats);
	wl->stats.fw_stats = NULL;

	debugfs_remove(wl->debugfs.fw_statistics);
	wl->debugfs.fw_statistics = NULL;

	debugfs_remove(wl->debugfs.rootdir);
	wl->debugfs.rootdir = NULL;

}