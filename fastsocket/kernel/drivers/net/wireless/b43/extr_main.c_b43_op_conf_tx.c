#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_queue_params {int dummy; } ;
struct ieee80211_hw {int dummy; } ;
struct b43_wldev {int dummy; } ;
struct b43_wl {int /*<<< orphan*/  mutex; TYPE_1__* qos_params; struct b43_wldev* current_dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  p; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ B43_STAT_INITIALIZED ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENODEV ; 
 int /*<<< orphan*/  b43_mac_enable (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_mac_suspend (struct b43_wldev*) ; 
 int /*<<< orphan*/  b43_qos_params_upload (struct b43_wldev*,int /*<<< orphan*/ *,TYPE_1__) ; 
 TYPE_1__* b43_qos_shm_offsets ; 
 scalar_t__ b43_status (struct b43_wldev*) ; 
 struct b43_wl* hw_to_b43_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee80211_tx_queue_params const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int b43_op_conf_tx(struct ieee80211_hw *hw,
			  struct ieee80211_vif *vif, u16 _queue,
			  const struct ieee80211_tx_queue_params *params)
{
	struct b43_wl *wl = hw_to_b43_wl(hw);
	struct b43_wldev *dev;
	unsigned int queue = (unsigned int)_queue;
	int err = -ENODEV;

	if (queue >= ARRAY_SIZE(wl->qos_params)) {
		/* Queue not available or don't support setting
		 * params on this queue. Return success to not
		 * confuse mac80211. */
		return 0;
	}
	BUILD_BUG_ON(ARRAY_SIZE(b43_qos_shm_offsets) !=
		     ARRAY_SIZE(wl->qos_params));

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	if (unlikely(!dev || (b43_status(dev) < B43_STAT_INITIALIZED)))
		goto out_unlock;

	memcpy(&(wl->qos_params[queue].p), params, sizeof(*params));
	b43_mac_suspend(dev);
	b43_qos_params_upload(dev, &(wl->qos_params[queue].p),
			      b43_qos_shm_offsets[queue]);
	b43_mac_enable(dev);
	err = 0;

out_unlock:
	mutex_unlock(&wl->mutex);

	return err;
}