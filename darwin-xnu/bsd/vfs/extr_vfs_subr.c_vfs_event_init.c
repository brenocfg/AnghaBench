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
 int /*<<< orphan*/  fs_klist ; 
 int /*<<< orphan*/  fs_klist_lck_grp ; 
 int /*<<< orphan*/  fs_klist_lock ; 
 int /*<<< orphan*/  klist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_alloc_init (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_alloc_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
vfs_event_init(void)
{

	klist_init(&fs_klist);
	fs_klist_lck_grp = lck_grp_alloc_init("fs_klist", NULL);
	fs_klist_lock = lck_mtx_alloc_init(fs_klist_lck_grp, NULL);
}