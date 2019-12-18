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
struct r8180_priv {TYPE_1__* ieee80211; } ;
struct net_device_stats {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {struct net_device_stats stats; } ;

/* Variables and functions */
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static struct net_device_stats *rtl8180_stats(struct net_device *dev)
{
	struct r8180_priv *priv = ieee80211_priv(dev);

	return &priv->ieee80211->stats;
}