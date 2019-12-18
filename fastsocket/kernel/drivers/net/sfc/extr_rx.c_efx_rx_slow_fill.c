#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct efx_rx_queue {int /*<<< orphan*/  slow_fill_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_nic_generate_fill_event (struct efx_rx_queue*) ; 

void efx_rx_slow_fill(unsigned long context)
{
	struct efx_rx_queue *rx_queue = (struct efx_rx_queue *)context;

	/* Post an event to cause NAPI to run and refill the queue */
	efx_nic_generate_fill_event(rx_queue);
	++rx_queue->slow_fill_count;
}