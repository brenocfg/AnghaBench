#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ len; scalar_t__ protocol; } ;
struct efx_nic {TYPE_1__* ptp_data; } ;
struct TYPE_6__ {scalar_t__ protocol; } ;
struct TYPE_5__ {scalar_t__ dest; } ;
struct TYPE_4__ {scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ MC_CMD_PTP_IN_TRANSMIT_PACKET_MAXNUM ; 
 int /*<<< orphan*/  PTP_EVENT_PORT ; 
 scalar_t__ PTP_MIN_LENGTH ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 TYPE_2__* udp_hdr (struct sk_buff*) ; 

bool efx_ptp_is_ptp_tx(struct efx_nic *efx, struct sk_buff *skb)
{
	return efx->ptp_data &&
		efx->ptp_data->enabled &&
		skb->len >= PTP_MIN_LENGTH &&
		skb->len <= MC_CMD_PTP_IN_TRANSMIT_PACKET_MAXNUM &&
		likely(skb->protocol == htons(ETH_P_IP)) &&
		ip_hdr(skb)->protocol == IPPROTO_UDP &&
		udp_hdr(skb)->dest == htons(PTP_EVENT_PORT);
}