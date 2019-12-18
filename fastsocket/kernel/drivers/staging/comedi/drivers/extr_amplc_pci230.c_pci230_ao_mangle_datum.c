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
struct comedi_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ ao_bipolar; } ;
struct TYPE_3__ {int ao_bits; } ;

/* Variables and functions */
 TYPE_2__* devpriv ; 
 TYPE_1__* thisboard ; 

__attribute__((used)) static inline unsigned short pci230_ao_mangle_datum(struct comedi_device *dev,
						    short datum)
{
	/* If a bipolar range was specified, mangle it (straight binary->twos
	 * complement). */
	if (devpriv->ao_bipolar) {
		datum ^= 1 << (thisboard->ao_bits - 1);
	}

	/* PCI230 is 12 bit - stored in upper bits of 16 bit register (lower
	 * four bits reserved for expansion). */
	/* PCI230+ is also 12 bit AO. */
	datum <<= (16 - thisboard->ao_bits);
	return (unsigned short)datum;
}