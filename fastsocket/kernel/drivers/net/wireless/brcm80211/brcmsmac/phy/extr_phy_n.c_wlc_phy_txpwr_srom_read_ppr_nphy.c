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
typedef  int uint ;
typedef  int u16 ;
struct ssb_sprom {int bw40po; int cddpo; int stbcpo; int bwduppo; int /*<<< orphan*/ * mcs5ghpo; int /*<<< orphan*/  ofdm5ghpo; TYPE_4__* core_pwr_info; int /*<<< orphan*/ * mcs5glpo; int /*<<< orphan*/  ofdm5glpo; int /*<<< orphan*/ * mcs5gpo; int /*<<< orphan*/  ofdm5gpo; int /*<<< orphan*/ * mcs2gpo; int /*<<< orphan*/  ofdm2gpo; int /*<<< orphan*/  cck2gpo; } ;
struct brcms_phy {int bw402gpo; int bw405gpo; int bw405glpo; int bw405ghpo; int cdd2gpo; int cdd5gpo; int cdd5glpo; int cdd5ghpo; int stbc2gpo; int stbc5gpo; int stbc5glpo; int stbc5ghpo; int bwdup2gpo; int bwdup5gpo; int bwdup5glpo; int bwdup5ghpo; int /*<<< orphan*/ * mcs5ghpo; int /*<<< orphan*/  ofdm5ghpo; TYPE_5__* nphy_pwrctrl_info; int /*<<< orphan*/ * mcs5glpo; int /*<<< orphan*/  ofdm5glpo; int /*<<< orphan*/ * mcs5gpo; int /*<<< orphan*/  ofdm5gpo; int /*<<< orphan*/ * mcs2gpo; int /*<<< orphan*/  ofdm2gpo; int /*<<< orphan*/  cck2gpo; TYPE_3__* sh; TYPE_2__* d11core; } ;
struct TYPE_10__ {int /*<<< orphan*/  idle_targ_5gh; int /*<<< orphan*/  pwrdet_5gh_b1; int /*<<< orphan*/  pwrdet_5gh_b0; int /*<<< orphan*/  pwrdet_5gh_a1; int /*<<< orphan*/  max_pwr_5gh; int /*<<< orphan*/  idle_targ_5gl; int /*<<< orphan*/  pwrdet_5gl_b1; int /*<<< orphan*/  pwrdet_5gl_b0; int /*<<< orphan*/  pwrdet_5gl_a1; int /*<<< orphan*/  max_pwr_5gl; int /*<<< orphan*/  idle_targ_5gm; int /*<<< orphan*/  pwrdet_5gm_b1; int /*<<< orphan*/  pwrdet_5gm_b0; int /*<<< orphan*/  pwrdet_5gm_a1; int /*<<< orphan*/  max_pwr_5gm; int /*<<< orphan*/  idle_targ_2g; int /*<<< orphan*/  pwrdet_2g_b1; int /*<<< orphan*/  pwrdet_2g_b0; int /*<<< orphan*/  pwrdet_2g_a1; int /*<<< orphan*/  max_pwr_2g; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pa_5gh; int /*<<< orphan*/  maxpwr_5gh; int /*<<< orphan*/ * pa_5gl; int /*<<< orphan*/  maxpwr_5gl; int /*<<< orphan*/  itssi_5g; int /*<<< orphan*/ * pa_5g; int /*<<< orphan*/  maxpwr_5g; int /*<<< orphan*/  itssi_2g; int /*<<< orphan*/ * pa_2g; int /*<<< orphan*/  maxpwr_2g; } ;
struct TYPE_8__ {int sromrev; } ;
struct TYPE_7__ {TYPE_1__* bus; } ;
struct TYPE_6__ {struct ssb_sprom sprom; } ;

/* Variables and functions */
 int CH_2G_GROUP ; 
 int CH_5G_GROUP ; 
 size_t PHY_CORE_0 ; 
 size_t PHY_CORE_1 ; 
 int /*<<< orphan*/  wlc_phy_txpwr_apply_nphy (struct brcms_phy*) ; 

