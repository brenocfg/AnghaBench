#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_6__ {TYPE_1__* asics; } ;
struct TYPE_5__ {int num_asics; } ;
struct TYPE_4__ {int pagelock; } ;

/* Variables and functions */
 int ASIC_IOSIZE ; 
 int NUM_PAGES ; 
 scalar_t__ REG_PAGELOCK ; 
 int REG_PAGE_BITOFFSET ; 
 int REG_PAGE_MASK ; 
 TYPE_3__* devpriv ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 TYPE_2__* thisboard ; 

__attribute__((used)) static void switch_page(struct comedi_device *dev, int asic, int page)
{
	if (asic < 0 || asic >= thisboard->num_asics)
		return;		/* paranoia */
	if (page < 0 || page >= NUM_PAGES)
		return;		/* more paranoia */

	devpriv->asics[asic].pagelock &= ~REG_PAGE_MASK;
	devpriv->asics[asic].pagelock |= page << REG_PAGE_BITOFFSET;

	/* now write out the shadow register */
	outb(devpriv->asics[asic].pagelock,
	     dev->iobase + ASIC_IOSIZE * asic + REG_PAGELOCK);
}