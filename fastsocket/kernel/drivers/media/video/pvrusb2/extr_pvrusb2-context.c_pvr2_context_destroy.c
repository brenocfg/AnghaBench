#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pvr2_context {TYPE_2__* exist_next; TYPE_1__* exist_prev; scalar_t__ hdw; } ;
struct TYPE_4__ {TYPE_1__* exist_prev; } ;
struct TYPE_3__ {TYPE_2__* exist_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_CTXT ; 
 int /*<<< orphan*/  kfree (struct pvr2_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* pvr2_context_exist_first ; 
 TYPE_1__* pvr2_context_exist_last ; 
 int /*<<< orphan*/  pvr2_context_mutex ; 
 int /*<<< orphan*/  pvr2_context_set_notify (struct pvr2_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvr2_context_sync_data ; 
 int /*<<< orphan*/  pvr2_hdw_destroy (scalar_t__) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,struct pvr2_context*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pvr2_context_destroy(struct pvr2_context *mp)
{
	pvr2_trace(PVR2_TRACE_CTXT,"pvr2_context %p (destroy)",mp);
	if (mp->hdw) pvr2_hdw_destroy(mp->hdw);
	pvr2_context_set_notify(mp, 0);
	mutex_lock(&pvr2_context_mutex);
	if (mp->exist_next) {
		mp->exist_next->exist_prev = mp->exist_prev;
	} else {
		pvr2_context_exist_last = mp->exist_prev;
	}
	if (mp->exist_prev) {
		mp->exist_prev->exist_next = mp->exist_next;
	} else {
		pvr2_context_exist_first = mp->exist_next;
	}
	if (!pvr2_context_exist_first) {
		/* Trigger wakeup on control thread in case it is waiting
		   for an exit condition. */
		wake_up(&pvr2_context_sync_data);
	}
	mutex_unlock(&pvr2_context_mutex);
	kfree(mp);
}