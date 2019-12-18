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
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* chan; } ;
struct ieee80211_conf {int flags; scalar_t__ power_level; TYPE_2__ chandef; int /*<<< orphan*/  long_frame_max_tx_count; int /*<<< orphan*/  short_frame_max_tx_count; } ;
struct ieee80211_hw {struct ieee80211_conf conf; } ;
struct b43legacy_phy {scalar_t__ channel; scalar_t__ power_level; scalar_t__ radio_on; int /*<<< orphan*/  type; } ;
struct b43legacy_wldev {int /*<<< orphan*/  irq_mask; TYPE_3__* wl; int /*<<< orphan*/  radio_hw_enable; struct b43legacy_phy phy; } ;
struct b43legacy_wl {scalar_t__ radio_enabled; int /*<<< orphan*/  mutex; int /*<<< orphan*/  irq_lock; struct b43legacy_wldev* current_dev; } ;
struct TYPE_6__ {int radiotap_enabled; } ;
struct TYPE_4__ {int band; scalar_t__ hw_value; } ;

/* Variables and functions */
 int B43legacy_ANTENNA_DEFAULT ; 
 int /*<<< orphan*/  B43legacy_MMIO_GEN_IRQ_MASK ; 
 unsigned int B43legacy_PHYMODE_B ; 
 unsigned int B43legacy_PHYMODE_G ; 
 int /*<<< orphan*/  B43legacy_PHYTYPE_B ; 
 scalar_t__ B43legacy_STAT_STARTED ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
#define  IEEE80211_BAND_2GHZ 128 
 int IEEE80211_CONF_CHANGE_RETRY_LIMITS ; 
 int IEEE80211_CONF_MONITOR ; 
 int /*<<< orphan*/  b43legacy_mgmtframe_txantenna (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_phy_xmitpower (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_radio_selectchannel (struct b43legacy_wldev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_radio_turn_off (struct b43legacy_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_radio_turn_on (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_set_retry_limits (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ b43legacy_status (struct b43legacy_wldev*) ; 
 int b43legacy_switch_phymode (struct b43legacy_wl*,unsigned int) ; 
 int /*<<< orphan*/  b43legacy_synchronize_irq (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_write32 (struct b43legacy_wldev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacyinfo (TYPE_3__*,char*) ; 
 struct b43legacy_wl* hw_to_b43legacy_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int b43legacy_op_dev_config(struct ieee80211_hw *hw,
				   u32 changed)
{
	struct b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	struct b43legacy_wldev *dev;
	struct b43legacy_phy *phy;
	struct ieee80211_conf *conf = &hw->conf;
	unsigned long flags;
	unsigned int new_phymode = 0xFFFF;
	int antenna_tx;
	int err = 0;

	antenna_tx = B43legacy_ANTENNA_DEFAULT;

	mutex_lock(&wl->mutex);
	dev = wl->current_dev;
	phy = &dev->phy;

	if (changed & IEEE80211_CONF_CHANGE_RETRY_LIMITS)
		b43legacy_set_retry_limits(dev,
					   conf->short_frame_max_tx_count,
					   conf->long_frame_max_tx_count);
	changed &= ~IEEE80211_CONF_CHANGE_RETRY_LIMITS;
	if (!changed)
		goto out_unlock_mutex;

	/* Switch the PHY mode (if necessary). */
	switch (conf->chandef.chan->band) {
	case IEEE80211_BAND_2GHZ:
		if (phy->type == B43legacy_PHYTYPE_B)
			new_phymode = B43legacy_PHYMODE_B;
		else
			new_phymode = B43legacy_PHYMODE_G;
		break;
	default:
		B43legacy_WARN_ON(1);
	}
	err = b43legacy_switch_phymode(wl, new_phymode);
	if (err)
		goto out_unlock_mutex;

	/* Disable IRQs while reconfiguring the device.
	 * This makes it possible to drop the spinlock throughout
	 * the reconfiguration process. */
	spin_lock_irqsave(&wl->irq_lock, flags);
	if (b43legacy_status(dev) < B43legacy_STAT_STARTED) {
		spin_unlock_irqrestore(&wl->irq_lock, flags);
		goto out_unlock_mutex;
	}
	b43legacy_write32(dev, B43legacy_MMIO_GEN_IRQ_MASK, 0);
	spin_unlock_irqrestore(&wl->irq_lock, flags);
	b43legacy_synchronize_irq(dev);

	/* Switch to the requested channel.
	 * The firmware takes care of races with the TX handler. */
	if (conf->chandef.chan->hw_value != phy->channel)
		b43legacy_radio_selectchannel(dev, conf->chandef.chan->hw_value,
					      0);

	dev->wl->radiotap_enabled = !!(conf->flags & IEEE80211_CONF_MONITOR);

	/* Adjust the desired TX power level. */
	if (conf->power_level != 0) {
		if (conf->power_level != phy->power_level) {
			phy->power_level = conf->power_level;
			b43legacy_phy_xmitpower(dev);
		}
	}

	/* Antennas for RX and management frame TX. */
	b43legacy_mgmtframe_txantenna(dev, antenna_tx);

	if (wl->radio_enabled != phy->radio_on) {
		if (wl->radio_enabled) {
			b43legacy_radio_turn_on(dev);
			b43legacyinfo(dev->wl, "Radio turned on by software\n");
			if (!dev->radio_hw_enable)
				b43legacyinfo(dev->wl, "The hardware RF-kill"
					      " button still turns the radio"
					      " physically off. Press the"
					      " button to turn it on.\n");
		} else {
			b43legacy_radio_turn_off(dev, 0);
			b43legacyinfo(dev->wl, "Radio turned off by"
				      " software\n");
		}
	}

	spin_lock_irqsave(&wl->irq_lock, flags);
	b43legacy_write32(dev, B43legacy_MMIO_GEN_IRQ_MASK, dev->irq_mask);
	mmiowb();
	spin_unlock_irqrestore(&wl->irq_lock, flags);
out_unlock_mutex:
	mutex_unlock(&wl->mutex);

	return err;
}