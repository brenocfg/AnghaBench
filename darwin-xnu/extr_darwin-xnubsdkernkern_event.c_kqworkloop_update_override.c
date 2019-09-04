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
typedef  int /*<<< orphan*/  kq_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  KQWL_UTQ_UPDATE_WAKEUP_OVERRIDE ; 
 int /*<<< orphan*/  kq_req_lock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kq_req_unlock (struct kqworkloop*) ; 
 int /*<<< orphan*/  kqworkloop_update_threads_qos (struct kqworkloop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kqworkloop_update_override(struct kqworkloop *kqwl, kq_index_t override_index)
{
	kq_req_lock(kqwl);
	kqworkloop_update_threads_qos(kqwl, KQWL_UTQ_UPDATE_WAKEUP_OVERRIDE,
			override_index);
	kq_req_unlock(kqwl);
}