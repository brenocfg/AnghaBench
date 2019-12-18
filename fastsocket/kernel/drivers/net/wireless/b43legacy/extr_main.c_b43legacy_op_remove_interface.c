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
struct ieee80211_vif {int /*<<< orphan*/  type; } ;
struct ieee80211_hw {int dummy; } ;
struct b43legacy_wldev {int dummy; } ;
struct b43legacy_wl {int operating; int /*<<< orphan*/  mutex; int /*<<< orphan*/  irq_lock; int /*<<< orphan*/  mac_addr; struct ieee80211_vif* vif; struct b43legacy_wldev* current_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  b43legacy_adjust_opmode (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_upload_card_macaddress (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacydbg (struct b43legacy_wl*,char*,int /*<<< orphan*/ ) ; 
 struct b43legacy_wl* hw_to_b43legacy_wl (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void b43legacy_op_remove_interface(struct ieee80211_hw *hw,
					  struct ieee80211_vif *vif)
{
	struct b43legacy_wl *wl = hw_to_b43legacy_wl(hw);
	struct b43legacy_wldev *dev = wl->current_dev;
	unsigned long flags;

	b43legacydbg(wl, "Removing Interface type %d\n", vif->type);

	mutex_lock(&wl->mutex);

	B43legacy_WARN_ON(!wl->operating);
	B43legacy_WARN_ON(wl->vif != vif);
	wl->vif = NULL;

	wl->operating = false;

	spin_lock_irqsave(&wl->irq_lock, flags);
	b43legacy_adjust_opmode(dev);
	memset(wl->mac_addr, 0, ETH_ALEN);
	b43legacy_upload_card_macaddress(dev);
	spin_unlock_irqrestore(&wl->irq_lock, flags);

	mutex_unlock(&wl->mutex);
}