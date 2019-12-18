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
struct TYPE_5__ {TYPE_2__ RxAdmittedBARecord; } ;
typedef  TYPE_1__* PRX_TS_RECORD ;
typedef  TYPE_2__* PBA_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  DeActivateBAEntry (struct ieee80211_device*,TYPE_2__*) ; 

u8 RxTsDeleteBA( struct ieee80211_device* ieee, PRX_TS_RECORD	pRxTs)
{
	PBA_RECORD		pBa = &pRxTs->RxAdmittedBARecord;
	u8			bSendDELBA = false;

	if(pBa->bValid)
	{
		DeActivateBAEntry(ieee, pBa);
		bSendDELBA = true;
	}

	return bSendDELBA;
}