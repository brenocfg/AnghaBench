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
struct efx_rx_queue {scalar_t__ enabled; } ;
struct efx_channel {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 struct efx_rx_queue* efx_channel_get_rx_queue (struct efx_channel*) ; 
 scalar_t__ efx_channel_has_rx_queue (struct efx_channel*) ; 
 int /*<<< orphan*/  efx_fast_push_rx_descriptors (struct efx_rx_queue*) ; 
 int efx_nic_process_eventq (struct efx_channel*,int) ; 
 int /*<<< orphan*/  efx_rx_flush_packet (struct efx_channel*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int efx_process_channel(struct efx_channel *channel, int budget)
{
	int spent;

	if (unlikely(!channel->enabled))
		return 0;

	spent = efx_nic_process_eventq(channel, budget);
	if (spent && efx_channel_has_rx_queue(channel)) {
		struct efx_rx_queue *rx_queue =
			efx_channel_get_rx_queue(channel);

		efx_rx_flush_packet(channel);
		if (rx_queue->enabled)
			efx_fast_push_rx_descriptors(rx_queue);
	}

	return spent;
}