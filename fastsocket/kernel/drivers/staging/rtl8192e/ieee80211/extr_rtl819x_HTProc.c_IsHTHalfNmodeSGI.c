#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  (* GetHalfNmodeSupportByAPsHandler ) (int /*<<< orphan*/ ) ;TYPE_1__* pHTInfo; } ;
struct TYPE_4__ {scalar_t__ ShortGI20Mhz; scalar_t__ ShortGI40Mhz; } ;
struct TYPE_3__ {int bCurrentHTSupport; scalar_t__ PeerHTCapBuf; } ;
typedef  TYPE_1__* PRT_HIGH_THROUGHPUT ;
typedef  TYPE_2__* PHT_CAPABILITY_ELE ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

bool IsHTHalfNmodeSGI(struct ieee80211_device* ieee, bool is40MHz)
{
	bool			retValue = false;
	PRT_HIGH_THROUGHPUT	 pHTInfo = ieee->pHTInfo;

	if(pHTInfo->bCurrentHTSupport == false )	// wireless is n mode
		retValue = false;
	else if(!ieee->GetHalfNmodeSupportByAPsHandler(ieee->dev)) 	// station in half n mode
		retValue = false;
	else if(is40MHz) // ap support 40 bw
	{
		if(((PHT_CAPABILITY_ELE)(pHTInfo->PeerHTCapBuf))->ShortGI40Mhz) // ap support 40 bw short GI
			retValue = true;
		else
			retValue = false;
	}
	else
	{
		if(((PHT_CAPABILITY_ELE)(pHTInfo->PeerHTCapBuf))->ShortGI20Mhz) // ap support 40 bw short GI
			retValue = true;
		else
			retValue = false;
	}

	return retValue;
}