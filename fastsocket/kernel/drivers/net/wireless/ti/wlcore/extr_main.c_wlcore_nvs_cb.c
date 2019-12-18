#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wlcore_platdev_data {int /*<<< orphan*/  if_ops; struct wl12xx_platform_data* pdata; } ;
struct wl12xx_platform_data {int platform_quirks; scalar_t__ pwr_in_suspend; } ;
struct wl1271 {scalar_t__ num_tx_desc; int platform_quirks; int irq_wake_enabled; int initialized; int /*<<< orphan*/  nvs_loading_complete; int /*<<< orphan*/ * nvs; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; TYPE_5__* ops; TYPE_4__* hw; int /*<<< orphan*/  if_ops; scalar_t__ nvs_len; struct platform_device* pdev; } ;
struct TYPE_6__ {struct wlcore_platdev_data* platform_data; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct firmware {scalar_t__ size; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int (* setup ) (struct wl1271*) ;int (* identify_chip ) (struct wl1271*) ;} ;
struct TYPE_9__ {TYPE_3__* wiphy; } ;
struct TYPE_7__ {int pattern_min_len; int /*<<< orphan*/  pattern_max_len; int /*<<< orphan*/  n_patterns; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_2__ wowlan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long IRQF_ONESHOT ; 
 unsigned long IRQF_TRIGGER_HIGH ; 
 unsigned long IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  WIPHY_WOWLAN_ANY ; 
 int /*<<< orphan*/  WL1271_MAX_RX_FILTERS ; 
 int /*<<< orphan*/  WL1271_RX_FILTER_MAX_PATTERN_SIZE ; 
 int /*<<< orphan*/  WL12XX_NVS_NAME ; 
 int WL12XX_PLATFORM_QUIRK_EDGE_IRQ ; 
 scalar_t__ WLCORE_MAX_TX_DESCRIPTORS ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_attr_bt_coex_state ; 
 int /*<<< orphan*/  dev_attr_hw_pg_ver ; 
 int device_create_bin_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct wl1271*) ; 
 int /*<<< orphan*/  fwlog_attr ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,struct wl1271*) ; 
 int stub1 (struct wl1271*) ; 
 int stub2 (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl1271_error (char*,...) ; 
 int wl1271_init_ieee80211 (struct wl1271*) ; 
 int wl1271_register_hw (struct wl1271*) ; 
 int /*<<< orphan*/  wl1271_unregister_hw (struct wl1271*) ; 
 int wl12xx_get_hw_info (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_adjust_conf (struct wl1271*) ; 
 int /*<<< orphan*/  wlcore_irq ; 

__attribute__((used)) static void wlcore_nvs_cb(const struct firmware *fw, void *context)
{
	struct wl1271 *wl = context;
	struct platform_device *pdev = wl->pdev;
	struct wlcore_platdev_data *pdev_data = pdev->dev.platform_data;
	struct wl12xx_platform_data *pdata = pdev_data->pdata;
	unsigned long irqflags;
	int ret;

	if (fw) {
		wl->nvs = kmemdup(fw->data, fw->size, GFP_KERNEL);
		if (!wl->nvs) {
			wl1271_error("Could not allocate nvs data");
			goto out;
		}
		wl->nvs_len = fw->size;
	} else {
		wl1271_debug(DEBUG_BOOT, "Could not get nvs file %s",
			     WL12XX_NVS_NAME);
		wl->nvs = NULL;
		wl->nvs_len = 0;
	}

	ret = wl->ops->setup(wl);
	if (ret < 0)
		goto out_free_nvs;

	BUG_ON(wl->num_tx_desc > WLCORE_MAX_TX_DESCRIPTORS);

	/* adjust some runtime configuration parameters */
	wlcore_adjust_conf(wl);

	wl->irq = platform_get_irq(pdev, 0);
	wl->platform_quirks = pdata->platform_quirks;
	wl->if_ops = pdev_data->if_ops;

	if (wl->platform_quirks & WL12XX_PLATFORM_QUIRK_EDGE_IRQ)
		irqflags = IRQF_TRIGGER_RISING;
	else
		irqflags = IRQF_TRIGGER_HIGH | IRQF_ONESHOT;

	ret = request_threaded_irq(wl->irq, NULL, wlcore_irq,
				   irqflags, pdev->name, wl);
	if (ret < 0) {
		wl1271_error("request_irq() failed: %d", ret);
		goto out_free_nvs;
	}

#ifdef CONFIG_PM
	ret = enable_irq_wake(wl->irq);
	if (!ret) {
		wl->irq_wake_enabled = true;
		device_init_wakeup(wl->dev, 1);
		if (pdata->pwr_in_suspend) {
			wl->hw->wiphy->wowlan.flags = WIPHY_WOWLAN_ANY;
			wl->hw->wiphy->wowlan.n_patterns =
				WL1271_MAX_RX_FILTERS;
			wl->hw->wiphy->wowlan.pattern_min_len = 1;
			wl->hw->wiphy->wowlan.pattern_max_len =
				WL1271_RX_FILTER_MAX_PATTERN_SIZE;
		}
	}
#endif
	disable_irq(wl->irq);

	ret = wl12xx_get_hw_info(wl);
	if (ret < 0) {
		wl1271_error("couldn't get hw info");
		goto out_irq;
	}

	ret = wl->ops->identify_chip(wl);
	if (ret < 0)
		goto out_irq;

	ret = wl1271_init_ieee80211(wl);
	if (ret)
		goto out_irq;

	ret = wl1271_register_hw(wl);
	if (ret)
		goto out_irq;

	/* Create sysfs file to control bt coex state */
	ret = device_create_file(wl->dev, &dev_attr_bt_coex_state);
	if (ret < 0) {
		wl1271_error("failed to create sysfs file bt_coex_state");
		goto out_unreg;
	}

	/* Create sysfs file to get HW PG version */
	ret = device_create_file(wl->dev, &dev_attr_hw_pg_ver);
	if (ret < 0) {
		wl1271_error("failed to create sysfs file hw_pg_ver");
		goto out_bt_coex_state;
	}

	/* Create sysfs file for the FW log */
	ret = device_create_bin_file(wl->dev, &fwlog_attr);
	if (ret < 0) {
		wl1271_error("failed to create sysfs file fwlog");
		goto out_hw_pg_ver;
	}

	wl->initialized = true;
	goto out;

out_hw_pg_ver:
	device_remove_file(wl->dev, &dev_attr_hw_pg_ver);

out_bt_coex_state:
	device_remove_file(wl->dev, &dev_attr_bt_coex_state);

out_unreg:
	wl1271_unregister_hw(wl);

out_irq:
	free_irq(wl->irq, wl);

out_free_nvs:
	kfree(wl->nvs);

out:
	release_firmware(fw);
	complete_all(&wl->nvs_loading_complete);
}