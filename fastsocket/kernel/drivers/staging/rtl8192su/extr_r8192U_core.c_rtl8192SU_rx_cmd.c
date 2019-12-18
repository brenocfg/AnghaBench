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
struct sk_buff {int len; scalar_t__ cb; } ;
struct rtl8192_rx_info {struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct ieee80211_rx_stats {int noise; int /*<<< orphan*/  freq; int /*<<< orphan*/  rate; int /*<<< orphan*/  signal; } ;
typedef  int /*<<< orphan*/  rx_desc_819x_usb ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RECV ; 
 int /*<<< orphan*/  IEEE80211_24GHZ_BAND ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int RX_URB_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  query_rx_cmdpkt_desc_status (struct sk_buff*,struct ieee80211_rx_stats*) ; 
 int /*<<< orphan*/  rtl819xusb_process_received_packet (struct net_device*,struct ieee80211_rx_stats*) ; 

void rtl8192SU_rx_cmd(struct sk_buff *skb)
{
	struct rtl8192_rx_info *info = (struct rtl8192_rx_info *)skb->cb;
	struct net_device *dev = info->dev;

	/* TODO */
	struct ieee80211_rx_stats stats = {
		.signal = 0,
		.noise = -98,
		.rate = 0,
		//      .mac_time = jiffies,
		.freq = IEEE80211_24GHZ_BAND,
	};

	//
	// Check buffer length to determine if this is a valid MPDU.
	//
	if( (skb->len >= sizeof(rx_desc_819x_usb)) && (skb->len <= RX_URB_SIZE) )//&&
		//(pHalData->SwChnlInProgress == FALSE))
	{
		//
		// Collection information in Rx descriptor.
		//
		query_rx_cmdpkt_desc_status(skb,&stats);
		// this is to be done by amy 080508     prfd->queue_id = 1;

		//
		// Process the MPDU recevied.
		//
		rtl819xusb_process_received_packet(dev,&stats);

		dev_kfree_skb_any(skb);
	}
	else
	{
		//RTInsertTailListWithCnt(&pAdapter->RfdIdleQueue, &pRfd->List, &pAdapter->NumIdleRfd);
		//RT_ASSERT(pAdapter->NumIdleRfd <= pAdapter->NumRfd, ("HalUsbInCommandComplete8192SUsb(): Adapter->NumIdleRfd(%d)\n", pAdapter->NumIdleRfd));
		//RT_TRACE(COMP_RECV, DBG_LOUD, ("HalUsbInCommandComplete8192SUsb(): NOT enough Resources!! BufLenUsed(%d), NumIdleRfd(%d)\n",
			//pContext->BufLenUsed, pAdapter->NumIdleRfd));
	}

	//
	// Reuse USB_IN_CONTEXT since we had finished processing the
	// buffer in USB_IN_CONTEXT.
	//
	//HalUsbReturnInContext(pAdapter, pContext);

	//
	// Issue another bulk IN transfer.
	//
	//HalUsbInMpdu(pAdapter, PipeIndex);

	RT_TRACE(COMP_RECV, "<--- HalUsbInCommandComplete8192SUsb()\n");

}