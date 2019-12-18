#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wbsoft_priv {int /*<<< orphan*/  sHwData; } ;
struct ieee80211_if_init_conf {TYPE_2__* vif; } ;
struct ieee80211_hw {struct wbsoft_priv* priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  beacon_int; } ;
struct TYPE_4__ {TYPE_1__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  hal_set_beacon_period (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wbsoft_add_interface(struct ieee80211_hw *dev,
				struct ieee80211_if_init_conf *conf)
{
	struct wbsoft_priv *priv = dev->priv;

	hal_set_beacon_period(&priv->sHwData, conf->vif->bss_conf.beacon_int);

	return 0;
}