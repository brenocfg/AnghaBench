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
typedef  size_t u8 ;
struct TYPE_4__ {int TotalNum; char** elements; size_t index; char* TotalVal; } ;
struct TYPE_5__ {TYPE_1__ cck_adc_pwdb; } ;
struct r8192_priv {scalar_t__ rf_type; int* undecorated_smoothed_cck_adc_pwdb; TYPE_2__ stats; } ;
struct ieee80211_rx_stats {char* cck_adc_pwdb; scalar_t__ bPacketBeacon; scalar_t__ bPacketToSelf; scalar_t__ bIsCCK; } ;
struct TYPE_6__ {int* cck_pwdb_sta; scalar_t__ Enable; } ;

/* Variables and functions */
 TYPE_3__ DM_RxPathSelTable ; 
 scalar_t__ PHY_RSSI_SLID_WIN_MAX ; 
 size_t RF90_PATH_A ; 
 size_t RF90_PATH_MAX ; 
 scalar_t__ RF_2T4R ; 
 int Rx_Smooth_Factor ; 

__attribute__((used)) static void
rtl8190_process_cck_rxpathsel(
	struct r8192_priv * priv,
	struct ieee80211_rx_stats * pprevious_stats
	)
{
#ifdef RTL8190P	//Only 90P 2T4R need to check
	char				last_cck_adc_pwdb[4]={0,0,0,0};
	u8				i;
//cosa add for Rx path selection
		if(priv->rf_type == RF_2T4R && DM_RxPathSelTable.Enable)
		{
			if(pprevious_stats->bIsCCK &&
				(pprevious_stats->bPacketToSelf ||pprevious_stats->bPacketBeacon))
			{
				/* record the cck adc_pwdb to the sliding window. */
				if(priv->stats.cck_adc_pwdb.TotalNum++ >= PHY_RSSI_SLID_WIN_MAX)
				{
					priv->stats.cck_adc_pwdb.TotalNum = PHY_RSSI_SLID_WIN_MAX;
					for(i=RF90_PATH_A; i<RF90_PATH_MAX; i++)
					{
						last_cck_adc_pwdb[i] = priv->stats.cck_adc_pwdb.elements[i][priv->stats.cck_adc_pwdb.index];
						priv->stats.cck_adc_pwdb.TotalVal[i] -= last_cck_adc_pwdb[i];
					}
				}
				for(i=RF90_PATH_A; i<RF90_PATH_MAX; i++)
				{
					priv->stats.cck_adc_pwdb.TotalVal[i] += pprevious_stats->cck_adc_pwdb[i];
					priv->stats.cck_adc_pwdb.elements[i][priv->stats.cck_adc_pwdb.index] = pprevious_stats->cck_adc_pwdb[i];
				}
				priv->stats.cck_adc_pwdb.index++;
				if(priv->stats.cck_adc_pwdb.index >= PHY_RSSI_SLID_WIN_MAX)
					priv->stats.cck_adc_pwdb.index = 0;

				for(i=RF90_PATH_A; i<RF90_PATH_MAX; i++)
				{
					DM_RxPathSelTable.cck_pwdb_sta[i] = priv->stats.cck_adc_pwdb.TotalVal[i]/priv->stats.cck_adc_pwdb.TotalNum;
				}

				for(i=RF90_PATH_A; i<RF90_PATH_MAX; i++)
				{
					if(pprevious_stats->cck_adc_pwdb[i]  > (char)priv->undecorated_smoothed_cck_adc_pwdb[i])
					{
						priv->undecorated_smoothed_cck_adc_pwdb[i] =
							( (priv->undecorated_smoothed_cck_adc_pwdb[i]*(Rx_Smooth_Factor-1)) +
							(pprevious_stats->cck_adc_pwdb[i])) /(Rx_Smooth_Factor);
						priv->undecorated_smoothed_cck_adc_pwdb[i] = priv->undecorated_smoothed_cck_adc_pwdb[i] + 1;
					}
					else
					{
						priv->undecorated_smoothed_cck_adc_pwdb[i] =
							( (priv->undecorated_smoothed_cck_adc_pwdb[i]*(Rx_Smooth_Factor-1)) +
							(pprevious_stats->cck_adc_pwdb[i])) /(Rx_Smooth_Factor);
					}
				}
			}
		}
#endif
}