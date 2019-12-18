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
typedef  size_t uint16_t ;
struct dlm_ls {TYPE_1__* ls_lkbtbl; } ;
struct dlm_lkb {int lkb_id; scalar_t__ lkb_lvbptr; int /*<<< orphan*/  lkb_idtbl_list; int /*<<< orphan*/  lkb_ref; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  detach_lkb (struct dlm_lkb*) ; 
 int /*<<< orphan*/  dlm_free_lkb (struct dlm_lkb*) ; 
 int /*<<< orphan*/  dlm_free_lvb (scalar_t__) ; 
 scalar_t__ is_master_copy (struct dlm_lkb*) ; 
 int /*<<< orphan*/  kill_lkb ; 
 scalar_t__ kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __put_lkb(struct dlm_ls *ls, struct dlm_lkb *lkb)
{
	uint16_t bucket = (lkb->lkb_id >> 16);

	write_lock(&ls->ls_lkbtbl[bucket].lock);
	if (kref_put(&lkb->lkb_ref, kill_lkb)) {
		list_del(&lkb->lkb_idtbl_list);
		write_unlock(&ls->ls_lkbtbl[bucket].lock);

		detach_lkb(lkb);

		/* for local/process lkbs, lvbptr points to caller's lksb */
		if (lkb->lkb_lvbptr && is_master_copy(lkb))
			dlm_free_lvb(lkb->lkb_lvbptr);
		dlm_free_lkb(lkb);
		return 1;
	} else {
		write_unlock(&ls->ls_lkbtbl[bucket].lock);
		return 0;
	}
}