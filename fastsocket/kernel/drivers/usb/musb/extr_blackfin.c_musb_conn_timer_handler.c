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
typedef  int u16 ;
struct musb {int /*<<< orphan*/  lock; int /*<<< orphan*/  mregs; TYPE_2__* config; TYPE_1__* xceiv; } ;
struct TYPE_4__ {int /*<<< orphan*/  gpio_vrsel; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUSB_DEVCTL ; 
 int MUSB_DEVCTL_BDEVICE ; 
 int MUSB_DEVCTL_SESSION ; 
 int /*<<< orphan*/  MUSB_INTRUSB ; 
 int /*<<< orphan*/  MUSB_INTRUSBE ; 
 int MUSB_INTR_SUSPEND ; 
 int MUSB_INTR_VBUSERROR ; 
 int /*<<< orphan*/  MUSB_POWER ; 
 int MUSB_POWER_HSENAB ; 
#define  OTG_STATE_A_IDLE 129 
#define  OTG_STATE_A_WAIT_BCON 128 
 scalar_t__ TIMER_DELAY ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  musb_conn_timer ; 
 int musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int musb_readw (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  musb_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  otg_state_string (struct musb*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void musb_conn_timer_handler(unsigned long _musb)
{
	struct musb *musb = (void *)_musb;
	unsigned long flags;
	u16 val;

	spin_lock_irqsave(&musb->lock, flags);
	switch (musb->xceiv->state) {
	case OTG_STATE_A_IDLE:
	case OTG_STATE_A_WAIT_BCON:
		/* Start a new session */
		val = musb_readw(musb->mregs, MUSB_DEVCTL);
		val |= MUSB_DEVCTL_SESSION;
		musb_writew(musb->mregs, MUSB_DEVCTL, val);

		val = musb_readw(musb->mregs, MUSB_DEVCTL);
		if (!(val & MUSB_DEVCTL_BDEVICE)) {
			gpio_set_value(musb->config->gpio_vrsel, 1);
			musb->xceiv->state = OTG_STATE_A_WAIT_BCON;
		} else {
			gpio_set_value(musb->config->gpio_vrsel, 0);

			/* Ignore VBUSERROR and SUSPEND IRQ */
			val = musb_readb(musb->mregs, MUSB_INTRUSBE);
			val &= ~MUSB_INTR_VBUSERROR;
			musb_writeb(musb->mregs, MUSB_INTRUSBE, val);

			val = MUSB_INTR_SUSPEND | MUSB_INTR_VBUSERROR;
			musb_writeb(musb->mregs, MUSB_INTRUSB, val);

			val = MUSB_POWER_HSENAB;
			musb_writeb(musb->mregs, MUSB_POWER, val);
		}
		mod_timer(&musb_conn_timer, jiffies + TIMER_DELAY);
		break;

	default:
		DBG(1, "%s state not handled\n", otg_state_string(musb));
		break;
	}
	spin_unlock_irqrestore(&musb->lock, flags);

	DBG(4, "state is %s\n", otg_state_string(musb));
}