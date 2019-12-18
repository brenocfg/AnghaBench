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
typedef  int /*<<< orphan*/  u32 ;
struct aac_dev {int OIMR; TYPE_1__* IndexRegs; } ;
struct TYPE_4__ {int /*<<< orphan*/  OIMR; } ;
struct TYPE_3__ {int /*<<< orphan*/ * Mailbox; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HZ ; 
 int INBOUNDDOORBELL_0 ; 
 int /*<<< orphan*/  InboundDoorbellReg ; 
 TYPE_2__ MUnit ; 
 int OUTBOUNDDOORBELL_0 ; 
 int /*<<< orphan*/  OutboundDoorbellReg ; 
 int /*<<< orphan*/  aac_adapter_enable_int (struct aac_dev*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_readb (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int rx_readl (struct aac_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rx_writeb (struct aac_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rx_writel (struct aac_dev*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rx_sync_cmd(struct aac_dev *dev, u32 command,
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
	rx_writel(dev, OutboundDoorbellReg, OUTBOUNDDOORBELL_0);
	/*
	 *	Disable doorbell interrupts
	 */
	rx_writeb(dev, MUnit.OIMR, dev->OIMR = 0xff);
	/*
	 *	Force the completion of the mask register write before issuing
	 *	the interrupt.
	 */
	rx_readb (dev, MUnit.OIMR);
	/*
	 *	Signal that there is a new synch command
	 */
	rx_writel(dev, InboundDoorbellReg, INBOUNDDOORBELL_0);

	ok = 0;
	start = jiffies;

	/*
	 *	Wait up to 30 seconds
	 */
	while (time_before(jiffies, start+30*HZ)) 
	{
		udelay(5);	/* Delay 5 microseconds to let Mon960 get info. */
		/*
		 *	Mon960 will set doorbell0 bit when it has completed the command.
		 */
		if (rx_readl(dev, OutboundDoorbellReg) & OUTBOUNDDOORBELL_0) {
			/*
			 *	Clear the doorbell.
			 */
			rx_writel(dev, OutboundDoorbellReg, OUTBOUNDDOORBELL_0);
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
	rx_writel(dev, OutboundDoorbellReg, OUTBOUNDDOORBELL_0);
	/*
	 *	Restore interrupt mask
	 */
	aac_adapter_enable_int(dev);
	return 0;

}