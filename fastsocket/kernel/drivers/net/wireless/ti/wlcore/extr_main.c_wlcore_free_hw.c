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
struct wl1271 {int fwlog_size; int /*<<< orphan*/  hw; int /*<<< orphan*/ * priv; int /*<<< orphan*/  freezable_wq; int /*<<< orphan*/ * tx_res_if; int /*<<< orphan*/ * fw_status_1; int /*<<< orphan*/ * nvs; int /*<<< orphan*/  fw_type; int /*<<< orphan*/ * fw; int /*<<< orphan*/  aggr_buf_size; scalar_t__ aggr_buf; int /*<<< orphan*/  dummy_packet; scalar_t__ fwlog; int /*<<< orphan*/ * mbox; int /*<<< orphan*/ * buffer_32; int /*<<< orphan*/  dev; int /*<<< orphan*/  mutex; int /*<<< orphan*/  fwlog_waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL12XX_FW_TYPE_NONE ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_attr_bt_coex_state ; 
 int /*<<< orphan*/  dev_attr_hw_pg_ver ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_remove_bin_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwlog_attr ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_free_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_debugfs_exit (struct wl1271*) ; 

int wlcore_free_hw(struct wl1271 *wl)
{
	/* Unblock any fwlog readers */
	mutex_lock(&wl->mutex);
	wl->fwlog_size = -1;
	wake_up_interruptible_all(&wl->fwlog_waitq);
	mutex_unlock(&wl->mutex);

	device_remove_bin_file(wl->dev, &fwlog_attr);

	device_remove_file(wl->dev, &dev_attr_hw_pg_ver);

	device_remove_file(wl->dev, &dev_attr_bt_coex_state);
	kfree(wl->buffer_32);
	kfree(wl->mbox);
	free_page((unsigned long)wl->fwlog);
	dev_kfree_skb(wl->dummy_packet);
	free_pages((unsigned long)wl->aggr_buf, get_order(wl->aggr_buf_size));

	wl1271_debugfs_exit(wl);

	vfree(wl->fw);
	wl->fw = NULL;
	wl->fw_type = WL12XX_FW_TYPE_NONE;
	kfree(wl->nvs);
	wl->nvs = NULL;

	kfree(wl->fw_status_1);
	kfree(wl->tx_res_if);
	destroy_workqueue(wl->freezable_wq);

	kfree(wl->priv);
	ieee80211_free_hw(wl->hw);

	return 0;
}