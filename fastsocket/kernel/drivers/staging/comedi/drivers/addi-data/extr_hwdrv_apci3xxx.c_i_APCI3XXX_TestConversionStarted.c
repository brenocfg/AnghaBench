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
struct TYPE_2__ {scalar_t__ dw_AiBase; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 
 int readl (void*) ; 

int i_APCI3XXX_TestConversionStarted(struct comedi_device *dev)
{
	if ((readl((void *)(devpriv->dw_AiBase + 8)) & 0x80000UL) == 0x80000UL)
		return 1;
	else
		return 0;

}