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
typedef  void* u32 ;
struct wl1271 {int sg_enabled; int hw_pg_ver; int num_tx_desc; int mbox_size; void* priv; int /*<<< orphan*/  freezable_wq; int /*<<< orphan*/ * aggr_buf; int /*<<< orphan*/  dummy_packet; int /*<<< orphan*/ * fwlog; void* mbox; void* buffer_32; void* aggr_buf_size; int /*<<< orphan*/  nvs_loading_complete; int /*<<< orphan*/  flush_mutex; int /*<<< orphan*/  mutex; int /*<<< orphan*/  fw_type; int /*<<< orphan*/  state; int /*<<< orphan*/  wl_lock; int /*<<< orphan*/ ** tx_frames; struct wl1271* tx_frames_map; int /*<<< orphan*/  links_map; int /*<<< orphan*/  fwlog_waitq; scalar_t__ fwlog_size; scalar_t__ active_link_count; scalar_t__ active_sta_count; int /*<<< orphan*/  system_hlid; scalar_t__ platform_quirks; scalar_t__ quirks; scalar_t__ ap_fw_ps_map; scalar_t__ ap_ps_map; scalar_t__ recovery_count; int /*<<< orphan*/  sleep_auth; scalar_t__ flags; int /*<<< orphan*/  channel_type; int /*<<< orphan*/  band; int /*<<< orphan*/  power_level; scalar_t__ rx_counter; int /*<<< orphan*/  channel; int /*<<< orphan*/  tx_watchdog_work; int /*<<< orphan*/  roc_complete_work; int /*<<< orphan*/  scan_complete_work; int /*<<< orphan*/  recovery_work; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  netstack_work; int /*<<< orphan*/  elp_work; int /*<<< orphan*/  deferred_tx_queue; int /*<<< orphan*/  deferred_rx_queue; TYPE_1__* links; struct ieee80211_hw* hw; int /*<<< orphan*/  wlvif_list; } ;
struct ieee80211_hw {struct wl1271* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/ * tx_queue; } ;

