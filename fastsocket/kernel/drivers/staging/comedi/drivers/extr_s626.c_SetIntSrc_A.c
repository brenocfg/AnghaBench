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
typedef  size_t uint16_t ;
struct enc_private {int* MyEventBits; int /*<<< orphan*/  MyCRA; int /*<<< orphan*/  MyCRB; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int CounterIntEnabs; } ;

/* Variables and functions */
 size_t CRABIT_INTSRC_A ; 
 size_t CRAMSK_INTSRC_A ; 
 scalar_t__ CRBMSK_INTCTRL ; 
 size_t CRBMSK_INTRESETCMD ; 
 size_t CRBMSK_INTRESET_A ; 
 int /*<<< orphan*/  DEBIreplace (struct comedi_device*,int /*<<< orphan*/ ,size_t,size_t) ; 
 TYPE_1__* devpriv ; 

__attribute__((used)) static void SetIntSrc_A(struct comedi_device *dev, struct enc_private *k,
			uint16_t IntSource)
{
	/*  Reset any pending counter overflow or index captures. */
	DEBIreplace(dev, k->MyCRB, (uint16_t) (~CRBMSK_INTCTRL),
		    CRBMSK_INTRESETCMD | CRBMSK_INTRESET_A);

	/*  Program counter interrupt source. */
	DEBIreplace(dev, k->MyCRA, ~CRAMSK_INTSRC_A,
		    (uint16_t) (IntSource << CRABIT_INTSRC_A));

	/*  Update MISC2 interrupt enable mask. */
	devpriv->CounterIntEnabs =
	    (devpriv->CounterIntEnabs & ~k->
	     MyEventBits[3]) | k->MyEventBits[IntSource];
}