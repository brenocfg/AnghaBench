#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int* raw; } ;
struct TYPE_9__ {int length; TYPE_2__ data; int /*<<< orphan*/  command; } ;
typedef  TYPE_3__ pcb_struct ;
struct TYPE_7__ {scalar_t__ direction; } ;
struct TYPE_10__ {int hcr_val; scalar_t__ send_pcb_semaphore; int /*<<< orphan*/  lock; TYPE_1__ current_dma; scalar_t__ dmaing; } ;
typedef  TYPE_4__ elp_device ;

/* Variables and functions */
#define  ASF_PCB_ACK 129 
#define  ASF_PCB_NAK 128 
 int GET_ASF (int /*<<< orphan*/ ) ; 
 int HZ ; 
 int /*<<< orphan*/  check_3c505_dma (struct net_device*) ; 
 int elp_debug ; 
 int /*<<< orphan*/  inb_status (int /*<<< orphan*/ ) ; 
 int jiffies ; 
 TYPE_4__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  outb_command (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb_control (int,struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ send_pcb_fast (int /*<<< orphan*/ ,int) ; 
 scalar_t__ send_pcb_slow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_hsf (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_set_bit (int,scalar_t__*) ; 
 scalar_t__ time_before (int,unsigned long) ; 

__attribute__((used)) static bool send_pcb(struct net_device *dev, pcb_struct * pcb)
{
	int i;
	unsigned long timeout;
	elp_device *adapter = netdev_priv(dev);
	unsigned long flags;

	check_3c505_dma(dev);

	if (adapter->dmaing && adapter->current_dma.direction == 0)
		return false;

	/* Avoid contention */
	if (test_and_set_bit(1, &adapter->send_pcb_semaphore)) {
		if (elp_debug >= 3) {
			pr_debug("%s: send_pcb entered while threaded\n", dev->name);
		}
		return false;
	}
	/*
	 * load each byte into the command register and
	 * wait for the HCRE bit to indicate the adapter
	 * had read the byte
	 */
	set_hsf(dev, 0);

	if (send_pcb_slow(dev->base_addr, pcb->command))
		goto abort;

	spin_lock_irqsave(&adapter->lock, flags);

	if (send_pcb_fast(dev->base_addr, pcb->length))
		goto sti_abort;

	for (i = 0; i < pcb->length; i++) {
		if (send_pcb_fast(dev->base_addr, pcb->data.raw[i]))
			goto sti_abort;
	}

	outb_control(adapter->hcr_val | 3, dev);	/* signal end of PCB */
	outb_command(2 + pcb->length, dev->base_addr);

	/* now wait for the acknowledgement */
	spin_unlock_irqrestore(&adapter->lock, flags);

	for (timeout = jiffies + 5*HZ/100; time_before(jiffies, timeout);) {
		switch (GET_ASF(dev->base_addr)) {
		case ASF_PCB_ACK:
			adapter->send_pcb_semaphore = 0;
			return true;

		case ASF_PCB_NAK:
#ifdef ELP_DEBUG
			pr_debug("%s: send_pcb got NAK\n", dev->name);
#endif
			goto abort;
		}
	}

	if (elp_debug >= 1)
		pr_debug("%s: timeout waiting for PCB acknowledge (status %02x)\n",
			dev->name, inb_status(dev->base_addr));
	goto abort;

      sti_abort:
	spin_unlock_irqrestore(&adapter->lock, flags);
      abort:
	adapter->send_pcb_semaphore = 0;
	return false;
}