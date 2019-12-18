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
struct TYPE_2__ {scalar_t__ iobase; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 int i_WatchdogNbr ; 
 int /*<<< orphan*/  outl (int,scalar_t__) ; 

int i_APCI035_Reset(struct comedi_device *dev)
{
	int i_Count = 0;
	for (i_Count = 1; i_Count <= 4; i_Count++) {
		i_WatchdogNbr = i_Count;
		outl(0x0, devpriv->iobase + ((i_WatchdogNbr - 1) * 32) + 0);	/* stop all timers */
	}
	outl(0x0, devpriv->iobase + 128 + 12);	/* Disable the warning delay */

	return 0;
}