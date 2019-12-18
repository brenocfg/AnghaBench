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
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int control_1; scalar_t__ me_regbase; } ;

/* Variables and functions */
 scalar_t__ ME_CONTROL_1 ; 
 TYPE_1__* dev_private ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int me_ai_cancel(struct comedi_device *dev, struct comedi_subdevice *s)
{
	/* disable interrupts */

	/* stop any running conversion */
	dev_private->control_1 &= 0xFFFC;
	writew(dev_private->control_1, dev_private->me_regbase + ME_CONTROL_1);

	return 0;
}