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
struct r8192_priv {int up; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int _rtl8192_up (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

int rtl8192_up(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	if (priv->up == 1) return -1;

	return _rtl8192_up(dev);
}