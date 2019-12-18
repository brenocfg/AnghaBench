#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dvb_ca_private {int /*<<< orphan*/  open; TYPE_2__* slot_info; TYPE_1__* pub; } ;
struct dvb_ca_en50221 {struct dvb_ca_private* private; } ;
struct TYPE_4__ {int slot_state; int da_irq_supported; } ;
struct TYPE_3__ {int (* read_cam_control ) (struct dvb_ca_en50221*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTRLIF_STATUS ; 
#define  DVB_CA_SLOTSTATE_LINKINIT 129 
#define  DVB_CA_SLOTSTATE_RUNNING 128 
 int STATUSREG_DA ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int /*<<< orphan*/  dvb_ca_en50221_thread_wakeup (struct dvb_ca_private*) ; 
 int stub1 (struct dvb_ca_en50221*,int,int /*<<< orphan*/ ) ; 

void dvb_ca_en50221_frda_irq(struct dvb_ca_en50221 *pubca, int slot)
{
	struct dvb_ca_private *ca = pubca->private;
	int flags;

	dprintk("FR/DA IRQ slot:%i\n", slot);

	switch (ca->slot_info[slot].slot_state) {
	case DVB_CA_SLOTSTATE_LINKINIT:
		flags = ca->pub->read_cam_control(pubca, slot, CTRLIF_STATUS);
		if (flags & STATUSREG_DA) {
			dprintk("CAM supports DA IRQ\n");
			ca->slot_info[slot].da_irq_supported = 1;
		}
		break;

	case DVB_CA_SLOTSTATE_RUNNING:
		if (ca->open)
			dvb_ca_en50221_thread_wakeup(ca);
		break;
	}
}