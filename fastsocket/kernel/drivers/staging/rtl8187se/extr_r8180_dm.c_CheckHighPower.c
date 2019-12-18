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
struct r8180_priv {int /*<<< orphan*/  bRegHighPowerMechanism; struct ieee80211_device* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_device {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_LINKED_SCANNING ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 

bool CheckHighPower(struct net_device *dev)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	struct ieee80211_device *ieee = priv->ieee80211;

	if(!priv->bRegHighPowerMechanism)
	{
		return false;
	}

	if(ieee->state == IEEE80211_LINKED_SCANNING)
	{
		return false;
	}

	return true;
}