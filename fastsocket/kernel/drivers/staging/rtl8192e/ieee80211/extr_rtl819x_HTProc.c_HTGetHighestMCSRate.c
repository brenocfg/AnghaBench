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
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ HTMcsToDataRate (struct ieee80211_device*,int) ; 
 int /*<<< orphan*/  IEEE80211_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  IEEE80211_DL_ERR ; 

u8 HTGetHighestMCSRate(struct ieee80211_device* ieee, u8* pMCSRateSet, u8* pMCSFilter)
{
	u8		i, j;
	u8		bitMap;
	u8		mcsRate = 0;
	u8		availableMcsRate[16];
	if (pMCSRateSet == NULL || pMCSFilter == NULL)
	{
		IEEE80211_DEBUG(IEEE80211_DL_ERR, "pMCSRateSet or pMCSFilter can't be null in HTGetHighestMCSRate()\n");
		return false;
	}
	for(i=0; i<16; i++)
		availableMcsRate[i] = pMCSRateSet[i] & pMCSFilter[i];

	for(i = 0; i < 16; i++)
	{
		if(availableMcsRate[i] != 0)
			break;
	}
	if(i == 16)
		return false;

	for(i = 0; i < 16; i++)
	{
		if(availableMcsRate[i] != 0)
		{
			bitMap = availableMcsRate[i];
			for(j = 0; j < 8; j++)
			{
				if((bitMap%2) != 0)
				{
					if(HTMcsToDataRate(ieee, (8*i+j)) > HTMcsToDataRate(ieee, mcsRate))
						mcsRate = (8*i+j);
				}
				bitMap = bitMap>>1;
			}
		}
	}
	return (mcsRate|0x80);
}