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
typedef  scalar_t__ thread_t ;
struct TYPE_2__ {int /*<<< orphan*/  kqr_suppressed; } ;
struct kqworkloop {scalar_t__ kqwl_owner; TYPE_1__ kqwl_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 scalar_t__ THREAD_NULL ; 
 scalar_t__ THREAD_QOS_UNSPECIFIED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ kqworkloop_owner_override (struct kqworkloop*) ; 
 int /*<<< orphan*/  thread_drop_ipc_override (scalar_t__) ; 
 int /*<<< orphan*/  thread_ends_owning_workloop (scalar_t__) ; 

__attribute__((used)) static thread_t
kqworkloop_invalidate(struct kqworkloop *kqwl)
{
	thread_t cur_owner = kqwl->kqwl_owner;

	assert(TAILQ_EMPTY(&kqwl->kqwl_request.kqr_suppressed));
	if (cur_owner) {
		/*
		 * If the kqueue had an owner that prevented the thread request to
		 * go through, then no unbind happened, and we may have lingering
		 * overrides to drop.
		 */
		if (kqworkloop_owner_override(kqwl) != THREAD_QOS_UNSPECIFIED) {
			thread_drop_ipc_override(cur_owner);
		}
		thread_ends_owning_workloop(cur_owner);
		kqwl->kqwl_owner = THREAD_NULL;
	}

	return cur_owner;
}