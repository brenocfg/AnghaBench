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
typedef  int /*<<< orphan*/  u16 ;
struct brcms_c_info {int /*<<< orphan*/  hw; } ;
struct brcms_bss_cfg {int dummy; } ;

/* Variables and functions */
 int BCN_TMPL_LEN ; 
 int /*<<< orphan*/  D11_PHY_HDR_LEN ; 
 scalar_t__ FCS_LEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IEEE80211_STYPE_PROBE_RESP ; 
 int /*<<< orphan*/  M_PRB_RESP_FRM_LEN ; 
 int /*<<< orphan*/  T_PRS_TPL_BASE ; 
 int /*<<< orphan*/  brcms_b_write_shm (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_b_write_template_ram (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcms_c_bcn_prb_template (struct brcms_c_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct brcms_bss_cfg*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  brcms_c_enable_mac (struct brcms_c_info*) ; 
 int /*<<< orphan*/  brcms_c_mod_prb_rsp_rate_table (struct brcms_c_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcms_c_shm_ssid_upd (struct brcms_c_info*,struct brcms_bss_cfg*) ; 
 int /*<<< orphan*/  brcms_c_suspend_mac_and_wait (struct brcms_c_info*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
brcms_c_bss_update_probe_resp(struct brcms_c_info *wlc,
			      struct brcms_bss_cfg *cfg,
			      bool suspend)
{
	u16 *prb_resp;
	int len = BCN_TMPL_LEN;

	prb_resp = kmalloc(BCN_TMPL_LEN, GFP_ATOMIC);
	if (!prb_resp)
		return;

	/*
	 * write the probe response to hardware, or save in
	 * the config structure
	 */

	/* create the probe response template */
	brcms_c_bcn_prb_template(wlc, IEEE80211_STYPE_PROBE_RESP, 0,
				 cfg, prb_resp, &len);

	if (suspend)
		brcms_c_suspend_mac_and_wait(wlc);

	/* write the probe response into the template region */
	brcms_b_write_template_ram(wlc->hw, T_PRS_TPL_BASE,
				    (len + 3) & ~3, prb_resp);

	/* write the length of the probe response frame (+PLCP/-FCS) */
	brcms_b_write_shm(wlc->hw, M_PRB_RESP_FRM_LEN, (u16) len);

	/* write the SSID and SSID length */
	brcms_c_shm_ssid_upd(wlc, cfg);

	/*
	 * Write PLCP headers and durations for probe response frames
	 * at all rates. Use the actual frame length covered by the
	 * PLCP header for the call to brcms_c_mod_prb_rsp_rate_table()
	 * by subtracting the PLCP len and adding the FCS.
	 */
	len += (-D11_PHY_HDR_LEN + FCS_LEN);
	brcms_c_mod_prb_rsp_rate_table(wlc, (u16) len);

	if (suspend)
		brcms_c_enable_mac(wlc);

	kfree(prb_resp);
}