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
struct TYPE_2__ {int clock_ns; } ;

/* Variables and functions */
#define  TRIG_ROUND_DOWN 130 
#define  TRIG_ROUND_NEAREST 129 
#define  TRIG_ROUND_UP 128 
 TYPE_1__* devpriv ; 

__attribute__((used)) static int ni_ns_to_timer(const struct comedi_device *dev, unsigned nanosec,
			  int round_mode)
{
	int divider;
	switch (round_mode) {
	case TRIG_ROUND_NEAREST:
	default:
		divider = (nanosec + devpriv->clock_ns / 2) / devpriv->clock_ns;
		break;
	case TRIG_ROUND_DOWN:
		divider = (nanosec) / devpriv->clock_ns;
		break;
	case TRIG_ROUND_UP:
		divider = (nanosec + devpriv->clock_ns - 1) / devpriv->clock_ns;
		break;
	}
	return divider - 1;
}