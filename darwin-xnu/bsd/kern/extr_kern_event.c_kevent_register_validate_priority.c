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
struct kqueue {int kq_state; } ;
struct knote {int /*<<< orphan*/  kn_qos; } ;
struct kevent_internal_s {int flags; int /*<<< orphan*/  qos; } ;

/* Variables and functions */
 int ERANGE ; 
 int EV_DELETE ; 
 int EV_DISABLE ; 
 int KQ_WORKLOOP ; 
 int /*<<< orphan*/  _pthread_priority_thread_qos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kevent_register_validate_priority(struct kqueue *kq, struct knote *kn,
		struct kevent_internal_s *kev)
{
	/* We don't care about the priority of a disabled or deleted knote */
	if (kev->flags & (EV_DISABLE | EV_DELETE)) {
		return 0;
	}

	if (kq->kq_state & KQ_WORKLOOP) {
		/*
		 * Workloops need valid priorities with a QOS (excluding manager) for
		 * any enabled knote.
		 *
		 * When it is pre-existing, just make sure it has a valid QoS as
		 * kevent_register() will not use the incoming priority (filters who do
		 * have the responsibility to validate it again, see filt_wltouch).
		 *
		 * If the knote is being made, validate the incoming priority.
		 */
		if (!_pthread_priority_thread_qos(kn ? kn->kn_qos : kev->qos)) {
			return ERANGE;
		}
	}

	return 0;
}