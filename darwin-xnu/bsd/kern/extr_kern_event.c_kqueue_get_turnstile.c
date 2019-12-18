#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct turnstile {int dummy; } ;
struct TYPE_10__ {TYPE_5__* kqwl; TYPE_1__* kq; } ;
typedef  TYPE_3__ kqueue_t ;
struct TYPE_9__ {int kqr_state; } ;
struct TYPE_11__ {int /*<<< orphan*/  kqwl_p; TYPE_2__ kqwl_request; struct turnstile* kqwl_turnstile; } ;
struct TYPE_8__ {int kq_state; } ;

/* Variables and functions */
 int KQR_ALLOCATED_TURNSTILE ; 
 int KQ_WORKLOOP ; 
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  TURNSTILE_WORKLOOPS ; 
 scalar_t__ filt_wlturnstile_interlock_is_workq (TYPE_5__*) ; 
 int /*<<< orphan*/  kq_req_lock (TYPE_3__) ; 
 int /*<<< orphan*/  kq_req_unlock (TYPE_5__*) ; 
 int os_atomic_load (int*,int /*<<< orphan*/ ) ; 
 struct turnstile* os_atomic_load_with_dependency_on (struct turnstile**,int) ; 
 int /*<<< orphan*/  os_atomic_or (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relaxed ; 
 int /*<<< orphan*/  release ; 
 struct turnstile* turnstile_alloc () ; 
 int /*<<< orphan*/  turnstile_deallocate (struct turnstile*) ; 
 struct turnstile* turnstile_prepare (uintptr_t,struct turnstile**,struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_kern_threadreq_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  workq_kern_threadreq_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct turnstile *
kqueue_get_turnstile(kqueue_t kqu, bool can_alloc)
{
	uint8_t kqr_state;

	if ((kqu.kq->kq_state & KQ_WORKLOOP) == 0) {
		return TURNSTILE_NULL;
	}

	kqr_state = os_atomic_load(&kqu.kqwl->kqwl_request.kqr_state, relaxed);
	if (kqr_state & KQR_ALLOCATED_TURNSTILE) {
		/* force a dependency to pair with the atomic or with release below */
		return os_atomic_load_with_dependency_on(&kqu.kqwl->kqwl_turnstile,
				kqr_state);
	}

	if (!can_alloc) {
		return TURNSTILE_NULL;
	}

	struct turnstile *ts = turnstile_alloc(), *free_ts = TURNSTILE_NULL;

	kq_req_lock(kqu);
	if (filt_wlturnstile_interlock_is_workq(kqu.kqwl)) {
		workq_kern_threadreq_lock(kqu.kqwl->kqwl_p);
	}

	if (kqu.kqwl->kqwl_request.kqr_state & KQR_ALLOCATED_TURNSTILE) {
		free_ts = ts;
		ts = kqu.kqwl->kqwl_turnstile;
	} else {
		ts = turnstile_prepare((uintptr_t)kqu.kqwl, &kqu.kqwl->kqwl_turnstile,
				ts, TURNSTILE_WORKLOOPS);

		/* release-barrier to pair with the unlocked load of kqwl_turnstile above */
		os_atomic_or(&kqu.kqwl->kqwl_request.kqr_state,
				KQR_ALLOCATED_TURNSTILE, release);
	}

	if (filt_wlturnstile_interlock_is_workq(kqu.kqwl)) {
		workq_kern_threadreq_unlock(kqu.kqwl->kqwl_p);
	}
	kq_req_unlock(kqu.kqwl);

	if (free_ts) {
		turnstile_deallocate(free_ts);
	}
	return ts;
}