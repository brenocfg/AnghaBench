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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_hw {struct ath9k_htc_priv* priv; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  mutex; TYPE_1__* ah; } ;
struct TYPE_2__ {int /*<<< orphan*/  coverage_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath9k_htc_ps_restore (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_htc_ps_wakeup (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  ath9k_hw_init_global_settings (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath9k_htc_set_coverage_class(struct ieee80211_hw *hw,
					 u8 coverage_class)
{
	struct ath9k_htc_priv *priv = hw->priv;

	mutex_lock(&priv->mutex);
	ath9k_htc_ps_wakeup(priv);
	priv->ah->coverage_class = coverage_class;
	ath9k_hw_init_global_settings(priv->ah);
	ath9k_htc_ps_restore(priv);
	mutex_unlock(&priv->mutex);
}