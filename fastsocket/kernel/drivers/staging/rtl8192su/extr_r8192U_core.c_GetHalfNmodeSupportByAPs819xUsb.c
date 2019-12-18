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
struct r8192_priv {struct ieee80211_device* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_device {int bHalfWirelessN24GMode; } ;

/* Variables and functions */
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

bool GetHalfNmodeSupportByAPs819xUsb(struct net_device* dev)
{
	bool			Reval;
	struct r8192_priv* priv = ieee80211_priv(dev);
	struct ieee80211_device* ieee = priv->ieee80211;

// 	Added by Roger, 2008.08.29.
	return false;

	if(ieee->bHalfWirelessN24GMode == true)
		Reval = true;
	else
		Reval =  false;

	return Reval;
}