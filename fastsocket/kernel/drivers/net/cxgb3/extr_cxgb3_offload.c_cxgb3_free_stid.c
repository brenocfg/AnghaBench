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
union listen_entry {union listen_entry* next; } ;
struct tid_info {int /*<<< orphan*/  stid_lock; int /*<<< orphan*/  stids_in_use; union listen_entry* sfree; } ;
struct t3cdev {int dummy; } ;
struct TYPE_2__ {struct tid_info tid_maps; } ;

/* Variables and functions */
 TYPE_1__* T3C_DATA (struct t3cdev*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 union listen_entry* stid2entry (struct tid_info*,int) ; 

void cxgb3_free_stid(struct t3cdev *tdev, int stid)
{
	struct tid_info *t = &(T3C_DATA(tdev))->tid_maps;
	union listen_entry *p = stid2entry(t, stid);

	spin_lock_bh(&t->stid_lock);
	p->next = t->sfree;
	t->sfree = p;
	t->stids_in_use--;
	spin_unlock_bh(&t->stid_lock);
}