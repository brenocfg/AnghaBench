#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ssb_sprom {int /*<<< orphan*/  il0mac; int /*<<< orphan*/  et1mac; } ;
struct TYPE_5__ {int /*<<< orphan*/  revision; } ;
struct ssb_device {TYPE_2__ id; TYPE_3__* bus; int /*<<< orphan*/  dev; } ;
struct ieee80211_hw {int flags; int queues; int max_rates; TYPE_1__* wiphy; } ;
struct b43legacy_wl {scalar_t__* tx_queue_stopped; int /*<<< orphan*/ * tx_queue; int /*<<< orphan*/  tx_work; int /*<<< orphan*/  beacon_update_trigger; int /*<<< orphan*/  devlist; int /*<<< orphan*/  mutex; int /*<<< orphan*/  leds_lock; int /*<<< orphan*/  irq_lock; struct ieee80211_hw* hw; } ;
struct TYPE_6__ {int /*<<< orphan*/  chip_id; struct ssb_sprom sprom; } ;
struct TYPE_4__ {int interface_modes; } ;

/* Variables and functions */
 int B43legacy_QOS_QUEUE_NUM ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int IEEE80211_HW_RX_INCLUDES_FCS ; 
 int IEEE80211_HW_SIGNAL_DBM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  NL80211_IFTYPE_WDS ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_IEEE80211_PERM_ADDR (struct ieee80211_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_beacon_update_trigger_work ; 
 int /*<<< orphan*/  b43legacy_hw_ops ; 
 int /*<<< orphan*/  b43legacy_sprom_fixup (TYPE_3__*) ; 
 int /*<<< orphan*/  b43legacy_tx_work ; 
 int /*<<< orphan*/  b43legacyerr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  b43legacyinfo (struct b43legacy_wl*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct b43legacy_wl* hw_to_b43legacy_wl (struct ieee80211_hw*) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ *) ; 
 scalar_t__ is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct b43legacy_wl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssb_set_devtypedata (struct ssb_device*,struct b43legacy_wl*) ; 

__attribute__((used)) static int b43legacy_wireless_init(struct ssb_device *dev)
{
	struct ssb_sprom *sprom = &dev->bus->sprom;
	struct ieee80211_hw *hw;
	struct b43legacy_wl *wl;
	int err = -ENOMEM;
	int queue_num;

	b43legacy_sprom_fixup(dev->bus);

	hw = ieee80211_alloc_hw(sizeof(*wl), &b43legacy_hw_ops);
	if (!hw) {
		b43legacyerr(NULL, "Could not allocate ieee80211 device\n");
		goto out;
	}

	/* fill hw info */
	hw->flags = IEEE80211_HW_RX_INCLUDES_FCS |
		    IEEE80211_HW_SIGNAL_DBM;
	hw->wiphy->interface_modes =
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_WDS) |
		BIT(NL80211_IFTYPE_ADHOC);
	hw->queues = 1; /* FIXME: hardware has more queues */
	hw->max_rates = 2;
	SET_IEEE80211_DEV(hw, dev->dev);
	if (is_valid_ether_addr(sprom->et1mac))
		SET_IEEE80211_PERM_ADDR(hw, sprom->et1mac);
	else
		SET_IEEE80211_PERM_ADDR(hw, sprom->il0mac);

	/* Get and initialize struct b43legacy_wl */
	wl = hw_to_b43legacy_wl(hw);
	memset(wl, 0, sizeof(*wl));
	wl->hw = hw;
	spin_lock_init(&wl->irq_lock);
	spin_lock_init(&wl->leds_lock);
	mutex_init(&wl->mutex);
	INIT_LIST_HEAD(&wl->devlist);
	INIT_WORK(&wl->beacon_update_trigger, b43legacy_beacon_update_trigger_work);
	INIT_WORK(&wl->tx_work, b43legacy_tx_work);

	/* Initialize queues and flags. */
	for (queue_num = 0; queue_num < B43legacy_QOS_QUEUE_NUM; queue_num++) {
		skb_queue_head_init(&wl->tx_queue[queue_num]);
		wl->tx_queue_stopped[queue_num] = 0;
	}

	ssb_set_devtypedata(dev, wl);
	b43legacyinfo(wl, "Broadcom %04X WLAN found (core revision %u)\n",
		      dev->bus->chip_id, dev->id.revision);
	err = 0;
out:
	return err;
}