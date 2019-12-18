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
typedef  int u64 ;
struct zd_mc_hash {int low; int high; } ;
struct zd_mac {int pass_failed_fcs; int pass_ctrl; int /*<<< orphan*/  chip; int /*<<< orphan*/  lock; struct zd_mc_hash multicast_hash; } ;
struct ieee80211_hw {int dummy; } ;

/* Variables and functions */
 unsigned int FIF_ALLMULTI ; 
 unsigned int FIF_CONTROL ; 
 unsigned int FIF_FCSFAIL ; 
 unsigned int FIF_PROMISC_IN_BSS ; 
 unsigned int SUPPORTED_FIF_FLAGS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int set_rx_filter (struct zd_mac*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  zd_chip_set_multicast_hash (int /*<<< orphan*/ *,struct zd_mc_hash*) ; 
 struct zd_mac* zd_hw_mac (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  zd_mac_dev (struct zd_mac*) ; 
 int /*<<< orphan*/  zd_mc_add_all (struct zd_mc_hash*) ; 

__attribute__((used)) static void zd_op_configure_filter(struct ieee80211_hw *hw,
			unsigned int changed_flags,
			unsigned int *new_flags,
			u64 multicast)
{
	struct zd_mc_hash hash = {
		.low = multicast,
		.high = multicast >> 32,
	};
	struct zd_mac *mac = zd_hw_mac(hw);
	unsigned long flags;
	int r;

	/* Only deal with supported flags */
	changed_flags &= SUPPORTED_FIF_FLAGS;
	*new_flags &= SUPPORTED_FIF_FLAGS;

	/*
	 * If multicast parameter (as returned by zd_op_prepare_multicast)
	 * has changed, no bit in changed_flags is set. To handle this
	 * situation, we do not return if changed_flags is 0. If we do so,
	 * we will have some issue with IPv6 which uses multicast for link
	 * layer address resolution.
	 */
	if (*new_flags & (FIF_PROMISC_IN_BSS | FIF_ALLMULTI))
		zd_mc_add_all(&hash);

	spin_lock_irqsave(&mac->lock, flags);
	mac->pass_failed_fcs = !!(*new_flags & FIF_FCSFAIL);
	mac->pass_ctrl = !!(*new_flags & FIF_CONTROL);
	mac->multicast_hash = hash;
	spin_unlock_irqrestore(&mac->lock, flags);

	zd_chip_set_multicast_hash(&mac->chip, &hash);

	if (changed_flags & FIF_CONTROL) {
		r = set_rx_filter(mac);
		if (r)
			dev_err(zd_mac_dev(mac), "set_rx_filter error %d\n", r);
	}

	/* no handling required for FIF_OTHER_BSS as we don't currently
	 * do BSSID filtering */
	/* FIXME: in future it would be nice to enable the probe response
	 * filter (so that the driver doesn't see them) until
	 * FIF_BCN_PRBRESP_PROMISC is set. however due to atomicity here, we'd
	 * have to schedule work to enable prbresp reception, which might
	 * happen too late. For now we'll just listen and forward them all the
	 * time. */
}