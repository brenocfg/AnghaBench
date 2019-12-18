#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct tx_radiotap_hdr {scalar_t__ data_retries; } ;
struct lbs_private {scalar_t__ connect_status; scalar_t__ mesh_connect_status; scalar_t__ mesh_dev; scalar_t__ dev; TYPE_1__* currenttxskb; int /*<<< orphan*/  rtap_net_dev; scalar_t__ txretrycount; int /*<<< orphan*/  monitormode; } ;
struct TYPE_3__ {int /*<<< orphan*/  protocol; scalar_t__ data; } ;

/* Variables and functions */
 scalar_t__ LBS_CONNECTED ; 
 int /*<<< orphan*/  eth_type_trans (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_wake_queue (scalar_t__) ; 

void lbs_send_tx_feedback(struct lbs_private *priv, u32 try_count)
{
	struct tx_radiotap_hdr *radiotap_hdr;

	if (!priv->monitormode || priv->currenttxskb == NULL)
		return;

	radiotap_hdr = (struct tx_radiotap_hdr *)priv->currenttxskb->data;

	radiotap_hdr->data_retries = try_count ?
		(1 + priv->txretrycount - try_count) : 0;

	priv->currenttxskb->protocol = eth_type_trans(priv->currenttxskb,
						      priv->rtap_net_dev);
	netif_rx(priv->currenttxskb);

	priv->currenttxskb = NULL;

	if (priv->connect_status == LBS_CONNECTED)
		netif_wake_queue(priv->dev);

	if (priv->mesh_dev && (priv->mesh_connect_status == LBS_CONNECTED))
		netif_wake_queue(priv->mesh_dev);
}