#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct sk_buff {scalar_t__ len; scalar_t__ data; } ;
struct TYPE_5__ {int capability; scalar_t__ buseprotection; } ;
struct ieee80211_device {scalar_t__ mode; scalar_t__ rts; TYPE_1__ current_network; TYPE_3__* pHTInfo; } ;
struct TYPE_6__ {int bRTSSTBC; int bRTSUseShortGI; int bCTSEnable; int bRTSBW; int bRTSEnable; int bUseShortPreamble; scalar_t__ RTSSC; void* rts_rate; scalar_t__ bAMPDUEnable; scalar_t__ bMulticast; scalar_t__ bBroadcast; } ;
typedef  TYPE_2__ cb_desc ;
struct TYPE_7__ {int CurrentOpMode; int IOTAction; scalar_t__ bCurBW40MHz; scalar_t__ bEnableHT; scalar_t__ bCurrentHTSupport; } ;
typedef  TYPE_3__* PRT_HIGH_THROUGHPUT ;

/* Variables and functions */
 int HT_IOT_ACT_FORCED_CTS2SELF ; 
 scalar_t__ IEEE_N_24G ; 
 scalar_t__ IW_MODE_MASTER ; 
 void* MGN_24M ; 
 int WLAN_CAPABILITY_SHORT_PREAMBLE ; 
 scalar_t__ is_broadcast_ether_addr (scalar_t__) ; 

void ieee80211_query_protectionmode(struct ieee80211_device* ieee, cb_desc* tcb_desc, struct sk_buff* skb)
{
	// Common Settings
	tcb_desc->bRTSSTBC			= false;
	tcb_desc->bRTSUseShortGI		= false; // Since protection frames are always sent by legacy rate, ShortGI will never be used.
	tcb_desc->bCTSEnable			= false; // Most of protection using RTS/CTS
	tcb_desc->RTSSC				= 0;		// 20MHz: Don't care;  40MHz: Duplicate.
	tcb_desc->bRTSBW			= false; // RTS frame bandwidth is always 20MHz

	if(tcb_desc->bBroadcast || tcb_desc->bMulticast)//only unicast frame will use rts/cts
		return;

	if (is_broadcast_ether_addr(skb->data+16))  //check addr3 as infrastructure add3 is DA.
		return;

	if (ieee->mode < IEEE_N_24G) //b, g mode
	{
			// (1) RTS_Threshold is compared to the MPDU, not MSDU.
			// (2) If there are more than one frag in  this MSDU, only the first frag uses protection frame.
			//		Other fragments are protected by previous fragment.
			//		So we only need to check the length of first fragment.
		if (skb->len > ieee->rts)
		{
			tcb_desc->bRTSEnable = true;
			tcb_desc->rts_rate = MGN_24M;
		}
		else if (ieee->current_network.buseprotection)
		{
			// Use CTS-to-SELF in protection mode.
			tcb_desc->bRTSEnable = true;
			tcb_desc->bCTSEnable = true;
			tcb_desc->rts_rate = MGN_24M;
		}
		//otherwise return;
		return;
	}
	else
	{// 11n High throughput case.
		PRT_HIGH_THROUGHPUT pHTInfo = ieee->pHTInfo;
		while (true)
		{
			//check ERP protection
			if (ieee->current_network.buseprotection)
			{// CTS-to-SELF
				tcb_desc->bRTSEnable = true;
				tcb_desc->bCTSEnable = true;
				tcb_desc->rts_rate = MGN_24M;
				break;
			}
			//check HT op mode
			if(pHTInfo->bCurrentHTSupport  && pHTInfo->bEnableHT)
			{
				u8 HTOpMode = pHTInfo->CurrentOpMode;
				if((pHTInfo->bCurBW40MHz && (HTOpMode == 2 || HTOpMode == 3)) ||
							(!pHTInfo->bCurBW40MHz && HTOpMode == 3) )
				{
					tcb_desc->rts_rate = MGN_24M; // Rate is 24Mbps.
					tcb_desc->bRTSEnable = true;
					break;
				}
			}
			//check rts
			if (skb->len > ieee->rts)
			{
				tcb_desc->rts_rate = MGN_24M; // Rate is 24Mbps.
				tcb_desc->bRTSEnable = true;
				break;
			}
			//to do list: check MIMO power save condition.
			//check AMPDU aggregation for TXOP
			if(tcb_desc->bAMPDUEnable)
			{
				tcb_desc->rts_rate = MGN_24M; // Rate is 24Mbps.
				// According to 8190 design, firmware sends CF-End only if RTS/CTS is enabled. However, it degrads
				// throughput around 10M, so we disable of this mechanism. 2007.08.03 by Emily
				tcb_desc->bRTSEnable = false;
				break;
			}
			//check IOT action
			if(pHTInfo->IOTAction & HT_IOT_ACT_FORCED_CTS2SELF)
			{
				tcb_desc->bCTSEnable	= true;
				tcb_desc->rts_rate  = 	MGN_24M;
				tcb_desc->bRTSEnable = true;
				break;
			}
			// Totally no protection case!!
			goto NO_PROTECTION;
		}
		}
	// For test , CTS replace with RTS
	if( 0 )
	{
		tcb_desc->bCTSEnable	= true;
		tcb_desc->rts_rate = MGN_24M;
		tcb_desc->bRTSEnable 	= true;
	}
	if (ieee->current_network.capability & WLAN_CAPABILITY_SHORT_PREAMBLE)
		tcb_desc->bUseShortPreamble = true;
	if (ieee->mode == IW_MODE_MASTER)
			goto NO_PROTECTION;
	return;
NO_PROTECTION:
	tcb_desc->bRTSEnable	= false;
	tcb_desc->bCTSEnable	= false;
	tcb_desc->rts_rate		= 0;
	tcb_desc->RTSSC		= 0;
	tcb_desc->bRTSBW		= false;
}