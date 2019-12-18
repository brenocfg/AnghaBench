#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct urb {scalar_t__ status; scalar_t__ context; } ;
struct sk_buff {scalar_t__ len; scalar_t__ cb; } ;
struct TYPE_7__ {int /*<<< orphan*/  txbytesunicast; int /*<<< orphan*/  txoktotal; } ;
struct r8192_priv {TYPE_5__* ieee80211; int /*<<< orphan*/ * tx_pending; TYPE_2__ stats; } ;
struct net_device {int dummy; } ;
struct TYPE_9__ {size_t queue_index; } ;
typedef  TYPE_4__ cb_desc ;
struct TYPE_8__ {int /*<<< orphan*/  tx_errors; } ;
struct TYPE_6__ {int /*<<< orphan*/  NumTxOkInPeriod; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* softmac_hard_start_xmit ) (struct sk_buff*,struct net_device*) ;int /*<<< orphan*/ * skb_waitQ; int /*<<< orphan*/  queue_stop; scalar_t__ ack_tx_to_ieee; TYPE_3__ stats; scalar_t__ tx_headroom; TYPE_1__ LinkDetectInfo; } ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 scalar_t__ MAX_DEV_ADDR_SIZE ; 
 size_t MGNT_QUEUE ; 
 scalar_t__ TXCMD_QUEUE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  ieee80211_ps_tx_ack (TYPE_5__*,int) ; 
 int /*<<< orphan*/  memcpy (struct net_device**,struct net_device*,int) ; 
 scalar_t__ rtl8192_is_tx_queue_empty (struct net_device*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  usb_free_urb (struct urb*) ; 

__attribute__((used)) static void rtl8192_tx_isr(struct urb *tx_urb)
{
	struct sk_buff *skb = (struct sk_buff*)tx_urb->context;
	struct net_device *dev = NULL;
	struct r8192_priv *priv = NULL;
	cb_desc *tcb_desc = (cb_desc *)(skb->cb + MAX_DEV_ADDR_SIZE);
	u8  queue_index = tcb_desc->queue_index;
//	bool bToSend0Byte;
//	u16 BufLen = skb->len;

	memcpy(&dev,(struct net_device*)(skb->cb),sizeof(struct net_device*));
	priv = ieee80211_priv(dev);

	if(tcb_desc->queue_index != TXCMD_QUEUE) {
		if(tx_urb->status == 0) {
		//	dev->trans_start = jiffies;
			// As act as station mode, destion shall be  unicast address.
			//priv->ieee80211->stats.tx_bytes+=(skb->len - priv->ieee80211->tx_headroom);
			//priv->ieee80211->stats.tx_packets++;
			priv->stats.txoktotal++;
			priv->ieee80211->LinkDetectInfo.NumTxOkInPeriod++;
			priv->stats.txbytesunicast += (skb->len - priv->ieee80211->tx_headroom);
		} else {
			priv->ieee80211->stats.tx_errors++;
			//priv->stats.txmanageerr++;
			/* TODO */
		}
	}

	/* free skb and tx_urb */
	if(skb != NULL) {
		dev_kfree_skb_any(skb);
		usb_free_urb(tx_urb);
		atomic_dec(&priv->tx_pending[queue_index]);
	}

	{
		//
		// Handle HW Beacon:
		// We had transfer our beacon frame to host controler at this moment.
		//
		//
		// Caution:
		// Handling the wait queue of command packets.
		// For Tx command packets, we must not do TCB fragment because it is not handled right now.
		// We must cut the packets to match the size of TX_CMD_PKT before we send it.
		//
	if (queue_index == MGNT_QUEUE){
        if (priv->ieee80211->ack_tx_to_ieee){
            if (rtl8192_is_tx_queue_empty(dev)){
                priv->ieee80211->ack_tx_to_ieee = 0;
                ieee80211_ps_tx_ack(priv->ieee80211, 1);
            }
        }
    }
		/* Handle MPDU in wait queue. */
		if(queue_index != BEACON_QUEUE) {
			/* Don't send data frame during scanning.*/
			if((skb_queue_len(&priv->ieee80211->skb_waitQ[queue_index]) != 0)&&\
					(!(priv->ieee80211->queue_stop))) {
				if(NULL != (skb = skb_dequeue(&(priv->ieee80211->skb_waitQ[queue_index]))))
					priv->ieee80211->softmac_hard_start_xmit(skb, dev);

				return; //modified by david to avoid further processing AMSDU
			}
		}
	}
}