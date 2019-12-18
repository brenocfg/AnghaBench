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
struct ath9k_htc_priv {int ps_usecount; int /*<<< orphan*/  htc_pm_lock; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH9K_PM_AWAKE ; 
 int /*<<< orphan*/  ath9k_hw_setpower (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ath9k_htc_ps_wakeup(struct ath9k_htc_priv *priv)
{
	mutex_lock(&priv->htc_pm_lock);
	if (++priv->ps_usecount != 1)
		goto unlock;
	ath9k_hw_setpower(priv->ah, ATH9K_PM_AWAKE);

unlock:
	mutex_unlock(&priv->htc_pm_lock);
}