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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int /*<<< orphan*/  cq_context; int /*<<< orphan*/  (* comp_handler ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
struct ipath_cq {scalar_t__ triggered; TYPE_1__ ibcq; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_complete(unsigned long data)
{
	struct ipath_cq *cq = (struct ipath_cq *)data;

	/*
	 * The completion handler will most likely rearm the notification
	 * and poll for all pending entries.  If a new completion entry
	 * is added while we are in this routine, tasklet_hi_schedule()
	 * won't call us again until we return so we check triggered to
	 * see if we need to call the handler again.
	 */
	for (;;) {
		u8 triggered = cq->triggered;

		cq->ibcq.comp_handler(&cq->ibcq, cq->ibcq.cq_context);

		if (cq->triggered == triggered)
			return;
	}
}