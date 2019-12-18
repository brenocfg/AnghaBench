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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ iobase1; } ;

/* Variables and functions */
 int /*<<< orphan*/  I8254_MODE1 ; 
 scalar_t__ PCI230_Z2_CT_BASE ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  i8254_set_mode (scalar_t__,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pci230_cancel_ct(struct comedi_device *dev, unsigned int ct)
{
	i8254_set_mode(devpriv->iobase1 + PCI230_Z2_CT_BASE, 0, ct,
		       I8254_MODE1);
	/* Counter ct, 8254 mode 1, initial count not written. */
}