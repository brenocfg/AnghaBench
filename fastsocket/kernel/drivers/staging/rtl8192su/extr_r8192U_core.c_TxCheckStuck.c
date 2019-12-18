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
typedef  size_t u8 ;
struct r8192_priv {TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * skb_aggQ; int /*<<< orphan*/ * skb_waitQ; } ;
typedef  int /*<<< orphan*/  RESET_TYPE ;

/* Variables and functions */
 size_t BEACON_QUEUE ; 
 int /*<<< orphan*/  COMP_RESET ; 
 scalar_t__ HalTxCheckStuck819xUsb (struct net_device*) ; 
 int /*<<< orphan*/  RESET_TYPE_NORESET ; 
 int /*<<< orphan*/  RESET_TYPE_SILENT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 size_t TXCMD_QUEUE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 

RESET_TYPE
TxCheckStuck(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u8			QueueID;
//	PRT_TCB			pTcb;
//	u8			ResetThreshold;
	bool			bCheckFwTxCnt = false;
	//unsigned long flags;

	//
	// Decide Stuch threshold according to current power save mode
	//

//     RT_TRACE(COMP_RESET, " ==> TxCheckStuck()\n");
//	     PlatformAcquireSpinLock(Adapter, RT_TX_SPINLOCK);
//	     spin_lock_irqsave(&priv->ieee80211->lock,flags);
	     for (QueueID = 0; QueueID<=BEACON_QUEUE;QueueID ++)
	     {
	     		if(QueueID == TXCMD_QUEUE)
		         continue;
#if 1
		     	if((skb_queue_len(&priv->ieee80211->skb_waitQ[QueueID]) == 0)  && (skb_queue_len(&priv->ieee80211->skb_aggQ[QueueID]) == 0))
			 	continue;
#endif

	             bCheckFwTxCnt = true;
	     }
//	     PlatformReleaseSpinLock(Adapter, RT_TX_SPINLOCK);
//	spin_unlock_irqrestore(&priv->ieee80211->lock,flags);
//	RT_TRACE(COMP_RESET,"bCheckFwTxCnt is %d\n",bCheckFwTxCnt);
#if 1
	if(bCheckFwTxCnt)
	{
		if(HalTxCheckStuck819xUsb(dev))
		{
			RT_TRACE(COMP_RESET, "TxCheckStuck(): Fw indicates no Tx condition! \n");
			return RESET_TYPE_SILENT;
		}
	}
#endif
	return RESET_TYPE_NORESET;
}