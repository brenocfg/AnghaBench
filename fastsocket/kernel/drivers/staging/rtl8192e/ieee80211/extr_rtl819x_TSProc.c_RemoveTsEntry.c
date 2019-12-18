#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_rxb {int nr_subframes; int /*<<< orphan*/ * subframes; } ;
struct ieee80211_device {int /*<<< orphan*/  reorder_spinlock; int /*<<< orphan*/  RxReorder_Unused_List; } ;
struct TYPE_12__ {int /*<<< orphan*/  prev; } ;
struct TYPE_11__ {int /*<<< orphan*/  List; struct ieee80211_rxb* prxb; } ;
struct TYPE_10__ {TYPE_5__ RxPendingPktList; int /*<<< orphan*/  RxPktPendingTimer; } ;
struct TYPE_9__ {int /*<<< orphan*/  InactTimer; int /*<<< orphan*/  SetupTimer; } ;
struct TYPE_8__ {int /*<<< orphan*/  TsAddBaTimer; } ;
typedef  scalar_t__ TR_SELECT ;
typedef  TYPE_1__* PTX_TS_RECORD ;
typedef  TYPE_2__* PTS_COMMON_INFO ;
typedef  TYPE_3__* PRX_TS_RECORD ;
typedef  TYPE_4__* PRX_REORDER_ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  List ; 
 scalar_t__ RX_DIR ; 
 int /*<<< orphan*/  RX_REORDER_ENTRY ; 
 int /*<<< orphan*/  TsInitDelBA (struct ieee80211_device*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_rxb*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (TYPE_5__*) ; 
 scalar_t__ list_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void RemoveTsEntry(
	struct ieee80211_device*	ieee,
	PTS_COMMON_INFO			pTs,
	TR_SELECT			TxRxSelect
	)
{
	//u32 flags = 0;
	unsigned long flags = 0;
	del_timer_sync(&pTs->SetupTimer);
	del_timer_sync(&pTs->InactTimer);
	TsInitDelBA(ieee, pTs, TxRxSelect);

	if(TxRxSelect == RX_DIR)
	{
//#ifdef TO_DO_LIST
		PRX_REORDER_ENTRY	pRxReorderEntry;
		PRX_TS_RECORD 		pRxTS = (PRX_TS_RECORD)pTs;
		if(timer_pending(&pRxTS->RxPktPendingTimer))
			del_timer_sync(&pRxTS->RxPktPendingTimer);

                while(!list_empty(&pRxTS->RxPendingPktList))
                {
                //      PlatformAcquireSpinLock(Adapter, RT_RX_SPINLOCK);
                        spin_lock_irqsave(&(ieee->reorder_spinlock), flags);
                        //pRxReorderEntry = list_entry(&pRxTS->RxPendingPktList.prev,RX_REORDER_ENTRY,List);
			pRxReorderEntry = (PRX_REORDER_ENTRY)list_entry(pRxTS->RxPendingPktList.prev,RX_REORDER_ENTRY,List);
                        list_del_init(&pRxReorderEntry->List);
                        {
                                int i = 0;
                                struct ieee80211_rxb * prxb = pRxReorderEntry->prxb;
				if (unlikely(!prxb))
				{
					spin_unlock_irqrestore(&(ieee->reorder_spinlock), flags);
					return;
				}
                                for(i =0; i < prxb->nr_subframes; i++) {
                                        dev_kfree_skb(prxb->subframes[i]);
                                }
                                kfree(prxb);
                                prxb = NULL;
                        }
                        list_add_tail(&pRxReorderEntry->List,&ieee->RxReorder_Unused_List);
                        //PlatformReleaseSpinLock(Adapter, RT_RX_SPINLOCK);
                        spin_unlock_irqrestore(&(ieee->reorder_spinlock), flags);
                }

//#endif
	}
	else
	{
		PTX_TS_RECORD pTxTS = (PTX_TS_RECORD)pTs;
		del_timer_sync(&pTxTS->TsAddBaTimer);
	}
}