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
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_rx_stats {int ntotalfrag; scalar_t__ fragoffset; scalar_t__ packetlength; scalar_t__ fraglength; scalar_t__ Length; scalar_t__ RxBufShift; scalar_t__ RxDrvInfoSize; int /*<<< orphan*/ * virtual_address; } ;
struct TYPE_2__ {scalar_t__ Length; } ;
typedef  TYPE_1__ rx_desc_819x_usb ;

/* Variables and functions */
 scalar_t__ scrclng ; 

void query_rx_cmdpkt_desc_status(struct sk_buff *skb, struct ieee80211_rx_stats *stats)
{
//	rtl8192_rx_info *info = (struct rtl8192_rx_info *)skb->cb;
//	struct net_device *dev=info->dev;
//	struct r8192_priv *priv = (struct r8192_priv *)ieee80211_priv(dev);
	rx_desc_819x_usb *desc = (rx_desc_819x_usb *)skb->data;
//	rx_drvinfo_819x_usb  *driver_info;

	//
	//Get Rx Descriptor Information
	//
	stats->virtual_address = (u8*)skb->data;
	stats->Length = desc->Length;
	stats->RxDrvInfoSize = 0;
	stats->RxBufShift = 0;
	stats->packetlength = stats->Length-scrclng;
	stats->fraglength = stats->packetlength;
	stats->fragoffset = 0;
	stats->ntotalfrag = 1;
}