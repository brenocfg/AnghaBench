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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {scalar_t__ status_word; } ;
struct TYPE_4__ {struct TYPE_4__* next; TYPE_1__ status; } ;

/* Variables and functions */
 int DMA_DONE ; 
 int DMA_ERR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  bfin_mac_rx (struct net_device*) ; 
 int bfin_read_DMA1_IRQ_STATUS () ; 
 int /*<<< orphan*/  bfin_write_DMA1_IRQ_STATUS (int) ; 
 TYPE_2__* current_rx_ptr ; 

__attribute__((used)) static irqreturn_t bfin_mac_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = dev_id;
	int number = 0;

get_one_packet:
	if (current_rx_ptr->status.status_word == 0) {
		/* no more new packet received */
		if (number == 0) {
			if (current_rx_ptr->next->status.status_word != 0) {
				current_rx_ptr = current_rx_ptr->next;
				goto real_rx;
			}
		}
		bfin_write_DMA1_IRQ_STATUS(bfin_read_DMA1_IRQ_STATUS() |
					   DMA_DONE | DMA_ERR);
		return IRQ_HANDLED;
	}

real_rx:
	bfin_mac_rx(dev);
	number++;
	goto get_one_packet;
}