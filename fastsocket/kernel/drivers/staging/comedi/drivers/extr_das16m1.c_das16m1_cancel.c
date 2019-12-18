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
struct comedi_device {scalar_t__ iobase; } ;
struct TYPE_2__ {int control_state; } ;

/* Variables and functions */
 scalar_t__ DAS16M1_INTR_CONTROL ; 
 int INTE ; 
 int PACER_MASK ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int das16m1_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	devpriv->control_state &= ~INTE & ~PACER_MASK;
	outb(devpriv->control_state, dev->iobase + DAS16M1_INTR_CONTROL);

	return 0;
}