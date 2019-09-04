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
typedef  int /*<<< orphan*/  turnstile_update_flags_t ;
typedef  int /*<<< orphan*/  turnstile_inheritor_t ;
struct turnstile {int dummy; } ;
struct kqrequest {int /*<<< orphan*/  kqr_thread; } ;
struct kqworkloop {int /*<<< orphan*/  kqwl_owner; struct kqrequest kqwl_request; } ;

/* Variables and functions */
 int /*<<< orphan*/  TURNSTILE_INHERITOR_NULL ; 
 int /*<<< orphan*/  TURNSTILE_INHERITOR_THREAD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  filt_wlturnstile_interlock_is_workq (struct kqworkloop*) ; 
 int /*<<< orphan*/  turnstile_update_inheritor (struct turnstile*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
filt_wlupdate_inheritor(struct kqworkloop *kqwl, struct turnstile *ts,
		turnstile_update_flags_t flags)
{
	turnstile_inheritor_t inheritor = TURNSTILE_INHERITOR_NULL;
	struct kqrequest *kqr = &kqwl->kqwl_request;

	/*
	 * binding to the workq should always happen through
	 * workq_kern_threadreq_update_inheritor()
	 */
	assert(!filt_wlturnstile_interlock_is_workq(kqwl));

	if ((inheritor = kqwl->kqwl_owner)) {
		flags |= TURNSTILE_INHERITOR_THREAD;
	} else if ((inheritor = kqr->kqr_thread)) {
		flags |= TURNSTILE_INHERITOR_THREAD;
	}

	turnstile_update_inheritor(ts, inheritor, flags);
}