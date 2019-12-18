#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_8__ {int /*<<< orphan*/  rx_mask; } ;
struct TYPE_12__ {int ampdu_params_info; TYPE_1__ mcs; } ;
struct TYPE_9__ {int /*<<< orphan*/  rx_mask; } ;
struct TYPE_11__ {int ampdu_params_info; TYPE_2__ mcs; } ;
struct TYPE_13__ {TYPE_5__ ht_capa; TYPE_4__ ht_capa_mask; } ;
struct TYPE_14__ {TYPE_6__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_7__ u; } ;
struct TYPE_10__ {scalar_t__* rx_mask; } ;
struct ieee80211_sta_ht_cap {scalar_t__ ampdu_factor; scalar_t__ ampdu_density; TYPE_3__ mcs; int /*<<< orphan*/  ht_supported; } ;

/* Variables and functions */
 int IEEE80211_HT_AMPDU_PARM_DENSITY ; 
 int IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT ; 
 int IEEE80211_HT_AMPDU_PARM_FACTOR ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_MAX_AMSDU ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_20 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SGI_40 ; 
 int /*<<< orphan*/  IEEE80211_HT_CAP_SUP_WIDTH_20_40 ; 
 int IEEE80211_HT_MCS_MASK_LEN ; 
 int /*<<< orphan*/  __check_htcap_disable (struct ieee80211_sub_if_data*,struct ieee80211_sta_ht_cap*,int /*<<< orphan*/ ) ; 

void ieee80211_apply_htcap_overrides(struct ieee80211_sub_if_data *sdata,
				     struct ieee80211_sta_ht_cap *ht_cap)
{
	u8 *scaps = (u8 *)(&sdata->u.mgd.ht_capa.mcs.rx_mask);
	u8 *smask = (u8 *)(&sdata->u.mgd.ht_capa_mask.mcs.rx_mask);
	int i;

	if (!ht_cap->ht_supported)
		return;

	/* NOTE:  If you add more over-rides here, update register_hw
	 * ht_capa_mod_msk logic in main.c as well.
	 * And, if this method can ever change ht_cap.ht_supported, fix
	 * the check in ieee80211_add_ht_ie.
	 */

	/* check for HT over-rides, MCS rates first. */
	for (i = 0; i < IEEE80211_HT_MCS_MASK_LEN; i++) {
		u8 m = smask[i];
		ht_cap->mcs.rx_mask[i] &= ~m; /* turn off all masked bits */
		/* Add back rates that are supported */
		ht_cap->mcs.rx_mask[i] |= (m & scaps[i]);
	}

	/* Force removal of HT-40 capabilities? */
	__check_htcap_disable(sdata, ht_cap, IEEE80211_HT_CAP_SUP_WIDTH_20_40);
	__check_htcap_disable(sdata, ht_cap, IEEE80211_HT_CAP_SGI_40);

	/* Allow user to disable SGI-20 (SGI-40 is handled above) */
	__check_htcap_disable(sdata, ht_cap, IEEE80211_HT_CAP_SGI_20);

	/* Allow user to disable the max-AMSDU bit. */
	__check_htcap_disable(sdata, ht_cap, IEEE80211_HT_CAP_MAX_AMSDU);

	/* Allow user to decrease AMPDU factor */
	if (sdata->u.mgd.ht_capa_mask.ampdu_params_info &
	    IEEE80211_HT_AMPDU_PARM_FACTOR) {
		u8 n = sdata->u.mgd.ht_capa.ampdu_params_info
			& IEEE80211_HT_AMPDU_PARM_FACTOR;
		if (n < ht_cap->ampdu_factor)
			ht_cap->ampdu_factor = n;
	}

	/* Allow the user to increase AMPDU density. */
	if (sdata->u.mgd.ht_capa_mask.ampdu_params_info &
	    IEEE80211_HT_AMPDU_PARM_DENSITY) {
		u8 n = (sdata->u.mgd.ht_capa.ampdu_params_info &
			IEEE80211_HT_AMPDU_PARM_DENSITY)
			>> IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT;
		if (n > ht_cap->ampdu_density)
			ht_cap->ampdu_density = n;
	}
}