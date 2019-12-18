#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  priority; scalar_t__ data; } ;
struct ieee80211_hdr_1addr {int /*<<< orphan*/  addr1; } ;
struct ieee80211_device {scalar_t__ pairwise_key_type; scalar_t__ iw_mode; scalar_t__ wpa_ie_len; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* GetNmodeSupportBySecCfg ) (int /*<<< orphan*/ ) ;TYPE_7__* pHTInfo; } ;
struct TYPE_17__ {int bAMPDUEnable; int /*<<< orphan*/  ampdu_factor; int /*<<< orphan*/  ampdu_density; } ;
typedef  TYPE_5__ cb_desc ;
struct TYPE_21__ {int PacketLength; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* GetNmodeSupportBySecCfgHandler ) (TYPE_8__*) ;} ;
struct TYPE_20__ {TYPE_1__ HalFunc; } ;
struct TYPE_19__ {int IOTAction; int ForcedAMPDUMode; int /*<<< orphan*/  ForcedAMPDUFactor; int /*<<< orphan*/  ForcedMPDUDensity; int /*<<< orphan*/  CurrentMPDUDensity; int /*<<< orphan*/  CurrentAMPDUFactor; scalar_t__ bCurrentAMPDUEnable; int /*<<< orphan*/  bEnableHT; int /*<<< orphan*/  bCurrentHTSupport; } ;
struct TYPE_14__ {int /*<<< orphan*/  SeqNum; } ;
struct TYPE_15__ {TYPE_2__ field; } ;
struct TYPE_16__ {int bValid; TYPE_3__ BaStartSeqCtrl; } ;
struct TYPE_18__ {int bUsingBa; int TxCurSeq; TYPE_4__ TxAdmittedBARecord; } ;
typedef  TYPE_6__* PTX_TS_RECORD ;
typedef  int /*<<< orphan*/  PTS_COMMON_INFO ;
typedef  TYPE_7__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 TYPE_8__* Adapter ; 
 int /*<<< orphan*/  GetTs (struct ieee80211_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  HT_AGG_AUTO 130 
#define  HT_AGG_FORCE_DISABLE 129 
#define  HT_AGG_FORCE_ENABLE 128 
 int HT_IOT_ACT_TX_NO_AGGREGATION ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  IsQoSDataFrame (scalar_t__) ; 
 scalar_t__ KEY_TYPE_NA ; 
 scalar_t__ SN_LESS (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TX_DIR ; 
 int /*<<< orphan*/  TsStartAddBaProcess (struct ieee80211_device*,TYPE_6__*) ; 
 scalar_t__ is_broadcast_ether_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ is_multicast_ether_addr (int /*<<< orphan*/ ) ; 
 TYPE_9__* pTcb ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_8__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

void ieee80211_tx_query_agg_cap(struct ieee80211_device* ieee, struct sk_buff* skb, cb_desc* tcb_desc)
{
	PRT_HIGH_THROUGHPUT	pHTInfo = ieee->pHTInfo;
	PTX_TS_RECORD			pTxTs = NULL;
	struct ieee80211_hdr_1addr* hdr = (struct ieee80211_hdr_1addr*)skb->data;

	if (!pHTInfo->bCurrentHTSupport||!pHTInfo->bEnableHT)
		return;
	if (!IsQoSDataFrame(skb->data))
		return;

	if (is_multicast_ether_addr(hdr->addr1) || is_broadcast_ether_addr(hdr->addr1))
		return;
	//check packet and mode later
#ifdef TO_DO_LIST
	if(pTcb->PacketLength >= 4096)
		return;
	// For RTL819X, if pairwisekey = wep/tkip, we don't aggrregation.
	if(!Adapter->HalFunc.GetNmodeSupportBySecCfgHandler(Adapter))
		return;
#endif

	if(pHTInfo->IOTAction & HT_IOT_ACT_TX_NO_AGGREGATION)
		return;

#if 1
	if(!ieee->GetNmodeSupportBySecCfg(ieee->dev))
	{
		return;
	}
#endif
	if(pHTInfo->bCurrentAMPDUEnable)
	{
		if (!GetTs(ieee, (PTS_COMMON_INFO*)(&pTxTs), hdr->addr1, skb->priority, TX_DIR, true))
		{
			printk("===>can't get TS\n");
			return;
		}
		if (pTxTs->TxAdmittedBARecord.bValid == false)
		{
			//as some AP will refuse our action frame until key handshake has been finished. WB
			if (ieee->wpa_ie_len && (ieee->pairwise_key_type == KEY_TYPE_NA))
			;
			else
			TsStartAddBaProcess(ieee, pTxTs);
			goto FORCED_AGG_SETTING;
		}
		else if (pTxTs->bUsingBa == false)
		{
			if (SN_LESS(pTxTs->TxAdmittedBARecord.BaStartSeqCtrl.field.SeqNum, (pTxTs->TxCurSeq+1)%4096))
				pTxTs->bUsingBa = true;
			else
				goto FORCED_AGG_SETTING;
		}

		if (ieee->iw_mode == IW_MODE_INFRA)
		{
			tcb_desc->bAMPDUEnable = true;
			tcb_desc->ampdu_factor = pHTInfo->CurrentAMPDUFactor;
			tcb_desc->ampdu_density = pHTInfo->CurrentMPDUDensity;
		}
	}
FORCED_AGG_SETTING:
	switch(pHTInfo->ForcedAMPDUMode )
	{
		case HT_AGG_AUTO:
			break;

		case HT_AGG_FORCE_ENABLE:
			tcb_desc->bAMPDUEnable = true;
			tcb_desc->ampdu_density = pHTInfo->ForcedMPDUDensity;
			tcb_desc->ampdu_factor = pHTInfo->ForcedAMPDUFactor;
			break;

		case HT_AGG_FORCE_DISABLE:
			tcb_desc->bAMPDUEnable = false;
			tcb_desc->ampdu_density = 0;
			tcb_desc->ampdu_factor = 0;
			break;

	}
		return;
}