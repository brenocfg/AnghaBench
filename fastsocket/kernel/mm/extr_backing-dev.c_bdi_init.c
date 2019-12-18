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
struct backing_dev_info {int max_ratio; int /*<<< orphan*/ * bdi_stat; int /*<<< orphan*/  completions; scalar_t__ dirty_exceeded; int /*<<< orphan*/  wb; int /*<<< orphan*/  work_list; int /*<<< orphan*/  wb_list; int /*<<< orphan*/  bdi_list; int /*<<< orphan*/  rcu_head; int /*<<< orphan*/  wb_lock; int /*<<< orphan*/  max_prop_frac; scalar_t__ min_ratio; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RCU_HEAD (int /*<<< orphan*/ *) ; 
 int NR_BDI_STAT_ITEMS ; 
 int /*<<< orphan*/  PROP_FRAC_BASE ; 
 int /*<<< orphan*/  bdi_wb_init (int /*<<< orphan*/ *,struct backing_dev_info*) ; 
 int /*<<< orphan*/  percpu_counter_destroy (int /*<<< orphan*/ *) ; 
 int percpu_counter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int prop_local_init_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int bdi_init(struct backing_dev_info *bdi)
{
	int i, err;

	bdi->dev = NULL;

	bdi->min_ratio = 0;
	bdi->max_ratio = 100;
	bdi->max_prop_frac = PROP_FRAC_BASE;
	spin_lock_init(&bdi->wb_lock);
	INIT_RCU_HEAD(&bdi->rcu_head);
	INIT_LIST_HEAD(&bdi->bdi_list);
	INIT_LIST_HEAD(&bdi->wb_list);
	INIT_LIST_HEAD(&bdi->work_list);

	bdi_wb_init(&bdi->wb, bdi);

	for (i = 0; i < NR_BDI_STAT_ITEMS; i++) {
		err = percpu_counter_init(&bdi->bdi_stat[i], 0);
		if (err)
			goto err;
	}

	bdi->dirty_exceeded = 0;
	err = prop_local_init_percpu(&bdi->completions);

	if (err) {
err:
		while (i--)
			percpu_counter_destroy(&bdi->bdi_stat[i]);
	}

	return err;
}