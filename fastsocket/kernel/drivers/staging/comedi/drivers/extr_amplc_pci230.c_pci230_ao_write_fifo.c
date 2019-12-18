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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {short* ao_readback; } ;

/* Variables and functions */
 scalar_t__ PCI230P2_DACDATA ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci230_ao_mangle_datum (struct comedi_device*,short) ; 

__attribute__((used)) static inline void pci230_ao_write_fifo(struct comedi_device *dev, short datum,
					unsigned int chan)
{
	/* Store unmangled datum to be read back later. */
	devpriv->ao_readback[chan] = datum;

	/* Write mangled datum to appropriate DACDATA register. */
	outw(pci230_ao_mangle_datum(dev, datum),
	     dev->iobase + PCI230P2_DACDATA);
}