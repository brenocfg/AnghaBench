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
struct ipath_devdata {int /*<<< orphan*/  ipath_sdma_lock; int /*<<< orphan*/  ipath_sdma_status; TYPE_1__* ipath_kregs; } ;
typedef  int ipath_err_t ;
struct TYPE_2__ {int /*<<< orphan*/  kr_senddmalengen; int /*<<< orphan*/  kr_senddmastatus; int /*<<< orphan*/  kr_senddmahead; int /*<<< orphan*/  kr_senddmatail; } ;

/* Variables and functions */
 int INFINIPATH_E_SDMAERRS ; 
 int /*<<< orphan*/  IPATH_SDMA_ABORTING ; 
 int /*<<< orphan*/  IPATH_SDMA_DISABLED ; 
 int /*<<< orphan*/  VERBOSE ; 
 int __IPATH_DBG ; 
 int __IPATH_VERBDBG ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipath_cancel_sends (struct ipath_devdata*,int) ; 
 int /*<<< orphan*/  ipath_cdbg (int /*<<< orphan*/ ,char*,unsigned long,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  ipath_dbg (char*,unsigned long,char*) ; 
 int ipath_debug ; 
 int /*<<< orphan*/  ipath_decode_err (struct ipath_devdata*,char*,int,int) ; 
 unsigned long ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_sdma_errors(struct ipath_devdata *dd, ipath_err_t errs)
{
	unsigned long flags;
	int expected;

	if (ipath_debug & __IPATH_DBG) {
		char msg[128];
		ipath_decode_err(dd, msg, sizeof msg, errs &
			INFINIPATH_E_SDMAERRS);
		ipath_dbg("errors %lx (%s)\n", (unsigned long)errs, msg);
	}
	if (ipath_debug & __IPATH_VERBDBG) {
		unsigned long tl, hd, status, lengen;
		tl = ipath_read_kreg64(dd, dd->ipath_kregs->kr_senddmatail);
		hd = ipath_read_kreg64(dd, dd->ipath_kregs->kr_senddmahead);
		status = ipath_read_kreg64(dd
			, dd->ipath_kregs->kr_senddmastatus);
		lengen = ipath_read_kreg64(dd,
			dd->ipath_kregs->kr_senddmalengen);
		ipath_cdbg(VERBOSE, "sdma tl 0x%lx hd 0x%lx status 0x%lx "
			"lengen 0x%lx\n", tl, hd, status, lengen);
	}

	spin_lock_irqsave(&dd->ipath_sdma_lock, flags);
	__set_bit(IPATH_SDMA_DISABLED, &dd->ipath_sdma_status);
	expected = test_bit(IPATH_SDMA_ABORTING, &dd->ipath_sdma_status);
	spin_unlock_irqrestore(&dd->ipath_sdma_lock, flags);
	if (!expected)
		ipath_cancel_sends(dd, 1);
}