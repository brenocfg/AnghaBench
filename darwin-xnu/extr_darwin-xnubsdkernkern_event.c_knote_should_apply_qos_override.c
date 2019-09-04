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
typedef  scalar_t__ thread_qos_t ;
struct kqueue {int kq_state; } ;
struct knote {scalar_t__ kn_req_index; int kn_qos; int kn_status; scalar_t__ kn_qos_override; scalar_t__ kn_inuse; int /*<<< orphan*/  kn_filtid; } ;
struct TYPE_2__ {int /*<<< orphan*/  f_adjusts_qos; } ;

/* Variables and functions */
 int FILTER_ADJUST_EVENT_QOS_BIT ; 
 int FILTER_ADJUST_EVENT_QOS_SHIFT ; 
 int KN_LOCKED ; 
 int KN_MERGE_QOS ; 
 scalar_t__ KQWL_BUCKET_STAYACTIVE ; 
 scalar_t__ KQWQ_QOS_MANAGER ; 
 int KQ_WORKLOOP ; 
 int KQ_WORKQ ; 
 scalar_t__ THREAD_QOS_LAST ; 
 scalar_t__ THREAD_QOS_UNSPECIFIED ; 
 int _PTHREAD_PRIORITY_FALLBACK_FLAG ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* knote_fops (struct knote*) ; 
 int /*<<< orphan*/  kqlock_held (struct kqueue*) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
knote_should_apply_qos_override(struct kqueue *kq, struct knote *kn, int result,
		thread_qos_t *qos_out)
{
	thread_qos_t qos_index = (result >> FILTER_ADJUST_EVENT_QOS_SHIFT) & 7;

	kqlock_held(kq);

	assert(result & FILTER_ADJUST_EVENT_QOS_BIT);
	assert(qos_index < THREAD_QOS_LAST);

	/*
	 * Early exit for knotes that should not change QoS
	 *
	 * It is safe to test kn_req_index against MANAGER / STAYACTIVE because
	 * knotes with such kn_req_index values never change for their entire
	 * lifetime.
	 */
	if (__improbable(!knote_fops(kn)->f_adjusts_qos)) {
		panic("filter %d cannot change QoS", kn->kn_filtid);
	} else if (kq->kq_state & KQ_WORKLOOP) {
		if (kn->kn_req_index == KQWL_BUCKET_STAYACTIVE) {
			return false;
		}
	} else if (kq->kq_state & KQ_WORKQ) {
		if (kn->kn_req_index == KQWQ_QOS_MANAGER) {
			return false;
		}
	} else {
		return false;
	}

	/*
	 * knotes with the FALLBACK flag will only use their registration QoS if the
	 * incoming event has no QoS, else, the registration QoS acts as a floor.
	 */
	if (kn->kn_qos & _PTHREAD_PRIORITY_FALLBACK_FLAG) {
		if (qos_index == THREAD_QOS_UNSPECIFIED)
			qos_index = kn->kn_req_index;
	} else {
		if (qos_index < kn->kn_req_index)
			qos_index = kn->kn_req_index;
	}
	if ((kn->kn_status & KN_MERGE_QOS) && (qos_index < kn->kn_qos_override)) {
		/* Never lower QoS when in "Merge" mode */
		return false;
	}

	if ((kn->kn_status & KN_LOCKED) && kn->kn_inuse) {
		/*
		 * When we're trying to update the QoS override and that both an
		 * f_event() and other f_* calls are running concurrently, any of these
		 * in flight calls may want to perform overrides that aren't properly
		 * serialized with each other.
		 *
		 * The first update that observes this racy situation enters a "Merge"
		 * mode which causes subsequent override requests to saturate the
		 * override instead of replacing its value.
		 *
		 * This mode is left when knote_unlock() or knote_call_filter_event()
		 * observe that no other f_* routine is in flight.
		 */
		kn->kn_status |= KN_MERGE_QOS;
	}

	if (kn->kn_qos_override == qos_index) {
		return false;
	}

	*qos_out = qos_index;
	return true;
}