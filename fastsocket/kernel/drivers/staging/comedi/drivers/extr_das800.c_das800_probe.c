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

/* Variables and functions */
 scalar_t__ DAS800_GAIN ; 
 scalar_t__ DAS800_ID ; 
 int /*<<< orphan*/  ID ; 
 int ciodas800 ; 
 int ciodas801 ; 
 int ciodas802 ; 
 int ciodas80216 ; 
 int das800 ; 
 int das800_boards ; 
 int das801 ; 
 int das802 ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int thisboard ; 

__attribute__((used)) static int das800_probe(struct comedi_device *dev)
{
	int id_bits;
	unsigned long irq_flags;
	int board;

	/*  'comedi spin lock irqsave' disables even rt interrupts, we use them to protect indirect addressing */
	spin_lock_irqsave(&dev->spinlock, irq_flags);
	outb(ID, dev->iobase + DAS800_GAIN);	/* select base address + 7 to be ID register */
	id_bits = inb(dev->iobase + DAS800_ID) & 0x3;	/* get id bits */
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	board = thisboard - das800_boards;

	switch (id_bits) {
	case 0x0:
		if (board == das800) {
			printk(" Board model: DAS-800\n");
			return board;
		}
		if (board == ciodas800) {
			printk(" Board model: CIO-DAS800\n");
			return board;
		}
		printk(" Board model (probed): DAS-800\n");
		return das800;
		break;
	case 0x2:
		if (board == das801) {
			printk(" Board model: DAS-801\n");
			return board;
		}
		if (board == ciodas801) {
			printk(" Board model: CIO-DAS801\n");
			return board;
		}
		printk(" Board model (probed): DAS-801\n");
		return das801;
		break;
	case 0x3:
		if (board == das802) {
			printk(" Board model: DAS-802\n");
			return board;
		}
		if (board == ciodas802) {
			printk(" Board model: CIO-DAS802\n");
			return board;
		}
		if (board == ciodas80216) {
			printk(" Board model: CIO-DAS802/16\n");
			return board;
		}
		printk(" Board model (probed): DAS-802\n");
		return das802;
		break;
	default:
		printk(" Board model: probe returned 0x%x (unknown)\n",
		       id_bits);
		return board;
		break;
	}
	return -1;
}