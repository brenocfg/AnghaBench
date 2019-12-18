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
struct urb {int /*<<< orphan*/  dev; struct ti_port* context; int /*<<< orphan*/  complete; } ;
struct tty_struct {int dummy; } ;
struct ti_port {scalar_t__ tp_read_urb_state; int /*<<< orphan*/  tp_lock; TYPE_2__* tp_port; } ;
struct TYPE_4__ {TYPE_1__* serial; struct urb* read_urb; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* TI_READ_URB_RUNNING ; 
 scalar_t__ TI_READ_URB_STOPPED ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ti_bulk_in_callback ; 
 int usb_submit_urb (struct urb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_restart_read(struct ti_port *tport, struct tty_struct *tty)
{
	struct urb *urb;
	int status = 0;
	unsigned long flags;

	spin_lock_irqsave(&tport->tp_lock, flags);

	if (tport->tp_read_urb_state == TI_READ_URB_STOPPED) {
		tport->tp_read_urb_state = TI_READ_URB_RUNNING;
		urb = tport->tp_port->read_urb;
		spin_unlock_irqrestore(&tport->tp_lock, flags);
		urb->complete = ti_bulk_in_callback;
		urb->context = tport;
		urb->dev = tport->tp_port->serial->dev;
		status = usb_submit_urb(urb, GFP_KERNEL);
	} else  {
		tport->tp_read_urb_state = TI_READ_URB_RUNNING;
		spin_unlock_irqrestore(&tport->tp_lock, flags);
	}

	return status;
}