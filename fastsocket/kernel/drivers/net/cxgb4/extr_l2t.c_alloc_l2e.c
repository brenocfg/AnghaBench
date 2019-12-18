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
struct l2t_entry {scalar_t__ state; size_t hash; struct l2t_entry* next; struct l2t_entry* first; int /*<<< orphan*/  refcnt; } ;
struct l2t_data {struct l2t_entry* l2tab; int /*<<< orphan*/  nfree; struct l2t_entry* rover; } ;

/* Variables and functions */
 size_t L2T_SIZE ; 
 scalar_t__ L2T_STATE_SWITCHING ; 
 scalar_t__ L2T_STATE_UNUSED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct l2t_entry *alloc_l2e(struct l2t_data *d)
{
	struct l2t_entry *end, *e, **p;

	if (!atomic_read(&d->nfree))
		return NULL;

	/* there's definitely a free entry */
	for (e = d->rover, end = &d->l2tab[L2T_SIZE]; e != end; ++e)
		if (atomic_read(&e->refcnt) == 0)
			goto found;

	for (e = d->l2tab; atomic_read(&e->refcnt); ++e)
		;
found:
	d->rover = e + 1;
	atomic_dec(&d->nfree);

	/*
	 * The entry we found may be an inactive entry that is
	 * presently in the hash table.  We need to remove it.
	 */
	if (e->state < L2T_STATE_SWITCHING)
		for (p = &d->l2tab[e->hash].first; *p; p = &(*p)->next)
			if (*p == e) {
				*p = e->next;
				e->next = NULL;
				break;
			}

	e->state = L2T_STATE_UNUSED;
	return e;
}