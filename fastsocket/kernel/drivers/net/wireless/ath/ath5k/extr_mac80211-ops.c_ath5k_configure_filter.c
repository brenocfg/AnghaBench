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
typedef  int u32 ;
struct ieee80211_hw {struct ath5k_hw* priv; } ;
struct ath5k_vif_iter_data {int n_stas; int need_set_hw_addr; int /*<<< orphan*/ * hw_macaddr; } ;
struct ath5k_hw {int nvifs; int opmode; int filter_flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  hw; int /*<<< orphan*/  assoc; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int AR5K_RX_FILTER_BCAST ; 
 int AR5K_RX_FILTER_BEACON ; 
 int AR5K_RX_FILTER_CONTROL ; 
 int AR5K_RX_FILTER_MCAST ; 
 int AR5K_RX_FILTER_PHYERR ; 
 int AR5K_RX_FILTER_PROBEREQ ; 
 int AR5K_RX_FILTER_PROM ; 
 int AR5K_RX_FILTER_UCAST ; 
 int /*<<< orphan*/  ATH_STAT_PROMISC ; 
 unsigned int FIF_ALLMULTI ; 
 unsigned int FIF_BCN_PRBRESP_PROMISC ; 
 unsigned int FIF_CONTROL ; 
 unsigned int FIF_FCSFAIL ; 
 unsigned int FIF_OTHER_BSS ; 
 unsigned int FIF_PLCPFAIL ; 
 unsigned int FIF_PROMISC_IN_BSS ; 
 int /*<<< orphan*/  IEEE80211_IFACE_ITER_RESUME_ALL ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
#define  NL80211_IFTYPE_STATION 128 
 unsigned int SUPPORTED_FIF_FLAGS ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ath5k_hw_get_rx_filter (struct ath5k_hw*) ; 
 int /*<<< orphan*/  ath5k_hw_set_mcast_filter (struct ath5k_hw*,int,int) ; 
 int /*<<< orphan*/  ath5k_hw_set_rx_filter (struct ath5k_hw*,int) ; 
 int /*<<< orphan*/  ath5k_vif_iter ; 
 int /*<<< orphan*/  ieee80211_iterate_active_interfaces_atomic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ath5k_vif_iter_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath5k_configure_filter(struct ieee80211_hw *hw, unsigned int changed_flags,
		       unsigned int *new_flags, u64 multicast)
{
#define SUPPORTED_FIF_FLAGS \
	(FIF_PROMISC_IN_BSS |  FIF_ALLMULTI | FIF_FCSFAIL | \
	FIF_PLCPFAIL | FIF_CONTROL | FIF_OTHER_BSS | \
	FIF_BCN_PRBRESP_PROMISC)

	struct ath5k_hw *ah = hw->priv;
	u32 mfilt[2], rfilt;
	struct ath5k_vif_iter_data iter_data; /* to count STA interfaces */

	mutex_lock(&ah->lock);

	mfilt[0] = multicast;
	mfilt[1] = multicast >> 32;

	/* Only deal with supported flags */
	changed_flags &= SUPPORTED_FIF_FLAGS;
	*new_flags &= SUPPORTED_FIF_FLAGS;

	/* If HW detects any phy or radar errors, leave those filters on.
	 * Also, always enable Unicast, Broadcasts and Multicast
	 * XXX: move unicast, bssid broadcasts and multicast to mac80211 */
	rfilt = (ath5k_hw_get_rx_filter(ah) & (AR5K_RX_FILTER_PHYERR)) |
		(AR5K_RX_FILTER_UCAST | AR5K_RX_FILTER_BCAST |
		AR5K_RX_FILTER_MCAST);

	if (changed_flags & (FIF_PROMISC_IN_BSS | FIF_OTHER_BSS)) {
		if (*new_flags & FIF_PROMISC_IN_BSS)
			__set_bit(ATH_STAT_PROMISC, ah->status);
		else
			__clear_bit(ATH_STAT_PROMISC, ah->status);
	}

	if (test_bit(ATH_STAT_PROMISC, ah->status))
		rfilt |= AR5K_RX_FILTER_PROM;

	/* Note, AR5K_RX_FILTER_MCAST is already enabled */
	if (*new_flags & FIF_ALLMULTI) {
		mfilt[0] =  ~0;
		mfilt[1] =  ~0;
	}

	/* This is the best we can do */
	if (*new_flags & (FIF_FCSFAIL | FIF_PLCPFAIL))
		rfilt |= AR5K_RX_FILTER_PHYERR;

	/* FIF_BCN_PRBRESP_PROMISC really means to enable beacons
	* and probes for any BSSID */
	if ((*new_flags & FIF_BCN_PRBRESP_PROMISC) || (ah->nvifs > 1))
		rfilt |= AR5K_RX_FILTER_BEACON;

	/* FIF_CONTROL doc says that if FIF_PROMISC_IN_BSS is not
	 * set we should only pass on control frames for this
	 * station. This needs testing. I believe right now this
	 * enables *all* control frames, which is OK.. but
	 * but we should see if we can improve on granularity */
	if (*new_flags & FIF_CONTROL)
		rfilt |= AR5K_RX_FILTER_CONTROL;

	/* Additional settings per mode -- this is per ath5k */

	/* XXX move these to mac80211, and add a beacon IFF flag to mac80211 */

	switch (ah->opmode) {
	case NL80211_IFTYPE_MESH_POINT:
		rfilt |= AR5K_RX_FILTER_CONTROL |
			 AR5K_RX_FILTER_BEACON |
			 AR5K_RX_FILTER_PROBEREQ |
			 AR5K_RX_FILTER_PROM;
		break;
	case NL80211_IFTYPE_AP:
	case NL80211_IFTYPE_ADHOC:
		rfilt |= AR5K_RX_FILTER_PROBEREQ |
			 AR5K_RX_FILTER_BEACON;
		break;
	case NL80211_IFTYPE_STATION:
		if (ah->assoc)
			rfilt |= AR5K_RX_FILTER_BEACON;
	default:
		break;
	}

	iter_data.hw_macaddr = NULL;
	iter_data.n_stas = 0;
	iter_data.need_set_hw_addr = false;
	ieee80211_iterate_active_interfaces_atomic(
		ah->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
		ath5k_vif_iter, &iter_data);

	/* Set up RX Filter */
	if (iter_data.n_stas > 1) {
		/* If you have multiple STA interfaces connected to
		 * different APs, ARPs are not received (most of the time?)
		 * Enabling PROMISC appears to fix that problem.
		 */
		rfilt |= AR5K_RX_FILTER_PROM;
	}

	/* Set filters */
	ath5k_hw_set_rx_filter(ah, rfilt);

	/* Set multicast bits */
	ath5k_hw_set_mcast_filter(ah, mfilt[0], mfilt[1]);
	/* Set the cached hw filter flags, this will later actually
	 * be set in HW */
	ah->filter_flags = rfilt;

	mutex_unlock(&ah->lock);
}