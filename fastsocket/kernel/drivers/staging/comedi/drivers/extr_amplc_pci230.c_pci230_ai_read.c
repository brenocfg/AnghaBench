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
struct TYPE_4__ {scalar_t__ ai_bipolar; } ;
struct TYPE_3__ {int ai_bits; } ;

/* Variables and functions */
 scalar_t__ PCI230_ADCDATA ; 
 TYPE_2__* devpriv ; 
 scalar_t__ inw (scalar_t__) ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static short pci230_ai_read(struct comedi_device *dev)
{
	/* Read sample. */
	short data = (short)inw(dev->iobase + PCI230_ADCDATA);

	/* PCI230 is 12 bit - stored in upper bits of 16 bit register (lower
	 * four bits reserved for expansion). */
	/* PCI230+ is 16 bit AI. */
	data = data >> (16 - thisboard->ai_bits);

	/* If a bipolar range was specified, mangle it (twos
	 * complement->straight binary). */
	if (devpriv->ai_bipolar) {
		data ^= 1 << (thisboard->ai_bits - 1);
	}
	return data;
}