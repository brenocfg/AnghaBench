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
typedef  int /*<<< orphan*/  uint64_t ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ iobase1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_CONFIG (unsigned int,unsigned int) ; 
 scalar_t__ PCI230_Z2_CT_BASE ; 
 scalar_t__ PCI230_ZCLK_SCE ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  i8254_set_mode (scalar_t__,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  i8254_write (scalar_t__,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int pci230_choose_clk_count (int /*<<< orphan*/ ,unsigned int*,unsigned int) ; 

__attribute__((used)) static void pci230_ct_setup_ns_mode(struct comedi_device *dev, unsigned int ct,
				    unsigned int mode, uint64_t ns,
				    unsigned int round)
{
	unsigned int clk_src;
	unsigned int count;

	/* Set mode. */
	i8254_set_mode(devpriv->iobase1 + PCI230_Z2_CT_BASE, 0, ct, mode);
	/* Determine clock source and count. */
	clk_src = pci230_choose_clk_count(ns, &count, round);
	/* Program clock source. */
	outb(CLK_CONFIG(ct, clk_src), devpriv->iobase1 + PCI230_ZCLK_SCE);
	/* Set initial count. */
	if (count >= 65536) {
		count = 0;
	}
	i8254_write(devpriv->iobase1 + PCI230_Z2_CT_BASE, 0, ct, count);
}