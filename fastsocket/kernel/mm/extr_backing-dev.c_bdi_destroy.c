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
struct bdi_writeback {int /*<<< orphan*/  b_more_io; int /*<<< orphan*/  b_io; int /*<<< orphan*/  b_dirty; } ;
struct TYPE_3__ {int /*<<< orphan*/  b_more_io; int /*<<< orphan*/  b_io; int /*<<< orphan*/  b_dirty; } ;
struct backing_dev_info {int /*<<< orphan*/  completions; int /*<<< orphan*/ * bdi_stat; TYPE_1__ wb; } ;
struct TYPE_4__ {struct bdi_writeback wb; } ;

/* Variables and functions */
 int NR_BDI_STAT_ITEMS ; 
 scalar_t__ bdi_has_dirty_io (struct backing_dev_info*) ; 
 int /*<<< orphan*/  bdi_unregister (struct backing_dev_info*) ; 
 TYPE_2__ default_backing_dev_info ; 
 int /*<<< orphan*/  inode_lock ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prop_local_destroy_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void bdi_destroy(struct backing_dev_info *bdi)
{
	int i;

	/*
	 * Splice our entries to the default_backing_dev_info, if this
	 * bdi disappears
	 */
	if (bdi_has_dirty_io(bdi)) {
		struct bdi_writeback *dst = &default_backing_dev_info.wb;

		spin_lock(&inode_lock);
		list_splice(&bdi->wb.b_dirty, &dst->b_dirty);
		list_splice(&bdi->wb.b_io, &dst->b_io);
		list_splice(&bdi->wb.b_more_io, &dst->b_more_io);
		spin_unlock(&inode_lock);
	}

	bdi_unregister(bdi);

	for (i = 0; i < NR_BDI_STAT_ITEMS; i++)
		percpu_counter_destroy(&bdi->bdi_stat[i]);

	prop_local_destroy_percpu(&bdi->completions);
}