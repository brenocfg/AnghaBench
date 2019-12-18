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
typedef  int /*<<< orphan*/  u64 ;
struct ipath_devdata {int ipath_flags; TYPE_1__* ipath_cregs; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_sendstallcnt; int /*<<< orphan*/  cr_pktrcvcnt; int /*<<< orphan*/  cr_pktsendcnt; int /*<<< orphan*/  cr_wordrcvcnt; int /*<<< orphan*/  cr_wordsendcnt; } ;

/* Variables and functions */
 int EINVAL ; 
 int IPATH_INITTED ; 
 int /*<<< orphan*/  ipath_snap_cntr (struct ipath_devdata*,int /*<<< orphan*/ ) ; 

int ipath_snapshot_counters(struct ipath_devdata *dd, u64 *swords,
			    u64 *rwords, u64 *spkts, u64 *rpkts,
			    u64 *xmit_wait)
{
	int ret;

	if (!(dd->ipath_flags & IPATH_INITTED)) {
		/* no hardware, freeze, etc. */
		ret = -EINVAL;
		goto bail;
	}
	*swords = ipath_snap_cntr(dd, dd->ipath_cregs->cr_wordsendcnt);
	*rwords = ipath_snap_cntr(dd, dd->ipath_cregs->cr_wordrcvcnt);
	*spkts = ipath_snap_cntr(dd, dd->ipath_cregs->cr_pktsendcnt);
	*rpkts = ipath_snap_cntr(dd, dd->ipath_cregs->cr_pktrcvcnt);
	*xmit_wait = ipath_snap_cntr(dd, dd->ipath_cregs->cr_sendstallcnt);

	ret = 0;

bail:
	return ret;
}