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
struct rtl8180_priv {int /*<<< orphan*/ * vif; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct rtl8180_priv* priv; } ;

/* Variables and functions */

__attribute__((used)) static void rtl8180_remove_interface(struct ieee80211_hw *dev,
				     struct ieee80211_vif *vif)
{
	struct rtl8180_priv *priv = dev->priv;
	priv->vif = NULL;
}