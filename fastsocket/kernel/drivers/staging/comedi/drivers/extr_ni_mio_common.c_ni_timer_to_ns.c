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
 TYPE_1__* devpriv ; 

__attribute__((used)) static unsigned ni_timer_to_ns(const struct comedi_device *dev, int timer)
{
	return devpriv->clock_ns * (timer + 1);
}