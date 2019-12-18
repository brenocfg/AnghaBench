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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  waitq_prepost; } ;
struct waitq_set {TYPE_1__ wqset_q; scalar_t__ wqset_prepost_id; int /*<<< orphan*/  wqset_id; } ;
typedef  int /*<<< orphan*/  spl_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 scalar_t__ waitq_irq_safe (TYPE_1__*) ; 
 int /*<<< orphan*/  waitq_set_lock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitq_set_unlock (struct waitq_set*) ; 
 int /*<<< orphan*/  waitqs_is_set (struct waitq_set*) ; 
 int /*<<< orphan*/  wq_prepost_iterate (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wqdbg_v (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wqset_clear_prepost_chain_cb ; 

void waitq_set_clear_preposts(struct waitq_set *wqset)
{
	uint64_t prepost_id;
	spl_t spl;

	assert(waitqs_is_set(wqset));

	if (!wqset->wqset_q.waitq_prepost || !wqset->wqset_prepost_id)
		return;

	wqdbg_v("Clearing all preposted queues on waitq_set: 0x%llx",
		wqset->wqset_id);

	if (waitq_irq_safe(&wqset->wqset_q))
		spl = splsched();
	waitq_set_lock(wqset);
	prepost_id = wqset->wqset_prepost_id;
	wqset->wqset_prepost_id = 0;
	waitq_set_unlock(wqset);
	if (waitq_irq_safe(&wqset->wqset_q))
		splx(spl);

	/* drop / unlink all the prepost table objects */
	if (prepost_id)
		(void)wq_prepost_iterate(prepost_id, NULL,
					 wqset_clear_prepost_chain_cb);
}