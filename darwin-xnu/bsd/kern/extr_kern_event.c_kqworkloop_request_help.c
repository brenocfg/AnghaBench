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
struct kqworkloop {int dummy; } ;
typedef  scalar_t__ kq_index_t ;

/* Variables and functions */
 scalar_t__ KQWL_NBUCKETS ; 
 int /*<<< orphan*/  KQWL_UTQ_UPDATE_WAKEUP_QOS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  kq_req_lock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kq_req_unlock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kqworkloop_update_threads_qos (struct kqworkloop*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
kqworkloop_request_help(struct kqworkloop *kqwl, kq_index_t qos_index)
{
	/* convert to thread qos value */
	assert(qos_index < KQWL_NBUCKETS);

	kq_req_lock(kqwl);
	kqworkloop_update_threads_qos(kqwl, KQWL_UTQ_UPDATE_WAKEUP_QOS, qos_index);
	kq_req_unlock(kqwl);
}