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
struct comedi_device {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ DAS16_CNTR_CONTROL ; 
 scalar_t__ DAS16_CONTROL ; 
 scalar_t__ DAS16_PACER ; 
 scalar_t__ DAS16_STATUS ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void das16_reset(struct comedi_device *dev)
{
	outb(0, dev->iobase + DAS16_STATUS);
	outb(0, dev->iobase + DAS16_CONTROL);
	outb(0, dev->iobase + DAS16_PACER);
	outb(0, dev->iobase + DAS16_CNTR_CONTROL);
}