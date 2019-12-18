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
struct TYPE_2__ {int /*<<< orphan*/  divisor2; int /*<<< orphan*/  divisor1; } ;

/* Variables and functions */
 scalar_t__ DAS16M1_8254_SECOND ; 
 int /*<<< orphan*/  DAS16M1_XTAL ; 
 int TRIG_ROUND_MASK ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  i8253_cascade_ns_to_timer_2div (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int) ; 
 int /*<<< orphan*/  i8254_load (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int das16m1_set_pacer(struct comedi_device *dev,
				      unsigned int ns, int rounding_flags)
{
	i8253_cascade_ns_to_timer_2div(DAS16M1_XTAL, &(devpriv->divisor1),
				       &(devpriv->divisor2), &ns,
				       rounding_flags & TRIG_ROUND_MASK);

	/* Write the values of ctr1 and ctr2 into counters 1 and 2 */
	i8254_load(dev->iobase + DAS16M1_8254_SECOND, 0, 1, devpriv->divisor1,
		   2);
	i8254_load(dev->iobase + DAS16M1_8254_SECOND, 0, 2, devpriv->divisor2,
		   2);

	return ns;
}