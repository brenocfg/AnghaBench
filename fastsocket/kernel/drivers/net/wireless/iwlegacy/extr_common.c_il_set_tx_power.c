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
struct il_priv {scalar_t__ tx_power_user_lmt; scalar_t__ tx_power_device_lmt; scalar_t__ tx_power_next; TYPE_1__* ops; int /*<<< orphan*/  staging; int /*<<< orphan*/  active; int /*<<< orphan*/  status; int /*<<< orphan*/  mutex; } ;
typedef  scalar_t__ s8 ;
struct TYPE_2__ {int (* send_tx_power ) (struct il_priv*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*) ; 
 int EINVAL ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IL_WARN (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  S_SCANNING ; 
 int /*<<< orphan*/  il_is_ready_rf (struct il_priv*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct il_priv*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
il_set_tx_power(struct il_priv *il, s8 tx_power, bool force)
{
	int ret;
	s8 prev_tx_power;
	bool defer;

	lockdep_assert_held(&il->mutex);

	if (il->tx_power_user_lmt == tx_power && !force)
		return 0;

	if (!il->ops->send_tx_power)
		return -EOPNOTSUPP;

	/* 0 dBm mean 1 milliwatt */
	if (tx_power < 0) {
		IL_WARN("Requested user TXPOWER %d below 1 mW.\n", tx_power);
		return -EINVAL;
	}

	if (tx_power > il->tx_power_device_lmt) {
		IL_WARN("Requested user TXPOWER %d above upper limit %d.\n",
			tx_power, il->tx_power_device_lmt);
		return -EINVAL;
	}

	if (!il_is_ready_rf(il))
		return -EIO;

	/* scan complete and commit_rxon use tx_power_next value,
	 * it always need to be updated for newest request */
	il->tx_power_next = tx_power;

	/* do not set tx power when scanning or channel changing */
	defer = test_bit(S_SCANNING, &il->status) ||
	    memcmp(&il->active, &il->staging, sizeof(il->staging));
	if (defer && !force) {
		D_INFO("Deferring tx power set\n");
		return 0;
	}

	prev_tx_power = il->tx_power_user_lmt;
	il->tx_power_user_lmt = tx_power;

	ret = il->ops->send_tx_power(il);

	/* if fail to set tx_power, restore the orig. tx power */
	if (ret) {
		il->tx_power_user_lmt = prev_tx_power;
		il->tx_power_next = prev_tx_power;
	}
	return ret;
}