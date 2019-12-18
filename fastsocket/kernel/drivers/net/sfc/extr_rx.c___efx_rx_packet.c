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
typedef  int /*<<< orphan*/  u8 ;
struct efx_rx_buffer {int flags; int /*<<< orphan*/  len; } ;
struct efx_nic {int loopback_selftest; int /*<<< orphan*/  rx_checksum_enabled; } ;
struct efx_channel {int /*<<< orphan*/  rx_pkt_n_frags; TYPE_1__* type; int /*<<< orphan*/  rx_pkt_index; int /*<<< orphan*/  rx_queue; struct efx_nic* efx; } ;
struct TYPE_2__ {int /*<<< orphan*/  receive_skb; } ;

/* Variables and functions */
 int EFX_RX_PKT_CSUMMED ; 
 int EFX_RX_PKT_TCP ; 
 int /*<<< orphan*/  efx_free_rx_buffer (struct efx_rx_buffer*) ; 
 int /*<<< orphan*/  efx_loopback_rx_packet (struct efx_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * efx_rx_buf_va (struct efx_rx_buffer*) ; 
 struct efx_rx_buffer* efx_rx_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_rx_deliver (struct efx_channel*,int /*<<< orphan*/ *,struct efx_rx_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_rx_packet_gro (struct efx_channel*,struct efx_rx_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void __efx_rx_packet(struct efx_channel *channel)
{
	struct efx_nic *efx = channel->efx;
	struct efx_rx_buffer *rx_buf =
		efx_rx_buffer(&channel->rx_queue, channel->rx_pkt_index);
	u8 *eh = efx_rx_buf_va(rx_buf);

	/* If we're in loopback test, then pass the packet directly to the
	 * loopback layer, and free the rx_buf here
	 */
	if (unlikely(efx->loopback_selftest)) {
		efx_loopback_rx_packet(efx, eh, rx_buf->len);
		efx_free_rx_buffer(rx_buf);
		goto out;
	}

	if (unlikely(!efx->rx_checksum_enabled))
		rx_buf->flags &= ~EFX_RX_PKT_CSUMMED;

	if ((rx_buf->flags & EFX_RX_PKT_TCP) && !channel->type->receive_skb)
		efx_rx_packet_gro(channel, rx_buf, channel->rx_pkt_n_frags, eh);
	else
		efx_rx_deliver(channel, eh, rx_buf, channel->rx_pkt_n_frags);
out:
	channel->rx_pkt_n_frags = 0;
}