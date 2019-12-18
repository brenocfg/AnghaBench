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

/* Variables and functions */
 int /*<<< orphan*/  KQWL_BUCKET_STAYACTIVE ; 
 int /*<<< orphan*/  KQWQ_QOS_MANAGER ; 
 int KQ_WORKLOOP ; 
 int KQ_WORKQ ; 
 int /*<<< orphan*/  kqworkloop_request_help (struct kqworkloop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kqworkq_request_help (struct kqworkq*,int /*<<< orphan*/ ) ; 

void
waitq_set__CALLING_PREPOST_HOOK__(void *kq_hook, void *knote_hook, int qos)
{
#pragma unused(knote_hook, qos)

	struct kqueue *kq = (struct kqueue *)kq_hook;

	if (kq->kq_state & KQ_WORKQ) {
		struct kqworkq *kqwq = (struct kqworkq *)kq;

		kqworkq_request_help(kqwq, KQWQ_QOS_MANAGER);
	} else if (kq->kq_state & KQ_WORKLOOP) {
		struct kqworkloop *kqwl = (struct kqworkloop *)kq;

		kqworkloop_request_help(kqwl, KQWL_BUCKET_STAYACTIVE);
	}
}