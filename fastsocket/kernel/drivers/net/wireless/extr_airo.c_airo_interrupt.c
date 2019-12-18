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
typedef  int u16 ;
struct net_device {struct airo_info* ml_priv; } ;
struct airo_info {TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVACK ; 
 int /*<<< orphan*/  EVINTEN ; 
 int /*<<< orphan*/  EVSTAT ; 
 int EV_AWAKE ; 
 int EV_LINK ; 
 int EV_MIC ; 
 int EV_RX ; 
 int EV_TX ; 
 int EV_TXCPY ; 
 int EV_TXEXC ; 
 int IGNORE_INTS ; 
 int IN4500 (struct airo_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  OUT4500 (struct airo_info*,int /*<<< orphan*/ ,int) ; 
 int STATUS_INTS ; 
 int /*<<< orphan*/  airo_handle_cisco_mic (struct airo_info*) ; 
 int /*<<< orphan*/  airo_handle_link (struct airo_info*) ; 
 int /*<<< orphan*/  airo_handle_rx (struct airo_info*) ; 
 int /*<<< orphan*/  airo_handle_tx (struct airo_info*,int) ; 
 int /*<<< orphan*/  airo_print_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 

__attribute__((used)) static irqreturn_t airo_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	u16 status, savedInterrupts = 0;
	struct airo_info *ai = dev->ml_priv;
	int handled = 0;

	if (!netif_device_present(dev))
		return IRQ_NONE;

	for (;;) {
		status = IN4500(ai, EVSTAT);
		if (!(status & STATUS_INTS) || (status == 0xffff))
			break;

		handled = 1;

		if (status & EV_AWAKE) {
			OUT4500(ai, EVACK, EV_AWAKE);
			OUT4500(ai, EVACK, EV_AWAKE);
		}

		if (!savedInterrupts) {
			savedInterrupts = IN4500(ai, EVINTEN);
			OUT4500(ai, EVINTEN, 0);
		}

		if (status & EV_MIC) {
			OUT4500(ai, EVACK, EV_MIC);
			airo_handle_cisco_mic(ai);
		}

		if (status & EV_LINK) {
			/* Link status changed */
			airo_handle_link(ai);
		}

		/* Check to see if there is something to receive */
		if (status & EV_RX)
			airo_handle_rx(ai);

		/* Check to see if a packet has been transmitted */
		if (status & (EV_TX | EV_TXCPY | EV_TXEXC))
			airo_handle_tx(ai, status);

		if ( status & ~STATUS_INTS & ~IGNORE_INTS ) {
			airo_print_warn(ai->dev->name, "Got weird status %x",
				status & ~STATUS_INTS & ~IGNORE_INTS );
		}
	}

	if (savedInterrupts)
		OUT4500(ai, EVINTEN, savedInterrupts);

	return IRQ_RETVAL(handled);
}