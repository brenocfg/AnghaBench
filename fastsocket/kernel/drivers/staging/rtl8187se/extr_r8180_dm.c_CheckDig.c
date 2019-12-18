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
struct r8180_priv {struct ieee80211_device* ieee80211; int /*<<< orphan*/  bDigMechanism; } ;
struct net_device {int dummy; } ;
struct ieee80211_device {scalar_t__ state; int rate; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_LINKED ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 

bool
CheckDig(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	struct ieee80211_device *ieee = priv->ieee80211;

	if(!priv->bDigMechanism)
		return false;

	if(ieee->state != IEEE80211_LINKED)
		return false;

	//if(priv->CurrentOperaRate < 36) // Schedule Dig under all OFDM rates. By Bruce, 2007-06-01.
	if((priv->ieee80211->rate/5) < 36) // Schedule Dig under all OFDM rates. By Bruce, 2007-06-01.
		return false;
	return true;
}