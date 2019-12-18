#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct net_local {int /*<<< orphan*/  led_lock; } ;
struct TYPE_4__ {int sw_len; int ctrl; int /*<<< orphan*/  buf; } ;
struct TYPE_5__ {TYPE_1__ descr; } ;

/* Variables and functions */
 int /*<<< orphan*/  D (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  IO_STATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NETWORK_ACTIVITY ; 
 scalar_t__ NET_FLASH_TIME ; 
 int /*<<< orphan*/ * R_DMA_CH0_CMD ; 
 int /*<<< orphan*/  clear_led_timer ; 
 int /*<<< orphan*/  cmd ; 
 int d_eol ; 
 int d_eop ; 
 int d_wait ; 
 int /*<<< orphan*/  e100_set_network_leds (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int led_active ; 
 scalar_t__ led_next_time ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* myLastTxDesc ; 
 TYPE_2__* myNextTxDesc ; 
 int /*<<< orphan*/  printk (char*,char*,int) ; 
 int /*<<< orphan*/  restart ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  virt_to_phys (char*) ; 

void
e100_hardware_send_packet(struct net_local *np, char *buf, int length)
{
	D(printk("e100 send pack, buf 0x%x len %d\n", buf, length));

	spin_lock(&np->led_lock);
	if (!led_active && time_after(jiffies, led_next_time)) {
		/* light the network leds depending on the current speed. */
		e100_set_network_leds(NETWORK_ACTIVITY);

		/* Set the earliest time we may clear the LED */
		led_next_time = jiffies + NET_FLASH_TIME;
		led_active = 1;
		mod_timer(&clear_led_timer, jiffies + HZ/10);
	}
	spin_unlock(&np->led_lock);

	/* configure the tx dma descriptor */
	myNextTxDesc->descr.sw_len = length;
	myNextTxDesc->descr.ctrl = d_eop | d_eol | d_wait;
	myNextTxDesc->descr.buf = virt_to_phys(buf);

        /* Move end of list */
        myLastTxDesc->descr.ctrl &= ~d_eol;
        myLastTxDesc = myNextTxDesc;

	/* Restart DMA channel */
	*R_DMA_CH0_CMD = IO_STATE(R_DMA_CH0_CMD, cmd, restart);
}