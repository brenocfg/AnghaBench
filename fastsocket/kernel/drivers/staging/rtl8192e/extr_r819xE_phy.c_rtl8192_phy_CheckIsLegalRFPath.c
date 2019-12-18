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
typedef  scalar_t__ u32 ;
struct r8192_priv {scalar_t__ rf_type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RF90_PATH_A ; 
 scalar_t__ RF90_PATH_B ; 
 scalar_t__ RF90_PATH_C ; 
 scalar_t__ RF90_PATH_D ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ RF_2T4R ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

u8 rtl8192_phy_CheckIsLegalRFPath(struct net_device* dev, u32 eRFPath)
{
	u8 ret = 1;
	struct r8192_priv *priv = ieee80211_priv(dev);
#ifdef RTL8190P
	if(priv->rf_type == RF_2T4R)
	{
		ret= 1;
	}
	else if (priv->rf_type == RF_1T2R)
	{
		if(eRFPath == RF90_PATH_A || eRFPath == RF90_PATH_B)
			ret = 0;
		else if(eRFPath == RF90_PATH_C || eRFPath == RF90_PATH_D)
			ret =  1;
	}
#else
	#ifdef RTL8192E
	if (priv->rf_type == RF_2T4R)
		ret = 0;
	else if (priv->rf_type == RF_1T2R)
	{
		if (eRFPath == RF90_PATH_A || eRFPath == RF90_PATH_B)
			ret = 1;
		else if (eRFPath == RF90_PATH_C || eRFPath == RF90_PATH_D)
			ret = 0;
	}
	#endif
#endif
	return ret;
}