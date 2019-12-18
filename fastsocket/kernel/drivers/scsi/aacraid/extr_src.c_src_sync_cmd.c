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
struct aac_dev {int OIMR; TYPE_1__* IndexRegs; int /*<<< orphan*/  sync_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  ODR_C; int /*<<< orphan*/  ODR_R; int /*<<< orphan*/  IDR; int /*<<< orphan*/  OIMR; } ;
struct TYPE_3__ {int /*<<< orphan*/ * Mailbox; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int INBOUNDDOORBELL_0 ; 
 TYPE_2__ MUnit ; 
 int OUTBOUNDDOORBELL_0 ; 
 scalar_t__ SEND_SYNCHRONOUS_FIB ; 
 int SRC_IDR_SHIFT ; 
 int SRC_ODR_SHIFT ; 
 int /*<<< orphan*/  aac_adapter_enable_int (struct aac_dev*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ readl (int /*<<< orphan*/ *) ; 
 int src_readl (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src_writel (struct aac_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int src_sync_cmd(struct aac_dev *dev, u32 command,
	u32 p1, u32 p2, u32 p3, u32 p4, u32 p5, u32 p6,
	u32 *status, u32 * r1, u32 * r2, u32 * r3, u32 * r4)
{
	unsigned long start;
	int ok;

	/*
	 *	Write the command into Mailbox 0
	 */
	writel(command, &dev->IndexRegs->Mailbox[0]);
	/*
	 *	Write the parameters into Mailboxes 1 - 6
	 */
	writel(p1, &dev->IndexRegs->Mailbox[1]);
	writel(p2, &dev->IndexRegs->Mailbox[2]);
	writel(p3, &dev->IndexRegs->Mailbox[3]);
	writel(p4, &dev->IndexRegs->Mailbox[4]);

	/*
	 *	Clear the synch command doorbell to start on a clean slate.
	 */
	src_writel(dev, MUnit.ODR_C, OUTBOUNDDOORBELL_0 << SRC_ODR_SHIFT);

	/*
	 *	Disable doorbell interrupts
	 */
	src_writel(dev, MUnit.OIMR, dev->OIMR = 0xffffffff);

	/*
	 *	Force the completion of the mask register write before issuing
	 *	the interrupt.
	 */
	src_readl(dev, MUnit.OIMR);

	/*
	 *	Signal that there is a new synch command
	 */
	src_writel(dev, MUnit.IDR, INBOUNDDOORBELL_0 << SRC_IDR_SHIFT);

	if (!dev->sync_mode || command != SEND_SYNCHRONOUS_FIB) {
		ok = 0;
		start = jiffies;

		/*
		 *	Wait up to 5 minutes
		 */
		while (time_before(jiffies, start+300*HZ)) {
			udelay(5);	/* Delay 5 microseconds to let Mon960 get info. */
			/*
			 *	Mon960 will set doorbell0 bit when it has completed the command.
			 */
			if ((src_readl(dev, MUnit.ODR_R) >> SRC_ODR_SHIFT) & OUTBOUNDDOORBELL_0) {
				/*
				 *	Clear the doorbell.
				 */
				src_writel(dev, MUnit.ODR_C, OUTBOUNDDOORBELL_0 << SRC_ODR_SHIFT);
				ok = 1;
				break;
			}
			/*
			 *	Yield the processor in case we are slow
			 */
			msleep(1);
		}
		if (unlikely(ok != 1)) {
			/*
			 *	Restore interrupt mask even though we timed out
			 */
			aac_adapter_enable_int(dev);
			return -ETIMEDOUT;
		}
		/*
		 *	Pull the synch status from Mailbox 0.
		 */
		if (status)
			*status = readl(&dev->IndexRegs->Mailbox[0]);
		if (r1)
			*r1 = readl(&dev->IndexRegs->Mailbox[1]);
		if (r2)
			*r2 = readl(&dev->IndexRegs->Mailbox[2]);
		if (r3)
			*r3 = readl(&dev->IndexRegs->Mailbox[3]);
		if (r4)
			*r4 = readl(&dev->IndexRegs->Mailbox[4]);

		/*
		 *	Clear the synch command doorbell.
		 */
		src_writel(dev, MUnit.ODR_C, OUTBOUNDDOORBELL_0 << SRC_ODR_SHIFT);
	}

	/*
	 *	Restore interrupt mask
	 */
	aac_adapter_enable_int(dev);
	return 0;
}