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
typedef  int u32 ;
struct musb {int port1_status; int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget_driver; int /*<<< orphan*/  is_active; int /*<<< orphan*/  idle_timeout; int /*<<< orphan*/  a_wait_bcon; TYPE_1__* xceiv; } ;
struct TYPE_2__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ) ; 
#define  OTG_STATE_A_IDLE 129 
#define  OTG_STATE_A_WAIT_BCON 128 
 int TUSB_PRCM_WBUS ; 
 int TUSB_PRCM_WHOSTDISCON ; 
 int TUSB_PRCM_WID ; 
 int TUSB_PRCM_WVBUS ; 
 scalar_t__ is_host_active (struct musb*) ; 
 scalar_t__ is_otg_enabled (struct musb*) ; 
 scalar_t__ is_peripheral_enabled (struct musb*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  otg_state_string (struct musb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tusb_allow_idle (struct musb*,int) ; 
 int /*<<< orphan*/  tusb_source_power (struct musb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void musb_do_idle(unsigned long _musb)
{
	struct musb	*musb = (void *)_musb;
	unsigned long	flags;

	spin_lock_irqsave(&musb->lock, flags);

	switch (musb->xceiv->state) {
	case OTG_STATE_A_WAIT_BCON:
		if ((musb->a_wait_bcon != 0)
			&& (musb->idle_timeout == 0
				|| time_after(jiffies, musb->idle_timeout))) {
			DBG(4, "Nothing connected %s, turning off VBUS\n",
					otg_state_string(musb));
		}
		/* FALLTHROUGH */
	case OTG_STATE_A_IDLE:
		tusb_source_power(musb, 0);
	default:
		break;
	}

	if (!musb->is_active) {
		u32	wakeups;

		/* wait until khubd handles port change status */
		if (is_host_active(musb) && (musb->port1_status >> 16))
			goto done;

#ifdef CONFIG_USB_GADGET_MUSB_HDRC
		if (is_peripheral_enabled(musb) && !musb->gadget_driver)
			wakeups = 0;
		else {
			wakeups = TUSB_PRCM_WHOSTDISCON
					| TUSB_PRCM_WBUS
					| TUSB_PRCM_WVBUS;
			if (is_otg_enabled(musb))
				wakeups |= TUSB_PRCM_WID;
		}
#else
		wakeups = TUSB_PRCM_WHOSTDISCON | TUSB_PRCM_WBUS;
#endif
		tusb_allow_idle(musb, wakeups);
	}
done:
	spin_unlock_irqrestore(&musb->lock, flags);
}