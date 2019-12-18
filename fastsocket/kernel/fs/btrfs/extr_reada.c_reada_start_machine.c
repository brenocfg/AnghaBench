#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  func; } ;
struct reada_machine_work {TYPE_1__ work; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  readahead_workers; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  btrfs_queue_worker (int /*<<< orphan*/ *,TYPE_1__*) ; 
 struct reada_machine_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reada_start_machine_worker ; 

__attribute__((used)) static void reada_start_machine(struct btrfs_fs_info *fs_info)
{
	struct reada_machine_work *rmw;

	rmw = kzalloc(sizeof(*rmw), GFP_NOFS);
	if (!rmw) {
		/* FIXME we cannot handle this properly right now */
		BUG();
	}
	rmw->work.func = reada_start_machine_worker;
	rmw->fs_info = fs_info;

	btrfs_queue_worker(&fs_info->readahead_workers, &rmw->work);
}