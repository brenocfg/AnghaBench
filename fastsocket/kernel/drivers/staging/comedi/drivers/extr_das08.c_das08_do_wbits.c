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
struct TYPE_2__ {int do_mux_bits; } ;

/* Variables and functions */
 scalar_t__ DAS08_CONTROL ; 
 int DAS08_DO_MASK ; 
 int DAS08_OP (int) ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int das08_do_wbits(struct comedi_device *dev, struct comedi_subdevice *s,
			  struct comedi_insn *insn, unsigned int *data)
{
	int wbits;

	/*  get current settings of digital output lines */
	wbits = (devpriv->do_mux_bits >> 4) & 0xf;
	/*  null bits we are going to set */
	wbits &= ~data[0];
	/*  set new bit values */
	wbits |= data[0] & data[1];
	/*  remember digital output bits */
	spin_lock(&dev->spinlock);	/*  prevent race with setting of analog input mux */
	devpriv->do_mux_bits &= ~DAS08_DO_MASK;
	devpriv->do_mux_bits |= DAS08_OP(wbits);
	outb(devpriv->do_mux_bits, dev->iobase + DAS08_CONTROL);
	spin_unlock(&dev->spinlock);

	data[1] = wbits;

	return 2;
}