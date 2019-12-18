#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct ieee80211_device {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IEEE80211_DL_ERR ; 
#define  IEEE_A 132 
#define  IEEE_B 131 
#define  IEEE_G 130 
#define  IEEE_N_24G 129 
#define  IEEE_N_5G 128 
 int RATE_ADPT_1SS_MASK ; 
 int RATE_ADPT_2SS_MASK ; 
 int RATE_ADPT_MCS32_MASK ; 

u8 HT_PickMCSRate(struct ieee80211_device* ieee, u8* pOperateMCS)
{
	u8					i;
	if (pOperateMCS == NULL)
	{
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "pOperateMCS can't be null in HT_PickMCSRate()\n");
		return false;
	}

	switch(ieee->mode)
	{
	case IEEE_A:
	case IEEE_B:
	case IEEE_G:
			//legacy rate routine handled at selectedrate

			//no MCS rate
			for(i=0;i<=15;i++){
				pOperateMCS[i] = 0;
			}
			break;

	case IEEE_N_24G:	//assume CCK rate ok
	case IEEE_N_5G:
			// Legacy part we only use 6, 5.5,2,1 for N_24G and 6 for N_5G.
			// Legacy part shall be handled at SelectRateSet().

			//HT part
			// TODO: may be different if we have different number of antenna
			pOperateMCS[0] &=RATE_ADPT_1SS_MASK;	//support MCS 0~7
			pOperateMCS[1] &=RATE_ADPT_2SS_MASK;
			pOperateMCS[3] &=RATE_ADPT_MCS32_MASK;
			break;

	//should never reach here
	default:

			break;

	}

	return true;
}