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
struct TYPE_2__ {int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,unsigned short,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 unsigned short AI_SC_TC_Interrupt_Ack ; 
 unsigned short AI_SC_TC_St ; 
 unsigned short AI_START1_Interrupt_Ack ; 
 unsigned short AI_START1_St ; 
 unsigned short AI_START_Interrupt_Ack ; 
 unsigned short AI_START_St ; 
 unsigned short AI_STOP_Interrupt_Ack ; 
 unsigned short AI_STOP_St ; 
 int /*<<< orphan*/  Interrupt_A_Ack_Register ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ack_a_interrupt(struct comedi_device *dev, unsigned short a_status)
{
	unsigned short ack = 0;

	if (a_status & AI_SC_TC_St) {
		ack |= AI_SC_TC_Interrupt_Ack;
	}
	if (a_status & AI_START1_St) {
		ack |= AI_START1_Interrupt_Ack;
	}
	if (a_status & AI_START_St) {
		ack |= AI_START_Interrupt_Ack;
	}
	if (a_status & AI_STOP_St) {
		/* not sure why we used to ack the START here also, instead of doing it independently. Frank Hess 2007-07-06 */
		ack |= AI_STOP_Interrupt_Ack /*| AI_START_Interrupt_Ack */ ;
	}
	if (ack)
		devpriv->stc_writew(dev, ack, Interrupt_A_Ack_Register);
}