#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct r8192_priv {scalar_t__ MidHighPwrTHR_L1; scalar_t__ MidHighPwrTHR_L2; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int dig_enable_flag; long rssi_val; scalar_t__ dig_algorithm; int dig_algorithm_switch; scalar_t__ rx_gain_range_max; scalar_t__ rx_gain_range_min; scalar_t__ backoff_val; scalar_t__ dbg_mode; void* dig_state; scalar_t__ rssi_high_power_highthresh; scalar_t__ rssi_low_thresh; scalar_t__ rssi_high_thresh; } ;

/* Variables and functions */
 scalar_t__ DIG_ALGO_BY_FALSE_ALARM ; 
 scalar_t__ DIG_ALGO_MAX ; 
 scalar_t__ DIG_TYPE_ALGORITHM ; 
 scalar_t__ DIG_TYPE_BACKOFF ; 
 scalar_t__ DIG_TYPE_DBG_MODE ; 
 scalar_t__ DIG_TYPE_DISABLE ; 
 scalar_t__ DIG_TYPE_ENABLE ; 
 scalar_t__ DIG_TYPE_RSSI ; 
 scalar_t__ DIG_TYPE_RX_GAIN_MAX ; 
 scalar_t__ DIG_TYPE_RX_GAIN_MIN ; 
 scalar_t__ DIG_TYPE_THRESH_HIGH ; 
 scalar_t__ DIG_TYPE_THRESH_HIGHPWR_HIGH ; 
 scalar_t__ DIG_TYPE_THRESH_HIGHPWR_LOW ; 
 scalar_t__ DIG_TYPE_THRESH_LOW ; 
 scalar_t__ DM_DBG_MAX ; 
 scalar_t__ DM_DBG_OFF ; 
 void* DM_STA_DIG_MAX ; 
 TYPE_1__ dm_digtable ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

extern void dm_change_dynamic_initgain_thresh(struct net_device *dev,
								u32		dm_type,
								u32		dm_value)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	if(dm_type == DIG_TYPE_THRESH_HIGHPWR_HIGH)
		priv->MidHighPwrTHR_L2 = (u8)dm_value;
	else if(dm_type == DIG_TYPE_THRESH_HIGHPWR_LOW)
		priv->MidHighPwrTHR_L1 = (u8)dm_value;
	return;
	if (dm_type == DIG_TYPE_THRESH_HIGH)
	{
		dm_digtable.rssi_high_thresh = dm_value;
	}
	else if (dm_type == DIG_TYPE_THRESH_LOW)
	{
		dm_digtable.rssi_low_thresh = dm_value;
	}
	else if (dm_type == DIG_TYPE_THRESH_HIGHPWR_HIGH)
	{
		dm_digtable.rssi_high_power_highthresh = dm_value;
	}
	else if (dm_type == DIG_TYPE_THRESH_HIGHPWR_HIGH)
	{
		dm_digtable.rssi_high_power_highthresh = dm_value;
	}
	else if (dm_type == DIG_TYPE_ENABLE)
	{
		dm_digtable.dig_state		= DM_STA_DIG_MAX;
		dm_digtable.dig_enable_flag	= true;
	}
	else if (dm_type == DIG_TYPE_DISABLE)
	{
		dm_digtable.dig_state		= DM_STA_DIG_MAX;
		dm_digtable.dig_enable_flag	= false;
	}
	else if (dm_type == DIG_TYPE_DBG_MODE)
	{
		if(dm_value >= DM_DBG_MAX)
			dm_value = DM_DBG_OFF;
		dm_digtable.dbg_mode		= (u8)dm_value;
	}
	else if (dm_type == DIG_TYPE_RSSI)
	{
		if(dm_value > 100)
			dm_value = 30;
		dm_digtable.rssi_val			= (long)dm_value;
	}
	else if (dm_type == DIG_TYPE_ALGORITHM)
	{
		if (dm_value >= DIG_ALGO_MAX)
			dm_value = DIG_ALGO_BY_FALSE_ALARM;
		if(dm_digtable.dig_algorithm != (u8)dm_value)
			dm_digtable.dig_algorithm_switch = 1;
		dm_digtable.dig_algorithm	= (u8)dm_value;
	}
	else if (dm_type == DIG_TYPE_BACKOFF)
	{
		if(dm_value > 30)
			dm_value = 30;
		dm_digtable.backoff_val		= (u8)dm_value;
	}
	else if(dm_type == DIG_TYPE_RX_GAIN_MIN)
	{
		if(dm_value == 0)
			dm_value = 0x1;
		dm_digtable.rx_gain_range_min = (u8)dm_value;
	}
	else if(dm_type == DIG_TYPE_RX_GAIN_MAX)
	{
		if(dm_value > 0x50)
			dm_value = 0x50;
		dm_digtable.rx_gain_range_max = (u8)dm_value;
	}
}