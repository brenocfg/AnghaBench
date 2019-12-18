#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct brcms_phy_lcnphy {int lcnphy_tempsense_option; scalar_t__ lcnphy_papd_rxGnCtrl_init; } ;
struct TYPE_8__ {int /*<<< orphan*/  phy_rev; } ;
struct TYPE_6__ {int /*<<< orphan*/  detach; int /*<<< orphan*/  radioloftget; int /*<<< orphan*/  txloccget; int /*<<< orphan*/  txiqccset; int /*<<< orphan*/  txiqccget; int /*<<< orphan*/  txpwrrecalc; int /*<<< orphan*/  chanset; int /*<<< orphan*/  calinit; int /*<<< orphan*/  init; } ;
struct TYPE_5__ {struct brcms_phy_lcnphy* pi_lcnphy; } ;
struct brcms_phy {int hwpwrctrl; int hwpwrctrl_capable; int temppwrctrl_capable; TYPE_4__ pubpi; TYPE_3__* sh; TYPE_2__ pi_fptr; int /*<<< orphan*/  xtalfreq; TYPE_1__ u; } ;
struct TYPE_7__ {int boardflags; int /*<<< orphan*/  sih; } ;

/* Variables and functions */
 int BFL_FEM ; 
 int BFL_NOPA ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ LCNREV_IS (int /*<<< orphan*/ ,int) ; 
 struct brcms_phy_lcnphy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  si_pmu_alp_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlc_lcnphy_get_radio_loft ; 
 int /*<<< orphan*/  wlc_lcnphy_get_tx_iqcc ; 
 int /*<<< orphan*/  wlc_lcnphy_get_tx_locc ; 
 int /*<<< orphan*/  wlc_lcnphy_set_tx_iqcc ; 
 int /*<<< orphan*/  wlc_phy_cal_init_lcnphy ; 
 int /*<<< orphan*/  wlc_phy_chanspec_set_lcnphy ; 
 int /*<<< orphan*/  wlc_phy_detach_lcnphy ; 
 int /*<<< orphan*/  wlc_phy_init_lcnphy ; 
 int /*<<< orphan*/  wlc_phy_txpower_recalc_target_lcnphy ; 
 int /*<<< orphan*/  wlc_phy_txpwr_srom_read_lcnphy (struct brcms_phy*) ; 

bool wlc_phy_attach_lcnphy(struct brcms_phy *pi)
{
	struct brcms_phy_lcnphy *pi_lcn;

	pi->u.pi_lcnphy = kzalloc(sizeof(struct brcms_phy_lcnphy), GFP_ATOMIC);
	if (pi->u.pi_lcnphy == NULL)
		return false;

	pi_lcn = pi->u.pi_lcnphy;

	if (0 == (pi->sh->boardflags & BFL_NOPA)) {
		pi->hwpwrctrl = true;
		pi->hwpwrctrl_capable = true;
	}

	pi->xtalfreq = si_pmu_alp_clock(pi->sh->sih);
	pi_lcn->lcnphy_papd_rxGnCtrl_init = 0;

	pi->pi_fptr.init = wlc_phy_init_lcnphy;
	pi->pi_fptr.calinit = wlc_phy_cal_init_lcnphy;
	pi->pi_fptr.chanset = wlc_phy_chanspec_set_lcnphy;
	pi->pi_fptr.txpwrrecalc = wlc_phy_txpower_recalc_target_lcnphy;
	pi->pi_fptr.txiqccget = wlc_lcnphy_get_tx_iqcc;
	pi->pi_fptr.txiqccset = wlc_lcnphy_set_tx_iqcc;
	pi->pi_fptr.txloccget = wlc_lcnphy_get_tx_locc;
	pi->pi_fptr.radioloftget = wlc_lcnphy_get_radio_loft;
	pi->pi_fptr.detach = wlc_phy_detach_lcnphy;

	if (!wlc_phy_txpwr_srom_read_lcnphy(pi))
		return false;

	if ((pi->sh->boardflags & BFL_FEM) &&
	    (LCNREV_IS(pi->pubpi.phy_rev, 1))) {
		if (pi_lcn->lcnphy_tempsense_option == 3) {
			pi->hwpwrctrl = true;
			pi->hwpwrctrl_capable = true;
			pi->temppwrctrl_capable = false;
		} else {
			pi->hwpwrctrl = false;
			pi->hwpwrctrl_capable = false;
			pi->temppwrctrl_capable = true;
		}
	}

	return true;
}