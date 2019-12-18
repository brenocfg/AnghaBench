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
struct ssb_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ucode; } ;
struct b43legacy_wldev {TYPE_1__ fw; int /*<<< orphan*/  restart_work; } ;
struct b43legacy_wl {int /*<<< orphan*/  devlist; int /*<<< orphan*/  hw; struct b43legacy_wldev* current_dev; int /*<<< orphan*/  firmware_load; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  b43legacy_one_core_detach (struct ssb_device*) ; 
 int /*<<< orphan*/  b43legacy_wireless_exit (struct ssb_device*,struct b43legacy_wl*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_unregister_hw (int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct b43legacy_wl* ssb_get_devtypedata (struct ssb_device*) ; 
 struct b43legacy_wldev* ssb_get_drvdata (struct ssb_device*) ; 

__attribute__((used)) static void b43legacy_remove(struct ssb_device *dev)
{
	struct b43legacy_wl *wl = ssb_get_devtypedata(dev);
	struct b43legacy_wldev *wldev = ssb_get_drvdata(dev);

	/* We must cancel any work here before unregistering from ieee80211,
	 * as the ieee80211 unreg will destroy the workqueue. */
	cancel_work_sync(&wldev->restart_work);
	cancel_work_sync(&wl->firmware_load);

	B43legacy_WARN_ON(!wl);
	if (!wldev->fw.ucode)
		return;			/* NULL if fw never loaded */
	if (wl->current_dev == wldev)
		ieee80211_unregister_hw(wl->hw);

	b43legacy_one_core_detach(dev);

	if (list_empty(&wl->devlist))
		/* Last core on the chip unregistered.
		 * We can destroy common struct b43legacy_wl.
		 */
		b43legacy_wireless_exit(dev, wl);
}