/* Variables and functions */
 int AP_MAX_STATIONS ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOMEM ; 
 struct ieee80211_hw* ERR_PTR (int) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_CHAN_NO_HT ; 
 int NUM_TX_QUEUES ; 
 int /*<<< orphan*/  WL1271_DEFAULT_CHANNEL ; 
 int /*<<< orphan*/  WL1271_DEFAULT_POWER_LEVEL ; 
 int /*<<< orphan*/  WL1271_PSM_ILLEGAL ; 
 int /*<<< orphan*/  WL12XX_FW_TYPE_NONE ; 
 int WL12XX_MAX_LINKS ; 
 int /*<<< orphan*/  WL12XX_SYSTEM_HLID ; 
 int /*<<< orphan*/  WLCORE_STATE_OFF ; 
 scalar_t__ __get_free_pages (int,unsigned int) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_freezable_workqueue (char*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  free_pages (unsigned long,unsigned int) ; 
 unsigned int get_order (void*) ; 
 scalar_t__ get_zeroed_page (int) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_free_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (int,int) ; 
 void* kzalloc (size_t,int) ; 
 int /*<<< orphan*/  memset (struct wl1271*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1271_debugfs_exit (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_elp_work ; 
 int /*<<< orphan*/  wl1271_error (char*) ; 
 int /*<<< orphan*/  wl1271_netstack_work ; 
 int /*<<< orphan*/  wl1271_ops ; 
 int /*<<< orphan*/  wl1271_recovery_work ; 
 int /*<<< orphan*/  wl1271_scan_complete_work ; 
 int /*<<< orphan*/  wl1271_tx_work ; 
 int /*<<< orphan*/  wl12xx_alloc_dummy_packet (struct wl1271*) ; 
 int /*<<< orphan*/  wl12xx_tx_watchdog_work ; 
 int /*<<< orphan*/  wlcore_roc_complete_work ; 

struct ieee80211_hw *wlcore_alloc_hw(size_t priv_size, u32 aggr_buf_size,
				     u32 mbox_size)
{
	struct ieee80211_hw *hw;
	struct wl1271 *wl;
	int i, j, ret;
	unsigned int order;

	BUILD_BUG_ON(AP_MAX_STATIONS > WL12XX_MAX_LINKS);

	hw = ieee80211_alloc_hw(sizeof(*wl), &wl1271_ops);
	if (!hw) {
		wl1271_error("could not alloc ieee80211_hw");
		ret = -ENOMEM;
		goto err_hw_alloc;
	}

	wl = hw->priv;
	memset(wl, 0, sizeof(*wl));

	wl->priv = kzalloc(priv_size, GFP_KERNEL);
	if (!wl->priv) {
		wl1271_error("could not alloc wl priv");
		ret = -ENOMEM;
		goto err_priv_alloc;
	}

	INIT_LIST_HEAD(&wl->wlvif_list);

	wl->hw = hw;

	for (i = 0; i < NUM_TX_QUEUES; i++)
		for (j = 0; j < WL12XX_MAX_LINKS; j++)
			skb_queue_head_init(&wl->links[j].tx_queue[i]);

	skb_queue_head_init(&wl->deferred_rx_queue);
	skb_queue_head_init(&wl->deferred_tx_queue);

	INIT_DELAYED_WORK(&wl->elp_work, wl1271_elp_work);
	INIT_WORK(&wl->netstack_work, wl1271_netstack_work);
	INIT_WORK(&wl->tx_work, wl1271_tx_work);
	INIT_WORK(&wl->recovery_work, wl1271_recovery_work);
	INIT_DELAYED_WORK(&wl->scan_complete_work, wl1271_scan_complete_work);
	INIT_DELAYED_WORK(&wl->roc_complete_work, wlcore_roc_complete_work);
	INIT_DELAYED_WORK(&wl->tx_watchdog_work, wl12xx_tx_watchdog_work);

	wl->freezable_wq = create_freezable_workqueue("wl12xx_wq");
	if (!wl->freezable_wq) {
		ret = -ENOMEM;
		goto err_hw;
	}

	wl->channel = WL1271_DEFAULT_CHANNEL;
	wl->rx_counter = 0;
	wl->power_level = WL1271_DEFAULT_POWER_LEVEL;
	wl->band = IEEE80211_BAND_2GHZ;
	wl->channel_type = NL80211_CHAN_NO_HT;
	wl->flags = 0;
	wl->sg_enabled = true;
	wl->sleep_auth = WL1271_PSM_ILLEGAL;
	wl->recovery_count = 0;
	wl->hw_pg_ver = -1;
	wl->ap_ps_map = 0;
	wl->ap_fw_ps_map = 0;
	wl->quirks = 0;
	wl->platform_quirks = 0;
	wl->system_hlid = WL12XX_SYSTEM_HLID;
	wl->active_sta_count = 0;
	wl->active_link_count = 0;
	wl->fwlog_size = 0;
	init_waitqueue_head(&wl->fwlog_waitq);

	/* The system link is always allocated */
	__set_bit(WL12XX_SYSTEM_HLID, wl->links_map);

	memset(wl->tx_frames_map, 0, sizeof(wl->tx_frames_map));
	for (i = 0; i < wl->num_tx_desc; i++)
		wl->tx_frames[i] = NULL;

	spin_lock_init(&wl->wl_lock);

	wl->state = WLCORE_STATE_OFF;
	wl->fw_type = WL12XX_FW_TYPE_NONE;
	mutex_init(&wl->mutex);
	mutex_init(&wl->flush_mutex);
	init_completion(&wl->nvs_loading_complete);

	order = get_order(aggr_buf_size);
	wl->aggr_buf = (u8 *)__get_free_pages(GFP_KERNEL, order);
	if (!wl->aggr_buf) {
		ret = -ENOMEM;
		goto err_wq;
	}
	wl->aggr_buf_size = aggr_buf_size;

	wl->dummy_packet = wl12xx_alloc_dummy_packet(wl);
	if (!wl->dummy_packet) {
		ret = -ENOMEM;
		goto err_aggr;
	}

	/* Allocate one page for the FW log */
	wl->fwlog = (u8 *)get_zeroed_page(GFP_KERNEL);
	if (!wl->fwlog) {
		ret = -ENOMEM;
		goto err_dummy_packet;
	}

	wl->mbox_size = mbox_size;
	wl->mbox = kmalloc(wl->mbox_size, GFP_KERNEL | GFP_DMA);
	if (!wl->mbox) {
		ret = -ENOMEM;
		goto err_fwlog;
	}

	wl->buffer_32 = kmalloc(sizeof(*wl->buffer_32), GFP_KERNEL);
	if (!wl->buffer_32) {
		ret = -ENOMEM;
		goto err_mbox;
	}

	return hw;

err_mbox:
	kfree(wl->mbox);

err_fwlog:
	free_page((unsigned long)wl->fwlog);

err_dummy_packet:
	dev_kfree_skb(wl->dummy_packet);

err_aggr:
	free_pages((unsigned long)wl->aggr_buf, order);

err_wq:
	destroy_workqueue(wl->freezable_wq);

err_hw:
	wl1271_debugfs_exit(wl);
	kfree(wl->priv);

err_priv_alloc:
	ieee80211_free_hw(hw);

err_hw_alloc:

	return ERR_PTR(ret);
}