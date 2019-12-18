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
struct efx_rx_queue {int dummy; } ;
struct efx_rx_buffer {int dummy; } ;
struct efx_channel {int dummy; } ;

/* Variables and functions */
 struct efx_rx_queue* efx_channel_get_rx_queue (struct efx_channel*) ; 
 int /*<<< orphan*/  efx_recycle_rx_page (struct efx_channel*,struct efx_rx_buffer*) ; 
 struct efx_rx_buffer* efx_rx_buf_next (struct efx_rx_queue*,struct efx_rx_buffer*) ; 

__attribute__((used)) static void efx_recycle_rx_pages(struct efx_channel *channel,
				 struct efx_rx_buffer *rx_buf,
				 unsigned int n_frags)
{
	struct efx_rx_queue *rx_queue = efx_channel_get_rx_queue(channel);

	do {
		efx_recycle_rx_page(channel, rx_buf);
		rx_buf = efx_rx_buf_next(rx_queue, rx_buf);
	} while (--n_frags);
}