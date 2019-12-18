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
typedef  int u32 ;
struct ipath_devdata {int ipath_piobcnt2k; int ipath_piobcnt4k; scalar_t__ ipath_lastcancel; TYPE_1__* ipath_kregs; } ;
struct TYPE_2__ {scalar_t__ kr_sendbuffererror; } ;

/* Variables and functions */
 int __IPATH_DBG ; 
 int /*<<< orphan*/  __IPATH_DBG_WHICH (int,char*,unsigned long,unsigned long) ; 
 int __IPATH_PKTDBG ; 
 int ipath_debug ; 
 int /*<<< orphan*/  ipath_disarm_piobufs (struct ipath_devdata*,int,int) ; 
 unsigned long ipath_read_kreg64 (struct ipath_devdata*,scalar_t__) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 scalar_t__ test_bit (int,unsigned long*) ; 

void ipath_disarm_senderrbufs(struct ipath_devdata *dd)
{
	u32 piobcnt;
	unsigned long sbuf[4];
	/*
	 * it's possible that sendbuffererror could have bits set; might
	 * have already done this as a result of hardware error handling
	 */
	piobcnt = dd->ipath_piobcnt2k + dd->ipath_piobcnt4k;
	/* read these before writing errorclear */
	sbuf[0] = ipath_read_kreg64(
		dd, dd->ipath_kregs->kr_sendbuffererror);
	sbuf[1] = ipath_read_kreg64(
		dd, dd->ipath_kregs->kr_sendbuffererror + 1);
	if (piobcnt > 128)
		sbuf[2] = ipath_read_kreg64(
			dd, dd->ipath_kregs->kr_sendbuffererror + 2);
	if (piobcnt > 192)
		sbuf[3] = ipath_read_kreg64(
			dd, dd->ipath_kregs->kr_sendbuffererror + 3);
	else
		sbuf[3] = 0;

	if (sbuf[0] || sbuf[1] || (piobcnt > 128 && (sbuf[2] || sbuf[3]))) {
		int i;
		if (ipath_debug & (__IPATH_PKTDBG|__IPATH_DBG) &&
			dd->ipath_lastcancel > jiffies) {
			__IPATH_DBG_WHICH(__IPATH_PKTDBG|__IPATH_DBG,
					  "SendbufErrs %lx %lx", sbuf[0],
					  sbuf[1]);
			if (ipath_debug & __IPATH_PKTDBG && piobcnt > 128)
				printk(" %lx %lx ", sbuf[2], sbuf[3]);
			printk("\n");
		}

		for (i = 0; i < piobcnt; i++)
			if (test_bit(i, sbuf))
				ipath_disarm_piobufs(dd, i, 1);
		/* ignore armlaunch errs for a bit */
		dd->ipath_lastcancel = jiffies+3;
	}
}