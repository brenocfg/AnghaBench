#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ieee80211_device {int dummy; } ;
struct TYPE_6__ {scalar_t__ bValid; } ;
struct TYPE_5__ {TYPE_2__ TxPendingBARecord; TYPE_2__ TxAdmittedBARecord; } ;
typedef  TYPE_1__* PTX_TS_RECORD ;
typedef  TYPE_2__* PBA_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeActivateBAEntry (struct ieee80211_device*,TYPE_2__*) ; 

u8 TxTsDeleteBA( struct ieee80211_device* ieee, PTX_TS_RECORD	pTxTs)
{
	PBA_RECORD		pAdmittedBa = &pTxTs->TxAdmittedBARecord;  //These two BA entries must exist in TS structure
	PBA_RECORD		pPendingBa = &pTxTs->TxPendingBARecord;
	u8			bSendDELBA = false;

	// Delete pending BA
	if(pPendingBa->bValid)
	{
		DeActivateBAEntry(ieee, pPendingBa);
		bSendDELBA = true;
	}

	// Delete admitted BA
	if(pAdmittedBa->bValid)
	{
		DeActivateBAEntry(ieee, pAdmittedBa);
		bSendDELBA = true;
	}

	return bSendDELBA;
}