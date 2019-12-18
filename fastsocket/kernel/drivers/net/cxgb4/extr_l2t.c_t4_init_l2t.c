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
struct l2t_data {TYPE_1__* l2tab; int /*<<< orphan*/  lock; int /*<<< orphan*/  nfree; TYPE_1__* rover; } ;
struct TYPE_2__ {int idx; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int L2T_SIZE ; 
 int /*<<< orphan*/  L2T_STATE_UNUSED ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct l2t_data* t4_alloc_mem (int) ; 

struct l2t_data *t4_init_l2t(void)
{
	int i;
	struct l2t_data *d;

	d = t4_alloc_mem(sizeof(*d));
	if (!d)
		return NULL;

	d->rover = d->l2tab;
	atomic_set(&d->nfree, L2T_SIZE);
	rwlock_init(&d->lock);

	for (i = 0; i < L2T_SIZE; ++i) {
		d->l2tab[i].idx = i;
		d->l2tab[i].state = L2T_STATE_UNUSED;
		spin_lock_init(&d->l2tab[i].lock);
		atomic_set(&d->l2tab[i].refcnt, 0);
	}
	return d;
}