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
struct TYPE_2__ {unsigned long longcal_timer; unsigned long shortcal_timer; unsigned long checkani_timer; } ;
struct ath_common {int /*<<< orphan*/  hw; TYPE_1__ ani; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  ani_work; int /*<<< orphan*/  op_flags; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_ANI_POLLINTERVAL ; 
 int /*<<< orphan*/  OP_ANI_RUNNING ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned long jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void ath9k_htc_start_ani(struct ath9k_htc_priv *priv)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	unsigned long timestamp = jiffies_to_msecs(jiffies);

	common->ani.longcal_timer = timestamp;
	common->ani.shortcal_timer = timestamp;
	common->ani.checkani_timer = timestamp;

	set_bit(OP_ANI_RUNNING, &priv->op_flags);

	ieee80211_queue_delayed_work(common->hw, &priv->ani_work,
				     msecs_to_jiffies(ATH_ANI_POLLINTERVAL));
}