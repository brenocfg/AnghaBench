#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* workq_threadreq_t ;
typedef  int /*<<< orphan*/  proc_t ;
struct TYPE_5__ {int tr_flags; int /*<<< orphan*/  tr_state; } ;

/* Variables and functions */
 int TR_FLAG_KEVENT ; 
 int TR_FLAG_WORKLOOP ; 
 int /*<<< orphan*/  TR_STATE_IDLE ; 
 int /*<<< orphan*/  kqueue_threadreq_cancel (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  workq_zone_threadreq ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
workq_threadreq_destroy(proc_t p, workq_threadreq_t req)
{
	req->tr_state = TR_STATE_IDLE;
	if (req->tr_flags & (TR_FLAG_WORKLOOP | TR_FLAG_KEVENT)) {
		kqueue_threadreq_cancel(p, req);
	} else {
		zfree(workq_zone_threadreq, req);
	}
}