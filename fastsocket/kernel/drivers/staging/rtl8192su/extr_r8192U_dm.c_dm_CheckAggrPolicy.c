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
typedef  int u8 ;
struct TYPE_5__ {int txbytesunicast; int rxbytesunicast; } ;
struct r8192_priv {TYPE_2__ stats; TYPE_1__* ieee80211; } ;
struct net_device {int /*<<< orphan*/ * TcbCountInAggrQueue; int /*<<< orphan*/ * TcbAggrQueue; } ;
struct TYPE_6__ {int IOTAction; int bCurrent_AMSDU_Support; int bCurrentAMPDUEnable; } ;
struct TYPE_4__ {TYPE_3__* pHTInfo; } ;
typedef  scalar_t__ PRT_TCB ;
typedef  TYPE_3__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 scalar_t__ DESC92S_RATE54M ; 
 int HT_IOT_ACT_AMSDU_ENABLE ; 
 int HT_IOT_ACT_HYBRID_AGGREGATION ; 
 int /*<<< orphan*/  INIMCS_SEL ; 
 size_t MAX_TX_QUEUE ; 
 int /*<<< orphan*/  PreTransmitTCB (struct net_device*,scalar_t__) ; 
 size_t QueueId ; 
 int /*<<< orphan*/  RTIsListEmpty (int /*<<< orphan*/ *) ; 
 scalar_t__ RTRemoveHeadList (int /*<<< orphan*/ *) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 scalar_t__ pTcb ; 
 scalar_t__ read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dm_CheckAggrPolicy(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	PRT_HIGH_THROUGHPUT	pHTInfo = priv->ieee80211->pHTInfo;
	//u8 			QueueId;
	//PRT_TCB			pTcb;
	bool			bAmsduEnable = false;

	static u8		lastTxOkCnt = 0;
	static u8		lastRxOkCnt = 0;
	u8			curTxOkCnt = 0;
	u8			curRxOkCnt = 0;

	// Determine if A-MSDU policy.
	if(priv->ieee80211->pHTInfo->IOTAction & HT_IOT_ACT_HYBRID_AGGREGATION)
	{
		if(read_nic_byte(dev, INIMCS_SEL) > DESC92S_RATE54M)
			bAmsduEnable = true;
	}
	else if(priv->ieee80211->pHTInfo->IOTAction & HT_IOT_ACT_AMSDU_ENABLE)
	{
		if(read_nic_byte(dev, INIMCS_SEL) > DESC92S_RATE54M)
		{
			curTxOkCnt = priv->stats.txbytesunicast - lastTxOkCnt;
			curRxOkCnt = priv->stats.rxbytesunicast - lastRxOkCnt;

			if(curRxOkCnt <= 4*curTxOkCnt)
				bAmsduEnable = true;
		}
	}
	else
	{
		// Do not need to switch aggregation policy.
		return;
	}

	// Switch A-MSDU
	if(bAmsduEnable && !pHTInfo->bCurrent_AMSDU_Support)
	{
		pHTInfo->bCurrent_AMSDU_Support = true;
	}
	else if(!bAmsduEnable && pHTInfo->bCurrent_AMSDU_Support)
	{
#ifdef TO_DO_LIST
		//PlatformAcquireSpinLock(Adapter, RT_TX_SPINLOCK);
		for(QueueId = 0; QueueId < MAX_TX_QUEUE; QueueId++)
		{
			while(!RTIsListEmpty(&dev->TcbAggrQueue[QueueId]))
			{
				pTcb = (PRT_TCB)RTRemoveHeadList(&dev->TcbAggrQueue[QueueId]);
				dev->TcbCountInAggrQueue[QueueId]--;
				PreTransmitTCB(dev, pTcb);
			}
		}
		//PlatformReleaseSpinLock(Adapter, RT_TX_SPINLOCK);
		pHTInfo->bCurrent_AMSDU_Support = false;
#endif
	}

	// Determine A-MPDU policy
	if(priv->ieee80211->pHTInfo->IOTAction & HT_IOT_ACT_AMSDU_ENABLE)
	{
		if(!bAmsduEnable)
			pHTInfo->bCurrentAMPDUEnable = true;
	}

	// Update local static variables.
	lastTxOkCnt = priv->stats.txbytesunicast;
	lastRxOkCnt = priv->stats.rxbytesunicast;
}