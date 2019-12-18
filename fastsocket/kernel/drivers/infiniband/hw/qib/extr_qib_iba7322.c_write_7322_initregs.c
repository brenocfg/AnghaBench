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
typedef  unsigned int u64 ;
struct qib_pportdata {unsigned int hw_pidx; int /*<<< orphan*/  p_rcvctrl; int /*<<< orphan*/  link_speed_supported; } ;
struct qib_devdata {int num_pports; int n_krcv_queues; unsigned int first_user_ctxt; int cfgctxts; struct qib_pportdata* pport; TYPE_1__* cspec; } ;
struct TYPE_2__ {int* rcvavail_timeout; int /*<<< orphan*/  rcvmod_lock; } ;

/* Variables and functions */
 scalar_t__ KREG_IDX (int /*<<< orphan*/ ) ; 
 int NUM_TIDFLOWS_CTXT ; 
 int /*<<< orphan*/  RcvCtrl_0 ; 
 int /*<<< orphan*/  RcvQPMapEnable ; 
 int /*<<< orphan*/  RcvQPMulticastContext_1 ; 
 int /*<<< orphan*/  SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int TIDFLOW_ERRBITS ; 
 scalar_t__ kr_rcvavailtimeout ; 
 unsigned int krp_rcvqpmaptable ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,scalar_t__,int) ; 
 int /*<<< orphan*/  qib_write_kreg_port (struct qib_pportdata*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  qib_write_ureg (struct qib_devdata*,scalar_t__,unsigned int,int) ; 
 int rcv_int_timeout ; 
 int /*<<< orphan*/  setup_7322_link_recovery (struct qib_pportdata*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ ur_rcvflowtable ; 

__attribute__((used)) static void write_7322_initregs(struct qib_devdata *dd)
{
	struct qib_pportdata *ppd;
	int i, pidx;
	u64 val;

	/* Set Multicast QPs received by port 2 to map to context one. */
	qib_write_kreg(dd, KREG_IDX(RcvQPMulticastContext_1), 1);

	for (pidx = 0; pidx < dd->num_pports; ++pidx) {
		unsigned n, regno;
		unsigned long flags;

		if (dd->n_krcv_queues < 2 ||
			!dd->pport[pidx].link_speed_supported)
			continue;

		ppd = &dd->pport[pidx];

		/* be paranoid against later code motion, etc. */
		spin_lock_irqsave(&dd->cspec->rcvmod_lock, flags);
		ppd->p_rcvctrl |= SYM_MASK(RcvCtrl_0, RcvQPMapEnable);
		spin_unlock_irqrestore(&dd->cspec->rcvmod_lock, flags);

		/* Initialize QP to context mapping */
		regno = krp_rcvqpmaptable;
		val = 0;
		if (dd->num_pports > 1)
			n = dd->first_user_ctxt / dd->num_pports;
		else
			n = dd->first_user_ctxt - 1;
		for (i = 0; i < 32; ) {
			unsigned ctxt;

			if (dd->num_pports > 1)
				ctxt = (i % n) * dd->num_pports + pidx;
			else if (i % n)
				ctxt = (i % n) + 1;
			else
				ctxt = ppd->hw_pidx;
			val |= ctxt << (5 * (i % 6));
			i++;
			if (i % 6 == 0) {
				qib_write_kreg_port(ppd, regno, val);
				val = 0;
				regno++;
			}
		}
		qib_write_kreg_port(ppd, regno, val);
	}

	/*
	 * Setup up interrupt mitigation for kernel contexts, but
	 * not user contexts (user contexts use interrupts when
	 * stalled waiting for any packet, so want those interrupts
	 * right away).
	 */
	for (i = 0; i < dd->first_user_ctxt; i++) {
		dd->cspec->rcvavail_timeout[i] = rcv_int_timeout;
		qib_write_kreg(dd, kr_rcvavailtimeout + i, rcv_int_timeout);
	}

	/*
	 * Initialize  as (disabled) rcvflow tables.  Application code
	 * will setup each flow as it uses the flow.
	 * Doesn't clear any of the error bits that might be set.
	 */
	val = TIDFLOW_ERRBITS; /* these are W1C */
	for (i = 0; i < dd->cfgctxts; i++) {
		int flow;
		for (flow = 0; flow < NUM_TIDFLOWS_CTXT; flow++)
			qib_write_ureg(dd, ur_rcvflowtable+flow, val, i);
	}

	/*
	 * dual cards init to dual port recovery, single port cards to
	 * the one port.  Dual port cards may later adjust to 1 port,
	 * and then back to dual port if both ports are connected
	 * */
	if (dd->num_pports)
		setup_7322_link_recovery(dd->pport, dd->num_pports > 1);
}