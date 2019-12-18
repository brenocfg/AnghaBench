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
typedef  scalar_t__ u64 ;
struct ipath_portdata {int port_lastrcvhdrqtail; } ;
struct ipath_devdata {int ipath_flags; scalar_t__ ipath_traffic_wds; int ipath_maskederrs; int ipath_errormask; int /*<<< orphan*/  ipath_stats_timer; struct ipath_portdata** ipath_pd; scalar_t__ ipath_cfgports; TYPE_2__* ipath_kregs; int /*<<< orphan*/  ipath_unmasktime; scalar_t__ ipath_lasthwerror; scalar_t__ ipath_lasterror; TYPE_1__* ipath_cregs; int /*<<< orphan*/  ipath_eep_st_lock; int /*<<< orphan*/  ipath_active_time; int /*<<< orphan*/  ipath_kregbase; } ;
struct TYPE_4__ {int /*<<< orphan*/  kr_errormask; } ;
struct TYPE_3__ {int /*<<< orphan*/  cr_pktrcvcnt; int /*<<< orphan*/  cr_pktsendcnt; int /*<<< orphan*/  cr_wordrcvcnt; int /*<<< orphan*/  cr_wordsendcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERRPKT ; 
 int HZ ; 
 int INFINIPATH_E_PKTERRS ; 
 int INFINIPATH_E_RRCVEGRFULL ; 
 int INFINIPATH_E_RRCVHDRFULL ; 
 int IPATH_32BITCOUNTERS ; 
 int IPATH_INITTED ; 
 scalar_t__ IPATH_TRAFFIC_ACTIVE_THRESHOLD ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  ipath_chk_errormask (struct ipath_devdata*) ; 
 int /*<<< orphan*/  ipath_dbg (char*,char*) ; 
 int ipath_decode_err (struct ipath_devdata*,char*,int,int) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*,char*) ; 
 scalar_t__ ipath_diag_inuse ; 
 int /*<<< orphan*/  ipath_qcheck (struct ipath_devdata*) ; 
 scalar_t__ ipath_snap_cntr (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after (scalar_t__,int /*<<< orphan*/ ) ; 

void ipath_get_faststats(unsigned long opaque)
{
	struct ipath_devdata *dd = (struct ipath_devdata *) opaque;
	int i;
	static unsigned cnt;
	unsigned long flags;
	u64 traffic_wds;

	/*
	 * don't access the chip while running diags, or memory diags can
	 * fail
	 */
	if (!dd->ipath_kregbase || !(dd->ipath_flags & IPATH_INITTED) ||
	    ipath_diag_inuse)
		/* but re-arm the timer, for diags case; won't hurt other */
		goto done;

	/*
	 * We now try to maintain a "active timer", based on traffic
	 * exceeding a threshold, so we need to check the word-counts
	 * even if they are 64-bit.
	 */
	traffic_wds = ipath_snap_cntr(dd, dd->ipath_cregs->cr_wordsendcnt) +
		ipath_snap_cntr(dd, dd->ipath_cregs->cr_wordrcvcnt);
	spin_lock_irqsave(&dd->ipath_eep_st_lock, flags);
	traffic_wds -= dd->ipath_traffic_wds;
	dd->ipath_traffic_wds += traffic_wds;
	if (traffic_wds  >= IPATH_TRAFFIC_ACTIVE_THRESHOLD)
		atomic_add(5, &dd->ipath_active_time); /* S/B #define */
	spin_unlock_irqrestore(&dd->ipath_eep_st_lock, flags);

	if (dd->ipath_flags & IPATH_32BITCOUNTERS) {
		ipath_snap_cntr(dd, dd->ipath_cregs->cr_pktsendcnt);
		ipath_snap_cntr(dd, dd->ipath_cregs->cr_pktrcvcnt);
	}

	ipath_qcheck(dd);

	/*
	 * deal with repeat error suppression.  Doesn't really matter if
	 * last error was almost a full interval ago, or just a few usecs
	 * ago; still won't get more than 2 per interval.  We may want
	 * longer intervals for this eventually, could do with mod, counter
	 * or separate timer.  Also see code in ipath_handle_errors() and
	 * ipath_handle_hwerrors().
	 */

	if (dd->ipath_lasterror)
		dd->ipath_lasterror = 0;
	if (dd->ipath_lasthwerror)
		dd->ipath_lasthwerror = 0;
	if (dd->ipath_maskederrs
	    && time_after(jiffies, dd->ipath_unmasktime)) {
		char ebuf[256];
		int iserr;
		iserr = ipath_decode_err(dd, ebuf, sizeof ebuf,
					 dd->ipath_maskederrs);
		if (dd->ipath_maskederrs &
		    ~(INFINIPATH_E_RRCVEGRFULL | INFINIPATH_E_RRCVHDRFULL |
		      INFINIPATH_E_PKTERRS))
			ipath_dev_err(dd, "Re-enabling masked errors "
				      "(%s)\n", ebuf);
		else {
			/*
			 * rcvegrfull and rcvhdrqfull are "normal", for some
			 * types of processes (mostly benchmarks) that send
			 * huge numbers of messages, while not processing
			 * them.  So only complain about these at debug
			 * level.
			 */
			if (iserr)
				ipath_dbg(
					"Re-enabling queue full errors (%s)\n",
					ebuf);
			else
				ipath_cdbg(ERRPKT, "Re-enabling packet"
					" problem interrupt (%s)\n", ebuf);
		}

		/* re-enable masked errors */
		dd->ipath_errormask |= dd->ipath_maskederrs;
		ipath_write_kreg(dd, dd->ipath_kregs->kr_errormask,
				 dd->ipath_errormask);
		dd->ipath_maskederrs = 0;
	}

	/* limit qfull messages to ~one per minute per port */
	if ((++cnt & 0x10)) {
		for (i = (int) dd->ipath_cfgports; --i >= 0; ) {
			struct ipath_portdata *pd = dd->ipath_pd[i];

			if (pd && pd->port_lastrcvhdrqtail != -1)
				pd->port_lastrcvhdrqtail = -1;
		}
	}

	ipath_chk_errormask(dd);
done:
	mod_timer(&dd->ipath_stats_timer, jiffies + HZ * 5);
}