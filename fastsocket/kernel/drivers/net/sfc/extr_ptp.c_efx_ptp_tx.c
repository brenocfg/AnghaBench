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
struct sk_buff {scalar_t__ len; } ;
struct efx_ptp_data {int /*<<< orphan*/  work; int /*<<< orphan*/  workwq; int /*<<< orphan*/  txq; } ;
struct efx_nic {struct efx_ptp_data* ptp_data; } ;
struct TYPE_4__ {int in_progress; } ;
struct TYPE_3__ {scalar_t__ dest; } ;

/* Variables and functions */
 scalar_t__ MC_CMD_PTP_IN_TRANSMIT_PACKET_MAXNUM ; 
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  PTP_EVENT_PORT ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 TYPE_2__* skb_tx (struct sk_buff*) ; 
 TYPE_1__* udp_hdr (struct sk_buff*) ; 

int efx_ptp_tx(struct efx_nic *efx, struct sk_buff *skb)
{
	struct efx_ptp_data *ptp = efx->ptp_data;

	skb_queue_tail(&ptp->txq, skb);

	if ((udp_hdr(skb)->dest == htons(PTP_EVENT_PORT)) &&
	    (skb->len <= MC_CMD_PTP_IN_TRANSMIT_PACKET_MAXNUM))
		skb_tx(skb)->in_progress = 1;
	queue_work(ptp->workwq, &ptp->work);

	return NETDEV_TX_OK;
}