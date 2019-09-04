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
struct kqworkq {int dummy; } ;
struct kqworkloop {int dummy; } ;
struct kqueue {int kq_state; } ;
struct knote {int kn_status; void* kn_qos_index; void* kn_qos_override; } ;
typedef  void* kq_index_t ;

/* Variables and functions */
 int KN_QUEUED ; 
 int KN_SUPPRESSED ; 
 int KQ_WORKQ ; 
 int /*<<< orphan*/  assert (int) ; 
 struct kqueue* knote_get_kq (struct knote*) ; 
 int /*<<< orphan*/  kqworkloop_update_override (struct kqworkloop*,void*) ; 
 int /*<<< orphan*/  kqworkq_update_override (struct kqworkq*,struct knote*,void*) ; 

__attribute__((used)) static void
knote_apply_qos_override(struct knote *kn, kq_index_t qos_index)
{
	assert((kn->kn_status & KN_QUEUED) == 0);

	kn->kn_qos_override = qos_index;

	if (kn->kn_status & KN_SUPPRESSED) {
		struct kqueue *kq = knote_get_kq(kn);
		/*
		 * For suppressed events, the kn_qos_index field cannot be touched as it
		 * allows us to know on which supress queue the knote is for a kqworkq.
		 *
		 * Also, there's no natural push applied on the kqueues when this field
		 * changes anyway. We hence need to apply manual overrides in this case,
		 * which will be cleared when the events are later acknowledged.
		 */
		if (kq->kq_state & KQ_WORKQ) {
			kqworkq_update_override((struct kqworkq *)kq, kn, qos_index);
		} else {
			kqworkloop_update_override((struct kqworkloop *)kq, qos_index);
		}
	} else {
		kn->kn_qos_index = qos_index;
	}
}