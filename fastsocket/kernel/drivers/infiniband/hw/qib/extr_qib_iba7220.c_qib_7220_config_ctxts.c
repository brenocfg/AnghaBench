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
typedef  scalar_t__ u32 ;
struct qib_devdata {int qpn_mask; int first_user_ctxt; int num_pports; scalar_t__ n_krcv_queues; int ctxtcnt; unsigned long long rcvctrl; TYPE_1__* cspec; int /*<<< orphan*/  rcvhdrcnt; } ;
struct TYPE_2__ {void* rcvegrcnt; int /*<<< orphan*/  rcvmod_lock; scalar_t__ numctxts; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBA7220_KRCVEGRCNT ; 
 unsigned long long IBA7220_R_CTXTCFG_SHIFT ; 
 unsigned long long QIB_7220_RcvCtrl_RcvQPMapEnable_LSB ; 
 int /*<<< orphan*/  kr_portcnt ; 
 int /*<<< orphan*/  kr_rcvctrl ; 
 int /*<<< orphan*/  kr_rcvegrcnt ; 
 int /*<<< orphan*/  max (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_online_cpus () ; 
 scalar_t__ qib_cfgctxts ; 
 int qib_n_krcv_queues ; 
 void* qib_read_kreg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qib_7220_config_ctxts(struct qib_devdata *dd)
{
	unsigned long flags;
	u32 nchipctxts;

	nchipctxts = qib_read_kreg32(dd, kr_portcnt);
	dd->cspec->numctxts = nchipctxts;
	if (qib_n_krcv_queues > 1) {
		dd->qpn_mask = 0x3e;
		dd->first_user_ctxt = qib_n_krcv_queues * dd->num_pports;
		if (dd->first_user_ctxt > nchipctxts)
			dd->first_user_ctxt = nchipctxts;
	} else
		dd->first_user_ctxt = dd->num_pports;
	dd->n_krcv_queues = dd->first_user_ctxt;

	if (!qib_cfgctxts) {
		int nctxts = dd->first_user_ctxt + num_online_cpus();

		if (nctxts <= 5)
			dd->ctxtcnt = 5;
		else if (nctxts <= 9)
			dd->ctxtcnt = 9;
		else if (nctxts <= nchipctxts)
			dd->ctxtcnt = nchipctxts;
	} else if (qib_cfgctxts <= nchipctxts)
		dd->ctxtcnt = qib_cfgctxts;
	if (!dd->ctxtcnt) /* none of the above, set to max */
		dd->ctxtcnt = nchipctxts;

	/*
	 * Chip can be configured for 5, 9, or 17 ctxts, and choice
	 * affects number of eager TIDs per ctxt (1K, 2K, 4K).
	 * Lock to be paranoid about later motion, etc.
	 */
	spin_lock_irqsave(&dd->cspec->rcvmod_lock, flags);
	if (dd->ctxtcnt > 9)
		dd->rcvctrl |= 2ULL << IBA7220_R_CTXTCFG_SHIFT;
	else if (dd->ctxtcnt > 5)
		dd->rcvctrl |= 1ULL << IBA7220_R_CTXTCFG_SHIFT;
	/* else configure for default 5 receive ctxts */
	if (dd->qpn_mask)
		dd->rcvctrl |= 1ULL << QIB_7220_RcvCtrl_RcvQPMapEnable_LSB;
	qib_write_kreg(dd, kr_rcvctrl, dd->rcvctrl);
	spin_unlock_irqrestore(&dd->cspec->rcvmod_lock, flags);

	/* kr_rcvegrcnt changes based on the number of contexts enabled */
	dd->cspec->rcvegrcnt = qib_read_kreg32(dd, kr_rcvegrcnt);
	dd->rcvhdrcnt = max(dd->cspec->rcvegrcnt, IBA7220_KRCVEGRCNT);
}