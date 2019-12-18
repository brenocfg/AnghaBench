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
struct comedi_subdevice {int dummy; } ;
struct comedi_insn {int dummy; } ;
struct comedi_device {int /*<<< orphan*/  spinlock; scalar_t__ iobase; } ;
struct TYPE_2__ {int do_bits; } ;

/* Variables and functions */
 int CONTROL1 ; 
 int CONTROL1_INTE ; 
 scalar_t__ DAS800_CONTROL1 ; 
 scalar_t__ DAS800_GAIN ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int das800_do_wbits(struct comedi_device *dev,
			   struct comedi_subdevice *s, struct comedi_insn *insn,
			   unsigned int *data)
{
	int wbits;
	unsigned long irq_flags;

	/*  only set bits that have been masked */
	data[0] &= 0xf;
	wbits = devpriv->do_bits >> 4;
	wbits &= ~data[0];
	wbits |= data[0] & data[1];
	devpriv->do_bits = wbits << 4;

	spin_lock_irqsave(&dev->spinlock, irq_flags);
	outb(CONTROL1, dev->iobase + DAS800_GAIN);	/* select dev->iobase + 2 to be control register 1 */
	outb(devpriv->do_bits | CONTROL1_INTE, dev->iobase + DAS800_CONTROL1);
	spin_unlock_irqrestore(&dev->spinlock, irq_flags);

	data[1] = wbits;

	return 2;
}