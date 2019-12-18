#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct udc {scalar_t__ data_ep_queued; int /*<<< orphan*/  data_ep_enabled; } ;
struct TYPE_4__ {scalar_t__ expires; } ;

/* Variables and functions */
 int HZ ; 
 int UDC_RDE_TIMER_DIV ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int set_rde ; 
 int /*<<< orphan*/  stop_timer ; 
 int /*<<< orphan*/  timer_pending (TYPE_1__*) ; 
 int /*<<< orphan*/  udc_set_rde (struct udc*) ; 
 TYPE_1__ udc_timer ; 
 scalar_t__ use_dma ; 

__attribute__((used)) static void udc_ep0_set_rde(struct udc *dev)
{
	if (use_dma) {
		/*
		 * only enable RXDMA when no data endpoint enabled
		 * or data is queued
		 */
		if (!dev->data_ep_enabled || dev->data_ep_queued) {
			udc_set_rde(dev);
		} else {
			/*
			 * setup timer for enabling RDE (to not enable
			 * RXFIFO DMA for data endpoints to early)
			 */
			if (set_rde != 0 && !timer_pending(&udc_timer)) {
				udc_timer.expires =
					jiffies + HZ/UDC_RDE_TIMER_DIV;
				set_rde = 1;
				if (!stop_timer) {
					add_timer(&udc_timer);
				}
			}
		}
	}
}