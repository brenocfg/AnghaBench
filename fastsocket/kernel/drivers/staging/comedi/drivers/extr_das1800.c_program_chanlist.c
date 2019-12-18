#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; } ;
struct comedi_cmd {int chanlist_len; int /*<<< orphan*/ * chanlist; } ;

/* Variables and functions */
 int const CR_CHAN (int /*<<< orphan*/ ) ; 
 int const CR_RANGE (int /*<<< orphan*/ ) ; 
 scalar_t__ DAS1800_QRAM ; 
 scalar_t__ DAS1800_QRAM_ADDRESS ; 
 scalar_t__ DAS1800_SELECT ; 
 int QRAM ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void program_chanlist(struct comedi_device *dev, struct comedi_cmd cmd)
{
	int i, n, chan_range;
	unsigned long irq_flags;
	const int range_mask = 0x3;	/* masks unipolar/bipolar bit off range */
	const int range_bitshift = 8;

	n = cmd.chanlist_len;
	/*  spinlock protects indirect addressing */
	spin_lock_irqsave(&dev->spinlock, irq_flags);
	outb(QRAM, dev->iobase + DAS1800_SELECT);	/* select QRAM for baseAddress + 0x0 */
	outb(n - 1, dev->iobase + DAS1800_QRAM_ADDRESS);	/*set QRAM address start */
	/* make channel / gain list */
	for (i = 0; i < n; i++) {
		chan_range =
		    CR_CHAN(cmd.
			    chanlist[i]) | ((CR_RANGE(cmd.chanlist[i]) &
					     range_mask) << range_bitshift);
		outw(chan_range, dev->iobase + DAS1800_QRAM);
	}
	outb(n - 1, dev->iobase + DAS1800_QRAM_ADDRESS);	/*finish write to QRAM */
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	return;
}