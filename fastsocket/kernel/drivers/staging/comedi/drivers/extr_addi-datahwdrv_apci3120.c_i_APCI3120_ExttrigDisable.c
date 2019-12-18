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
struct TYPE_2__ {int /*<<< orphan*/  us_OutputRegister; } ;

/* Variables and functions */
 int /*<<< orphan*/  APCI3120_ENABLE_EXT_TRIGGER ; 
 scalar_t__ APCI3120_WR_ADDRESS ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

int i_APCI3120_ExttrigDisable(struct comedi_device *dev)
{
	devpriv->us_OutputRegister &= ~APCI3120_ENABLE_EXT_TRIGGER;
	outw(devpriv->us_OutputRegister, dev->iobase + APCI3120_WR_ADDRESS);
	return 0;
}