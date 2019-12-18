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
struct bas_cardstate {int pending; int basstate; int /*<<< orphan*/  lock; int /*<<< orphan*/  timer_ctrl; TYPE_1__* interface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BS_ATOPEN ; 
 int BS_B1OPEN ; 
 int BS_B2OPEN ; 
 int BS_RESETTING ; 
#define  HD_CLOSE_ATCHANNEL 135 
#define  HD_CLOSE_B1CHANNEL 134 
#define  HD_CLOSE_B2CHANNEL 133 
#define  HD_DEVICE_INIT_ACK 132 
#define  HD_OPEN_ATCHANNEL 131 
#define  HD_OPEN_B1CHANNEL 130 
#define  HD_OPEN_B2CHANNEL 129 
#define  HD_RESET_INTERRUPT_PIPE 128 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void check_pending(struct bas_cardstate *ucs)
{
	unsigned long flags;

	spin_lock_irqsave(&ucs->lock, flags);
	switch (ucs->pending) {
	case 0:
		break;
	case HD_OPEN_ATCHANNEL:
		if (ucs->basstate & BS_ATOPEN)
			ucs->pending = 0;
		break;
	case HD_OPEN_B1CHANNEL:
		if (ucs->basstate & BS_B1OPEN)
			ucs->pending = 0;
		break;
	case HD_OPEN_B2CHANNEL:
		if (ucs->basstate & BS_B2OPEN)
			ucs->pending = 0;
		break;
	case HD_CLOSE_ATCHANNEL:
		if (!(ucs->basstate & BS_ATOPEN))
			ucs->pending = 0;
		break;
	case HD_CLOSE_B1CHANNEL:
		if (!(ucs->basstate & BS_B1OPEN))
			ucs->pending = 0;
		break;
	case HD_CLOSE_B2CHANNEL:
		if (!(ucs->basstate & BS_B2OPEN))
			ucs->pending = 0;
		break;
	case HD_DEVICE_INIT_ACK:		/* no reply expected */
		ucs->pending = 0;
		break;
	case HD_RESET_INTERRUPT_PIPE:
		if (!(ucs->basstate & BS_RESETTING))
			ucs->pending = 0;
		break;
	/*
	 * HD_READ_ATMESSAGE and HD_WRITE_ATMESSAGE are handled separately
	 * and should never end up here
	 */
	default:
		dev_warn(&ucs->interface->dev,
			 "unknown pending request 0x%02x cleared\n",
			 ucs->pending);
		ucs->pending = 0;
	}

	if (!ucs->pending)
		del_timer(&ucs->timer_ctrl);

	spin_unlock_irqrestore(&ucs->lock, flags);
}