#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
struct ieee80211_device {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  ucTSID; } ;
struct TYPE_19__ {TYPE_1__ field; } ;
struct TYPE_20__ {TYPE_2__ TSInfo; } ;
struct TYPE_21__ {TYPE_3__ f; } ;
struct TYPE_26__ {int /*<<< orphan*/  Addr; TYPE_4__ TSpec; } ;
struct TYPE_24__ {int SeqNum; } ;
struct TYPE_25__ {TYPE_7__ field; } ;
struct TYPE_22__ {int BAPolicy; int BufferSize; int /*<<< orphan*/  TID; scalar_t__ AMSDU_Support; } ;
struct TYPE_23__ {TYPE_5__ field; } ;
struct TYPE_17__ {int bValid; TYPE_8__ BaStartSeqCtrl; scalar_t__ BaTimeoutValue; TYPE_6__ BaParamSet; int /*<<< orphan*/  DialogToken; } ;
struct TYPE_16__ {int TxCurSeq; TYPE_9__ TsCommonInfo; TYPE_11__ TxPendingBARecord; } ;
typedef  TYPE_10__* PTX_TS_RECORD ;
typedef  TYPE_11__* PBA_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  ActivateBAEntry (struct ieee80211_device*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BA_SETUP_TIMEOUT ; 
 int /*<<< orphan*/  DeActivateBAEntry (struct ieee80211_device*,TYPE_11__*) ; 
 int /*<<< orphan*/  ieee80211_send_ADDBAReq (struct ieee80211_device*,int /*<<< orphan*/ ,TYPE_11__*) ; 

void
TsInitAddBA(
	struct ieee80211_device* ieee,
	PTX_TS_RECORD	pTS,
	u8		Policy,
	u8		bOverwritePending
	)
{
	PBA_RECORD			pBA = &pTS->TxPendingBARecord;

	if(pBA->bValid==true && bOverwritePending==false)
		return;

	// Set parameters to "Pending" variable set
	DeActivateBAEntry(ieee, pBA);

	pBA->DialogToken++;						// DialogToken: Only keep the latest dialog token
	pBA->BaParamSet.field.AMSDU_Support = 0;	// Do not support A-MSDU with A-MPDU now!!
	pBA->BaParamSet.field.BAPolicy = Policy;	// Policy: Delayed or Immediate
	pBA->BaParamSet.field.TID = pTS->TsCommonInfo.TSpec.f.TSInfo.field.ucTSID;	// TID
	// BufferSize: This need to be set according to A-MPDU vector
	pBA->BaParamSet.field.BufferSize = 32;		// BufferSize: This need to be set according to A-MPDU vector
	pBA->BaTimeoutValue = 0;					// Timeout value: Set 0 to disable Timer
	pBA->BaStartSeqCtrl.field.SeqNum = (pTS->TxCurSeq + 3) % 4096; 	// Block Ack will start after 3 packets later.

	ActivateBAEntry(ieee, pBA, BA_SETUP_TIMEOUT);

	ieee80211_send_ADDBAReq(ieee, pTS->TsCommonInfo.Addr, pBA);
}