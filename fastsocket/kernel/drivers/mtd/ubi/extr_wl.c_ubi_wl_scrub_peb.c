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
struct TYPE_2__ {int /*<<< orphan*/  rb; } ;
struct ubi_wl_entry {int /*<<< orphan*/  pnum; TYPE_1__ u; } ;
struct ubi_device {int /*<<< orphan*/  wl_lock; int /*<<< orphan*/  scrub; int /*<<< orphan*/  used; struct ubi_wl_entry* move_to; struct ubi_wl_entry* move_from; struct ubi_wl_entry** lookuptbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_msg (char*,int) ; 
 int /*<<< orphan*/  dbg_wl (char*,int) ; 
 int ensure_wear_leveling (struct ubi_device*) ; 
 scalar_t__ in_wl_tree (struct ubi_wl_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  paranoid_check_in_wl_tree (struct ubi_wl_entry*,int /*<<< orphan*/ *) ; 
 int prot_queue_del (struct ubi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_err (char*,int) ; 
 int /*<<< orphan*/  ubi_ro_mode (struct ubi_device*) ; 
 int /*<<< orphan*/  wl_tree_add (struct ubi_wl_entry*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yield () ; 

int ubi_wl_scrub_peb(struct ubi_device *ubi, int pnum)
{
	struct ubi_wl_entry *e;

	dbg_msg("schedule PEB %d for scrubbing", pnum);

retry:
	spin_lock(&ubi->wl_lock);
	e = ubi->lookuptbl[pnum];
	if (e == ubi->move_from || in_wl_tree(e, &ubi->scrub)) {
		spin_unlock(&ubi->wl_lock);
		return 0;
	}

	if (e == ubi->move_to) {
		/*
		 * This physical eraseblock was used to move data to. The data
		 * was moved but the PEB was not yet inserted to the proper
		 * tree. We should just wait a little and let the WL worker
		 * proceed.
		 */
		spin_unlock(&ubi->wl_lock);
		dbg_wl("the PEB %d is not in proper tree, retry", pnum);
		yield();
		goto retry;
	}

	if (in_wl_tree(e, &ubi->used)) {
		paranoid_check_in_wl_tree(e, &ubi->used);
		rb_erase(&e->u.rb, &ubi->used);
	} else {
		int err;

		err = prot_queue_del(ubi, e->pnum);
		if (err) {
			ubi_err("PEB %d not found", pnum);
			ubi_ro_mode(ubi);
			spin_unlock(&ubi->wl_lock);
			return err;
		}
	}

	wl_tree_add(e, &ubi->scrub);
	spin_unlock(&ubi->wl_lock);

	/*
	 * Technically scrubbing is the same as wear-leveling, so it is done
	 * by the WL worker.
	 */
	return ensure_wear_leveling(ubi);
}