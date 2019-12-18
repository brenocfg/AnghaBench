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
struct TYPE_4__ {int /*<<< orphan*/  rfkill_poll; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct il_priv {int is_open; TYPE_2__ _3945; int /*<<< orphan*/  status; int /*<<< orphan*/  wait_command_queue; int /*<<< orphan*/  mutex; TYPE_1__ ucode_code; } ;
struct ieee80211_hw {struct il_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*) ; 
 int /*<<< orphan*/  D_MAC80211 (char*) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  IL_ERR (char*,int) ; 
 int /*<<< orphan*/  S_READY ; 
 int /*<<< orphan*/  UCODE_READY_TIMEOUT ; 
 int __il3945_up (struct il_priv*) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int il3945_read_ucode (struct il_priv*) ; 
 int jiffies_to_msecs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
il3945_mac_start(struct ieee80211_hw *hw)
{
	struct il_priv *il = hw->priv;
	int ret;

	/* we should be verifying the device is ready to be opened */
	mutex_lock(&il->mutex);
	D_MAC80211("enter\n");

	/* fetch ucode file from disk, alloc and copy to bus-master buffers ...
	 * ucode filename and max sizes are card-specific. */

	if (!il->ucode_code.len) {
		ret = il3945_read_ucode(il);
		if (ret) {
			IL_ERR("Could not read microcode: %d\n", ret);
			mutex_unlock(&il->mutex);
			goto out_release_irq;
		}
	}

	ret = __il3945_up(il);

	mutex_unlock(&il->mutex);

	if (ret)
		goto out_release_irq;

	D_INFO("Start UP work.\n");

	/* Wait for START_ALIVE from ucode. Otherwise callbacks from
	 * mac80211 will not be run successfully. */
	ret = wait_event_timeout(il->wait_command_queue,
				 test_bit(S_READY, &il->status),
				 UCODE_READY_TIMEOUT);
	if (!ret) {
		if (!test_bit(S_READY, &il->status)) {
			IL_ERR("Wait for START_ALIVE timeout after %dms.\n",
			       jiffies_to_msecs(UCODE_READY_TIMEOUT));
			ret = -ETIMEDOUT;
			goto out_release_irq;
		}
	}

	/* ucode is running and will send rfkill notifications,
	 * no need to poll the killswitch state anymore */
	cancel_delayed_work(&il->_3945.rfkill_poll);

	il->is_open = 1;
	D_MAC80211("leave\n");
	return 0;

out_release_irq:
	il->is_open = 0;
	D_MAC80211("leave - failed\n");
	return ret;
}