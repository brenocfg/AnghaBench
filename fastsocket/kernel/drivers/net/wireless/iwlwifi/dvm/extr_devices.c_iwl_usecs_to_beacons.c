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
typedef  int u32 ;
struct iwl_priv {int dummy; } ;

/* Variables and functions */
 int IWLAGN_EXT_BEACON_TIME_POS ; 
 int TIME_UNIT ; 
 int iwl_beacon_time_mask_high (struct iwl_priv*,int) ; 
 int iwl_beacon_time_mask_low (struct iwl_priv*,int) ; 

__attribute__((used)) static u32 iwl_usecs_to_beacons(struct iwl_priv *priv, u32 usec,
				u32 beacon_interval)
{
	u32 quot;
	u32 rem;
	u32 interval = beacon_interval * TIME_UNIT;

	if (!interval || !usec)
		return 0;

	quot = (usec / interval) &
		(iwl_beacon_time_mask_high(priv, IWLAGN_EXT_BEACON_TIME_POS) >>
		IWLAGN_EXT_BEACON_TIME_POS);
	rem = (usec % interval) & iwl_beacon_time_mask_low(priv,
				   IWLAGN_EXT_BEACON_TIME_POS);

	return (quot << IWLAGN_EXT_BEACON_TIME_POS) + rem;
}