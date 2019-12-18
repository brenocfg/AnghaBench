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
typedef  scalar_t__ u32 ;
struct ipath_devdata {unsigned long long ipath_rcvctrl; unsigned long long ipath_r_tailupd_shift; int ipath_portcnt; unsigned int ipath_sendctrl; scalar_t__ ipath_rcvtidcnt; scalar_t__ ipath_rcvtidbase; scalar_t__ ipath_rcvegrcnt; scalar_t__ ipath_rcvegrbase; TYPE_2__* pcidev; TYPE_1__* ipath_kregs; int /*<<< orphan*/  ipath_sendctrl_lock; scalar_t__ ipath_r_intravail_shift; scalar_t__ ipath_r_portenable_shift; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  kr_rcvegrbase; int /*<<< orphan*/  kr_rcvegrcnt; int /*<<< orphan*/  kr_rcvtidbase; int /*<<< orphan*/  kr_rcvtidcnt; int /*<<< orphan*/  kr_control; int /*<<< orphan*/  kr_scratch; int /*<<< orphan*/  kr_sendctrl; int /*<<< orphan*/  kr_rcvctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (scalar_t__,unsigned long long*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ ipath_read_kreg32 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_read_kreg64 (struct ipath_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipath_write_kreg (struct ipath_devdata*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int init_chip_reset(struct ipath_devdata *dd)
{
	u32 rtmp;
	int i;
	unsigned long flags;

	/*
	 * ensure chip does no sends or receives, tail updates, or
	 * pioavail updates while we re-initialize
	 */
	dd->ipath_rcvctrl &= ~(1ULL << dd->ipath_r_tailupd_shift);
	for (i = 0; i < dd->ipath_portcnt; i++) {
		clear_bit(dd->ipath_r_portenable_shift + i,
			  &dd->ipath_rcvctrl);
		clear_bit(dd->ipath_r_intravail_shift + i,
			  &dd->ipath_rcvctrl);
	}
	ipath_write_kreg(dd, dd->ipath_kregs->kr_rcvctrl,
		dd->ipath_rcvctrl);

	spin_lock_irqsave(&dd->ipath_sendctrl_lock, flags);
	dd->ipath_sendctrl = 0U; /* no sdma, etc */
	ipath_write_kreg(dd, dd->ipath_kregs->kr_sendctrl, dd->ipath_sendctrl);
	ipath_read_kreg64(dd, dd->ipath_kregs->kr_scratch);
	spin_unlock_irqrestore(&dd->ipath_sendctrl_lock, flags);

	ipath_write_kreg(dd, dd->ipath_kregs->kr_control, 0ULL);

	rtmp = ipath_read_kreg32(dd, dd->ipath_kregs->kr_rcvtidcnt);
	if (rtmp != dd->ipath_rcvtidcnt)
		dev_info(&dd->pcidev->dev, "tidcnt was %u before "
			 "reset, now %u, using original\n",
			 dd->ipath_rcvtidcnt, rtmp);
	rtmp = ipath_read_kreg32(dd, dd->ipath_kregs->kr_rcvtidbase);
	if (rtmp != dd->ipath_rcvtidbase)
		dev_info(&dd->pcidev->dev, "tidbase was %u before "
			 "reset, now %u, using original\n",
			 dd->ipath_rcvtidbase, rtmp);
	rtmp = ipath_read_kreg32(dd, dd->ipath_kregs->kr_rcvegrcnt);
	if (rtmp != dd->ipath_rcvegrcnt)
		dev_info(&dd->pcidev->dev, "egrcnt was %u before "
			 "reset, now %u, using original\n",
			 dd->ipath_rcvegrcnt, rtmp);
	rtmp = ipath_read_kreg32(dd, dd->ipath_kregs->kr_rcvegrbase);
	if (rtmp != dd->ipath_rcvegrbase)
		dev_info(&dd->pcidev->dev, "egrbase was %u before "
			 "reset, now %u, using original\n",
			 dd->ipath_rcvegrbase, rtmp);

	return 0;
}