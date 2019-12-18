#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct brcms_c_info {int shortslot; int include_legacy_erp; TYPE_2__* pub; int /*<<< orphan*/  LRL; int /*<<< orphan*/  SRL; int /*<<< orphan*/  LFBL; int /*<<< orphan*/  SFBL; int /*<<< orphan*/  RTSThresh; void** fragthresh; void* usr_fragthresh; int /*<<< orphan*/  prb_resp_timeout; TYPE_1__* stf; int /*<<< orphan*/  shortslot_override; int /*<<< orphan*/  chanspec; } ;
struct TYPE_4__ {scalar_t__ bcmerror; int /*<<< orphan*/  _ampdu; } ;
struct TYPE_3__ {int /*<<< orphan*/  txant; int /*<<< orphan*/  ant_rx_ovr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMPDU_AGG_HOST ; 
 int /*<<< orphan*/  ANT_RX_DIV_DEF ; 
 int /*<<< orphan*/  ANT_TX_DEF ; 
 int AUTO ; 
 int BRCMS_N_PROTECTION_OFF ; 
 int /*<<< orphan*/  BRCMS_PRB_RESP_TIMEOUT ; 
 int BRCMS_PROTECTION_AUTO ; 
 int BRCMS_PROTECTION_CTL_OVERLAP ; 
 int /*<<< orphan*/  BRCMS_PROT_G_OVR ; 
 int /*<<< orphan*/  BRCMS_PROT_G_SPEC ; 
 int /*<<< orphan*/  BRCMS_PROT_N_CFG ; 
 int /*<<< orphan*/  BRCMS_PROT_N_CFG_OVR ; 
 int /*<<< orphan*/  BRCMS_PROT_N_NONGF ; 
 int /*<<< orphan*/  BRCMS_PROT_N_NONGF_OVR ; 
 int /*<<< orphan*/  BRCMS_PROT_N_PAM_OVR ; 
 int /*<<< orphan*/  BRCMS_PROT_OVERLAP ; 
 int /*<<< orphan*/  BRCMS_SHORTSLOT_AUTO ; 
 void* DOT11_DEFAULT_FRAG_LEN ; 
 int /*<<< orphan*/  DOT11_DEFAULT_RTS_LEN ; 
 int NFIFO ; 
 int /*<<< orphan*/  RETRY_LONG_DEF ; 
 int /*<<< orphan*/  RETRY_LONG_FB ; 
 int /*<<< orphan*/  RETRY_SHORT_DEF ; 
 int /*<<< orphan*/  RETRY_SHORT_FB ; 
 int /*<<< orphan*/  brcms_c_protection_upd (struct brcms_c_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ch20mhz_chspec (int) ; 

__attribute__((used)) static void brcms_c_info_init(struct brcms_c_info *wlc, int unit)
{
	int i;

	/* Save our copy of the chanspec */
	wlc->chanspec = ch20mhz_chspec(1);

	/* various 802.11g modes */
	wlc->shortslot = false;
	wlc->shortslot_override = BRCMS_SHORTSLOT_AUTO;

	brcms_c_protection_upd(wlc, BRCMS_PROT_G_OVR, BRCMS_PROTECTION_AUTO);
	brcms_c_protection_upd(wlc, BRCMS_PROT_G_SPEC, false);

	brcms_c_protection_upd(wlc, BRCMS_PROT_N_CFG_OVR,
			       BRCMS_PROTECTION_AUTO);
	brcms_c_protection_upd(wlc, BRCMS_PROT_N_CFG, BRCMS_N_PROTECTION_OFF);
	brcms_c_protection_upd(wlc, BRCMS_PROT_N_NONGF_OVR,
			       BRCMS_PROTECTION_AUTO);
	brcms_c_protection_upd(wlc, BRCMS_PROT_N_NONGF, false);
	brcms_c_protection_upd(wlc, BRCMS_PROT_N_PAM_OVR, AUTO);

	brcms_c_protection_upd(wlc, BRCMS_PROT_OVERLAP,
			       BRCMS_PROTECTION_CTL_OVERLAP);

	/* 802.11g draft 4.0 NonERP elt advertisement */
	wlc->include_legacy_erp = true;

	wlc->stf->ant_rx_ovr = ANT_RX_DIV_DEF;
	wlc->stf->txant = ANT_TX_DEF;

	wlc->prb_resp_timeout = BRCMS_PRB_RESP_TIMEOUT;

	wlc->usr_fragthresh = DOT11_DEFAULT_FRAG_LEN;
	for (i = 0; i < NFIFO; i++)
		wlc->fragthresh[i] = DOT11_DEFAULT_FRAG_LEN;
	wlc->RTSThresh = DOT11_DEFAULT_RTS_LEN;

	/* default rate fallback retry limits */
	wlc->SFBL = RETRY_SHORT_FB;
	wlc->LFBL = RETRY_LONG_FB;

	/* default mac retry limits */
	wlc->SRL = RETRY_SHORT_DEF;
	wlc->LRL = RETRY_LONG_DEF;

	/* WME QoS mode is Auto by default */
	wlc->pub->_ampdu = AMPDU_AGG_HOST;
	wlc->pub->bcmerror = 0;
}