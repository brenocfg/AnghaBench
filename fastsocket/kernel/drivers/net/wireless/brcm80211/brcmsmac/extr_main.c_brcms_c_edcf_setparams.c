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
typedef  int u16 ;
struct ieee80211_tx_queue_params {int aifs; void* cw_max; void* cw_min; int /*<<< orphan*/  txop; } ;
struct edcf_acparam {int ACI; int ECW; int /*<<< orphan*/  TXOP; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct brcms_c_info {int dummy; } ;

/* Variables and functions */
 int EDCF_ACI_MASK ; 
 int EDCF_ACI_SHIFT ; 
#define  EDCF_AC_BE_ACI_STA 139 
#define  EDCF_AC_BE_ECW_STA 138 
#define  EDCF_AC_BE_TXOP_STA 137 
#define  EDCF_AC_BK_ACI_STA 136 
#define  EDCF_AC_BK_ECW_STA 135 
#define  EDCF_AC_BK_TXOP_STA 134 
#define  EDCF_AC_VI_ACI_STA 133 
#define  EDCF_AC_VI_ECW_STA 132 
#define  EDCF_AC_VI_TXOP_STA 131 
#define  EDCF_AC_VO_ACI_STA 130 
#define  EDCF_AC_VO_ECW_STA 129 
#define  EDCF_AC_VO_TXOP_STA 128 
 void* EDCF_ECW2CW (int) ; 
 int EDCF_ECWMAX_MASK ; 
 int EDCF_ECWMAX_SHIFT ; 
 int EDCF_ECWMIN_MASK ; 
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  brcms_c_enable_mac (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_suspend_mac_and_wait (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_wme_setparams (struct brcms_c_info*,int,struct ieee80211_tx_queue_params*,int) ; 

__attribute__((used)) static void brcms_c_edcf_setparams(struct brcms_c_info *wlc, bool suspend)
{
	u16 aci;
	int i_ac;
	struct ieee80211_tx_queue_params txq_pars;
	static const struct edcf_acparam default_edcf_acparams[] = {
		 {EDCF_AC_BE_ACI_STA, EDCF_AC_BE_ECW_STA, EDCF_AC_BE_TXOP_STA},
		 {EDCF_AC_BK_ACI_STA, EDCF_AC_BK_ECW_STA, EDCF_AC_BK_TXOP_STA},
		 {EDCF_AC_VI_ACI_STA, EDCF_AC_VI_ECW_STA, EDCF_AC_VI_TXOP_STA},
		 {EDCF_AC_VO_ACI_STA, EDCF_AC_VO_ECW_STA, EDCF_AC_VO_TXOP_STA}
	}; /* ucode needs these parameters during its initialization */
	const struct edcf_acparam *edcf_acp = &default_edcf_acparams[0];

	for (i_ac = 0; i_ac < IEEE80211_NUM_ACS; i_ac++, edcf_acp++) {
		/* find out which ac this set of params applies to */
		aci = (edcf_acp->ACI & EDCF_ACI_MASK) >> EDCF_ACI_SHIFT;

		/* fill in shm ac params struct */
		txq_pars.txop = edcf_acp->TXOP;
		txq_pars.aifs = edcf_acp->ACI;

		/* CWmin = 2^(ECWmin) - 1 */
		txq_pars.cw_min = EDCF_ECW2CW(edcf_acp->ECW & EDCF_ECWMIN_MASK);
		/* CWmax = 2^(ECWmax) - 1 */
		txq_pars.cw_max = EDCF_ECW2CW((edcf_acp->ECW & EDCF_ECWMAX_MASK)
					    >> EDCF_ECWMAX_SHIFT);
		brcms_c_wme_setparams(wlc, aci, &txq_pars, suspend);
	}

	if (suspend) {
		brcms_c_suspend_mac_and_wait(wlc);
		brcms_c_enable_mac(wlc);
	}
}