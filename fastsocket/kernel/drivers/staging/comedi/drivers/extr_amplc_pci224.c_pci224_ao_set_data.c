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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_4__ {unsigned int* ao_readback; unsigned short daccon; int /*<<< orphan*/ * hwrange; } ;
struct TYPE_3__ {int ao_bits; } ;

/* Variables and functions */
 unsigned short COMBINE (unsigned short,int /*<<< orphan*/ ,int) ; 
 scalar_t__ PCI224_DACCEN ; 
 scalar_t__ PCI224_DACCON ; 
 unsigned short PCI224_DACCON_FIFORESET ; 
 int PCI224_DACCON_POLAR_BI ; 
 int PCI224_DACCON_POLAR_MASK ; 
 int PCI224_DACCON_VREF_MASK ; 
 scalar_t__ PCI224_DACDATA ; 
 scalar_t__ PCI224_SOFTTRIG ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (unsigned short,scalar_t__) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static void
pci224_ao_set_data(struct comedi_device *dev, int chan, int range,
		   unsigned int data)
{
	unsigned short mangled;

	/* Store unmangled data for readback. */
	devpriv->ao_readback[chan] = data;
	/* Enable the channel. */
	outw(1 << chan, dev->iobase + PCI224_DACCEN);
	/* Set range and reset FIFO. */
	devpriv->daccon = COMBINE(devpriv->daccon, devpriv->hwrange[range],
				  (PCI224_DACCON_POLAR_MASK |
				   PCI224_DACCON_VREF_MASK));
	outw(devpriv->daccon | PCI224_DACCON_FIFORESET,
	     dev->iobase + PCI224_DACCON);
	/*
	 * Mangle the data.  The hardware expects:
	 * - bipolar: 16-bit 2's complement
	 * - unipolar: 16-bit unsigned
	 */
	mangled = (unsigned short)data << (16 - thisboard->ao_bits);
	if ((devpriv->daccon & PCI224_DACCON_POLAR_MASK) ==
	    PCI224_DACCON_POLAR_BI) {
		mangled ^= 0x8000;
	}
	/* Write mangled data to the FIFO. */
	outw(mangled, dev->iobase + PCI224_DACDATA);
	/* Trigger the conversion. */
	inw(dev->iobase + PCI224_SOFTTRIG);
}