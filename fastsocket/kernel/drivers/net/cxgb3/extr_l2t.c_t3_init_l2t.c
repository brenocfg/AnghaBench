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
struct l2t_entry {int dummy; } ;
struct l2t_data {unsigned int nentries; TYPE_1__* l2tab; int /*<<< orphan*/  lock; int /*<<< orphan*/  nfree; TYPE_1__* rover; } ;
struct TYPE_2__ {int idx; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  arpq; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2T_STATE_UNUSED ; 
 int /*<<< orphan*/  __skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,unsigned int) ; 
 struct l2t_data* cxgb_alloc_mem (int) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct l2t_data *t3_init_l2t(unsigned int l2t_capacity)
{
	struct l2t_data *d;
	int i, size = sizeof(*d) + l2t_capacity * sizeof(struct l2t_entry);

	d = cxgb_alloc_mem(size);
	if (!d)
		return NULL;

	d->nentries = l2t_capacity;
	d->rover = &d->l2tab[1];	/* entry 0 is not used */
	atomic_set(&d->nfree, l2t_capacity - 1);
	rwlock_init(&d->lock);

	for (i = 0; i < l2t_capacity; ++i) {
		d->l2tab[i].idx = i;
		d->l2tab[i].state = L2T_STATE_UNUSED;
		__skb_queue_head_init(&d->l2tab[i].arpq);
		spin_lock_init(&d->l2tab[i].lock);
		atomic_set(&d->l2tab[i].refcnt, 0);
	}
	return d;
}