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
typedef  scalar_t__ waitq_lock_state_t ;
typedef  scalar_t__ uint64_t ;
struct waitq_set {int /*<<< orphan*/  wqset_id; } ;
struct waitq_link {int dummy; } ;
struct waitq {int dummy; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_NO_SPACE ; 
 scalar_t__ VM_KERNEL_UNSLIDE_OR_PERM (struct waitq*) ; 
 scalar_t__ WAITQ_SHOULD_LOCK ; 
 int /*<<< orphan*/  WQL_LINK ; 
 int /*<<< orphan*/  panic (char*,struct waitq*) ; 
 scalar_t__ waitq_irq_safe (struct waitq*) ; 
 int /*<<< orphan*/  waitq_link_internal (struct waitq*,int /*<<< orphan*/ ,struct waitq_link*) ; 
 int /*<<< orphan*/  waitq_lock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_set_lazy_init_link (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_unlock (struct waitq*) ; 
 int /*<<< orphan*/  waitq_valid (struct waitq*) ; 
 int /*<<< orphan*/  waitqs_is_linked (struct waitq_set*) ; 
 int /*<<< orphan*/  waitqs_is_set (struct waitq_set*) ; 
 int /*<<< orphan*/  wqdbg_v (char*,void*,int /*<<< orphan*/ ) ; 
 struct waitq_link* wql_alloc_link (int /*<<< orphan*/ ) ; 
 struct waitq_link* wql_get_reserved (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wql_put_link (struct waitq_link*) ; 

kern_return_t waitq_link(struct waitq *waitq, struct waitq_set *wqset,
			 waitq_lock_state_t lock_state, uint64_t *reserved_link)
{
	kern_return_t kr;
	struct waitq_link *link;
	int should_lock = (lock_state == WAITQ_SHOULD_LOCK);

	if (!waitq_valid(waitq) || waitq_irq_safe(waitq))
		panic("Invalid waitq: %p", waitq);

	if (!waitqs_is_set(wqset))
		return KERN_INVALID_ARGUMENT;

	if (!reserved_link || *reserved_link == 0) {
		if (!waitqs_is_linked(wqset)) {
			waitq_set_lazy_init_link(wqset);
		}
	}

	wqdbg_v("Link waitq %p to wqset 0x%llx",
		(void *)VM_KERNEL_UNSLIDE_OR_PERM(waitq), wqset->wqset_id);

	/*
	 * We _might_ need a new link object here, so we'll grab outside
	 * the lock because the alloc call _might_ block.
	 *
	 * If the caller reserved a link beforehand, then wql_get_link
	 * is guaranteed not to block because the caller holds an extra
	 * reference to the link which, in turn, hold a reference to the
	 * link table.
	 */
	if (reserved_link && *reserved_link != 0) {
		link = wql_get_reserved(*reserved_link, WQL_LINK);
		/* always consume the caller's reference */
		*reserved_link = 0;
	} else {
		link = wql_alloc_link(WQL_LINK);
	}
	if (!link)
		return KERN_NO_SPACE;

	if (should_lock) {
		waitq_lock(waitq);
	}

	kr = waitq_link_internal(waitq, wqset->wqset_id, link);

	if (should_lock) {
		waitq_unlock(waitq);
	}

	wql_put_link(link);

	return kr;
}