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
 unsigned short AO_BC_TC_Interrupt_Ack ; 
 unsigned short AO_BC_TC_St ; 
 unsigned short AO_Error_Interrupt_Ack ; 
 unsigned short AO_Overrun_St ; 
 unsigned short AO_START1_Interrupt_Ack ; 
 unsigned short AO_START1_St ; 
 unsigned short AO_START_Interrupt_Ack ; 
 unsigned short AO_START_St ; 
 unsigned short AO_UC_TC_Interrupt_Ack ; 
 unsigned short AO_UC_TC_St ; 
 unsigned short AO_UI2_TC_Interrupt_Ack ; 
 unsigned short AO_UI2_TC_St ; 
 unsigned short AO_UPDATE_Interrupt_Ack ; 
 unsigned short AO_UPDATE_St ; 
 int /*<<< orphan*/  Interrupt_B_Ack_Register ; 
 TYPE_1__* devpriv ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,unsigned short,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ack_b_interrupt(struct comedi_device *dev, unsigned short b_status)
{
	unsigned short ack = 0;
	if (b_status & AO_BC_TC_St) {
		ack |= AO_BC_TC_Interrupt_Ack;
	}
	if (b_status & AO_Overrun_St) {
		ack |= AO_Error_Interrupt_Ack;
	}
	if (b_status & AO_START_St) {
		ack |= AO_START_Interrupt_Ack;
	}
	if (b_status & AO_START1_St) {
		ack |= AO_START1_Interrupt_Ack;
	}
	if (b_status & AO_UC_TC_St) {
		ack |= AO_UC_TC_Interrupt_Ack;
	}
	if (b_status & AO_UI2_TC_St) {
		ack |= AO_UI2_TC_Interrupt_Ack;
	}
	if (b_status & AO_UPDATE_St) {
		ack |= AO_UPDATE_Interrupt_Ack;
	}
	if (ack)
		devpriv->stc_writew(dev, ack, Interrupt_B_Ack_Register);
}