__attribute__((used)) static void wlc_phy_txpwr_srom_read_ppr_nphy(struct brcms_phy *pi)
{
	u16 bw40po, cddpo, stbcpo, bwduppo;
	uint band_num;
	struct ssb_sprom *sprom = &pi->d11core->bus->sprom;

	if (pi->sh->sromrev >= 9)
		return;

	bw40po = sprom->bw40po;
	pi->bw402gpo = bw40po & 0xf;
	pi->bw405gpo = (bw40po & 0xf0) >> 4;
	pi->bw405glpo = (bw40po & 0xf00) >> 8;
	pi->bw405ghpo = (bw40po & 0xf000) >> 12;

	cddpo = sprom->cddpo;
	pi->cdd2gpo = cddpo & 0xf;
	pi->cdd5gpo = (cddpo & 0xf0) >> 4;
	pi->cdd5glpo = (cddpo & 0xf00) >> 8;
	pi->cdd5ghpo = (cddpo & 0xf000) >> 12;

	stbcpo = sprom->stbcpo;
	pi->stbc2gpo = stbcpo & 0xf;
	pi->stbc5gpo = (stbcpo & 0xf0) >> 4;
	pi->stbc5glpo = (stbcpo & 0xf00) >> 8;
	pi->stbc5ghpo = (stbcpo & 0xf000) >> 12;

	bwduppo = sprom->bwduppo;
	pi->bwdup2gpo = bwduppo & 0xf;
	pi->bwdup5gpo = (bwduppo & 0xf0) >> 4;
	pi->bwdup5glpo = (bwduppo & 0xf00) >> 8;
	pi->bwdup5ghpo = (bwduppo & 0xf000) >> 12;

	for (band_num = 0; band_num < (CH_2G_GROUP + CH_5G_GROUP);
	     band_num++) {
		switch (band_num) {
		case 0:
			pi->nphy_pwrctrl_info[PHY_CORE_0].max_pwr_2g =
				sprom->core_pwr_info[0].maxpwr_2g;
			pi->nphy_pwrctrl_info[PHY_CORE_1].max_pwr_2g =
				sprom->core_pwr_info[1].maxpwr_2g;
			pi->nphy_pwrctrl_info[PHY_CORE_0].pwrdet_2g_a1 =
				sprom->core_pwr_info[0].pa_2g[0];
			pi->nphy_pwrctrl_info[PHY_CORE_1].pwrdet_2g_a1 =
				sprom->core_pwr_info[1].pa_2g[0];
			pi->nphy_pwrctrl_info[PHY_CORE_0].pwrdet_2g_b0 =
				sprom->core_pwr_info[0].pa_2g[1];
			pi->nphy_pwrctrl_info[PHY_CORE_1].pwrdet_2g_b0 =
				sprom->core_pwr_info[1].pa_2g[1];
			pi->nphy_pwrctrl_info[PHY_CORE_0].pwrdet_2g_b1 =
				sprom->core_pwr_info[0].pa_2g[2];
			pi->nphy_pwrctrl_info[PHY_CORE_1].pwrdet_2g_b1 =
				sprom->core_pwr_info[1].pa_2g[2];
			pi->nphy_pwrctrl_info[PHY_CORE_0].idle_targ_2g =
				sprom->core_pwr_info[0].itssi_2g;
			pi->nphy_pwrctrl_info[PHY_CORE_1].idle_targ_2g =
				sprom->core_pwr_info[1].itssi_2g;

			pi->cck2gpo = sprom->cck2gpo;

			pi->ofdm2gpo = sprom->ofdm2gpo;

			pi->mcs2gpo[0] = sprom->mcs2gpo[0];
			pi->mcs2gpo[1] = sprom->mcs2gpo[1];
			pi->mcs2gpo[2] = sprom->mcs2gpo[2];
			pi->mcs2gpo[3] = sprom->mcs2gpo[3];
			pi->mcs2gpo[4] = sprom->mcs2gpo[4];
			pi->mcs2gpo[5] = sprom->mcs2gpo[5];
			pi->mcs2gpo[6] = sprom->mcs2gpo[6];
			pi->mcs2gpo[7] = sprom->mcs2gpo[7];
			break;
		case 1:

			pi->nphy_pwrctrl_info[PHY_CORE_0].max_pwr_5gm =
				sprom->core_pwr_info[0].maxpwr_5g;
			pi->nphy_pwrctrl_info[PHY_CORE_1].max_pwr_5gm =
				sprom->core_pwr_info[1].maxpwr_5g;
			pi->nphy_pwrctrl_info[PHY_CORE_0].pwrdet_5gm_a1 =
				sprom->core_pwr_info[0].pa_5g[0];
			pi->nphy_pwrctrl_info[PHY_CORE_1].pwrdet_5gm_a1 =
				sprom->core_pwr_info[1].pa_5g[0];
			pi->nphy_pwrctrl_info[PHY_CORE_0].pwrdet_5gm_b0 =
				sprom->core_pwr_info[0].pa_5g[1];
			pi->nphy_pwrctrl_info[PHY_CORE_1].pwrdet_5gm_b0 =
				sprom->core_pwr_info[1].pa_5g[1];
			pi->nphy_pwrctrl_info[PHY_CORE_0].pwrdet_5gm_b1 =
				sprom->core_pwr_info[0].pa_5g[2];
			pi->nphy_pwrctrl_info[PHY_CORE_1].pwrdet_5gm_b1 =
				sprom->core_pwr_info[1].pa_5g[2];
			pi->nphy_pwrctrl_info[PHY_CORE_0].idle_targ_5gm =
				sprom->core_pwr_info[0].itssi_5g;
			pi->nphy_pwrctrl_info[PHY_CORE_1].idle_targ_5gm =
				sprom->core_pwr_info[1].itssi_5g;

			pi->ofdm5gpo = sprom->ofdm5gpo;

			pi->mcs5gpo[0] = sprom->mcs5gpo[0];
			pi->mcs5gpo[1] = sprom->mcs5gpo[1];
			pi->mcs5gpo[2] = sprom->mcs5gpo[2];
			pi->mcs5gpo[3] = sprom->mcs5gpo[3];
			pi->mcs5gpo[4] = sprom->mcs5gpo[4];
			pi->mcs5gpo[5] = sprom->mcs5gpo[5];
			pi->mcs5gpo[6] = sprom->mcs5gpo[6];
			pi->mcs5gpo[7] = sprom->mcs5gpo[7];
			break;
		case 2:

			pi->nphy_pwrctrl_info[0].max_pwr_5gl =
				sprom->core_pwr_info[0].maxpwr_5gl;
			pi->nphy_pwrctrl_info[1].max_pwr_5gl =
				sprom->core_pwr_info[1].maxpwr_5gl;
			pi->nphy_pwrctrl_info[0].pwrdet_5gl_a1 =
				sprom->core_pwr_info[0].pa_5gl[0];
			pi->nphy_pwrctrl_info[1].pwrdet_5gl_a1 =
				sprom->core_pwr_info[1].pa_5gl[0];
			pi->nphy_pwrctrl_info[0].pwrdet_5gl_b0 =
				sprom->core_pwr_info[0].pa_5gl[1];
			pi->nphy_pwrctrl_info[1].pwrdet_5gl_b0 =
				sprom->core_pwr_info[1].pa_5gl[1];
			pi->nphy_pwrctrl_info[0].pwrdet_5gl_b1 =
				sprom->core_pwr_info[0].pa_5gl[2];
			pi->nphy_pwrctrl_info[1].pwrdet_5gl_b1 =
				sprom->core_pwr_info[1].pa_5gl[2];
			pi->nphy_pwrctrl_info[0].idle_targ_5gl = 0;
			pi->nphy_pwrctrl_info[1].idle_targ_5gl = 0;

			pi->ofdm5glpo = sprom->ofdm5glpo;

			pi->mcs5glpo[0] = sprom->mcs5glpo[0];
			pi->mcs5glpo[1] = sprom->mcs5glpo[1];
			pi->mcs5glpo[2] = sprom->mcs5glpo[2];
			pi->mcs5glpo[3] = sprom->mcs5glpo[3];
			pi->mcs5glpo[4] = sprom->mcs5glpo[4];
			pi->mcs5glpo[5] = sprom->mcs5glpo[5];
			pi->mcs5glpo[6] = sprom->mcs5glpo[6];
			pi->mcs5glpo[7] = sprom->mcs5glpo[7];
			break;
		case 3:

			pi->nphy_pwrctrl_info[0].max_pwr_5gh =
				sprom->core_pwr_info[0].maxpwr_5gh;
			pi->nphy_pwrctrl_info[1].max_pwr_5gh =
				sprom->core_pwr_info[1].maxpwr_5gh;
			pi->nphy_pwrctrl_info[0].pwrdet_5gh_a1 =
				sprom->core_pwr_info[0].pa_5gh[0];
			pi->nphy_pwrctrl_info[1].pwrdet_5gh_a1 =
				sprom->core_pwr_info[1].pa_5gh[0];
			pi->nphy_pwrctrl_info[0].pwrdet_5gh_b0 =
				sprom->core_pwr_info[0].pa_5gh[1];
			pi->nphy_pwrctrl_info[1].pwrdet_5gh_b0 =
				sprom->core_pwr_info[1].pa_5gh[1];
			pi->nphy_pwrctrl_info[0].pwrdet_5gh_b1 =
				sprom->core_pwr_info[0].pa_5gh[2];
			pi->nphy_pwrctrl_info[1].pwrdet_5gh_b1 =
				sprom->core_pwr_info[1].pa_5gh[2];
			pi->nphy_pwrctrl_info[0].idle_targ_5gh = 0;
			pi->nphy_pwrctrl_info[1].idle_targ_5gh = 0;

			pi->ofdm5ghpo = sprom->ofdm5ghpo;

			pi->mcs5ghpo[0] = sprom->mcs5ghpo[0];
			pi->mcs5ghpo[1] = sprom->mcs5ghpo[1];
			pi->mcs5ghpo[2] = sprom->mcs5ghpo[2];
			pi->mcs5ghpo[3] = sprom->mcs5ghpo[3];
			pi->mcs5ghpo[4] = sprom->mcs5ghpo[4];
			pi->mcs5ghpo[5] = sprom->mcs5ghpo[5];
			pi->mcs5ghpo[6] = sprom->mcs5ghpo[6];
			pi->mcs5ghpo[7] = sprom->mcs5ghpo[7];
			break;
		}
	}

	wlc_phy_txpwr_apply_nphy(pi);
}