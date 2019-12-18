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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 

__attribute__((used)) static void adm8211_remove_interface(struct ieee80211_hw *dev,
				     struct ieee80211_vif *vif)
{
	struct adm8211_priv *priv = dev->priv;
	priv->mode = NL80211_IFTYPE_MONITOR;
}