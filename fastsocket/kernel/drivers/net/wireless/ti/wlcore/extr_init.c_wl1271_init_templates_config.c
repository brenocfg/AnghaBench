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
struct wl12xx_ps_poll_template {int dummy; } ;
struct wl12xx_null_data_template {int dummy; } ;
struct wl12xx_disconn_template {int dummy; } ;
struct wl12xx_arp_rsp_template {int dummy; } ;
struct wl1271 {int quirks; int /*<<< orphan*/  sched_scan_templ_id_5; int /*<<< orphan*/  sched_scan_templ_id_2_4; int /*<<< orphan*/  scan_templ_id_5; int /*<<< orphan*/  scan_templ_id_2_4; } ;
struct ieee80211_qos_hdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_TEMPL_AP_BEACON ; 
 int /*<<< orphan*/  CMD_TEMPL_AP_PROBE_RESPONSE ; 
 int /*<<< orphan*/  CMD_TEMPL_ARP_RSP ; 
 int /*<<< orphan*/  CMD_TEMPL_BEACON ; 
 int /*<<< orphan*/  CMD_TEMPL_DEAUTH_AP ; 
 int /*<<< orphan*/  CMD_TEMPL_KLV ; 
 int /*<<< orphan*/  CMD_TEMPL_NULL_DATA ; 
 int /*<<< orphan*/  CMD_TEMPL_PROBE_RESPONSE ; 
 int /*<<< orphan*/  CMD_TEMPL_PS_POLL ; 
 int /*<<< orphan*/  CMD_TEMPL_QOS_NULL_DATA ; 
 int WL1271_CMD_TEMPL_DFLT_SIZE ; 
 int WL1271_CMD_TEMPL_MAX_SIZE ; 
 int WL1271_EXTRA_SPACE_MAX ; 
 int /*<<< orphan*/  WL1271_RATE_AUTOMATIC ; 
 int /*<<< orphan*/  WL12XX_INVALID_ROLE_ID ; 
 int WLCORE_MAX_KLV_TEMPLATES ; 
 int WLCORE_QUIRK_DUAL_PROBE_TMPL ; 
 int wl1271_cmd_template_set (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 

int wl1271_init_templates_config(struct wl1271 *wl)
{
	int ret, i;
	size_t max_size;

	/* send empty templates for fw memory reservation */
	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      wl->scan_templ_id_2_4, NULL,
				      WL1271_CMD_TEMPL_MAX_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      wl->scan_templ_id_5,
				      NULL, WL1271_CMD_TEMPL_MAX_SIZE, 0,
				      WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	if (wl->quirks & WLCORE_QUIRK_DUAL_PROBE_TMPL) {
		ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
					      wl->sched_scan_templ_id_2_4,
					      NULL,
					      WL1271_CMD_TEMPL_MAX_SIZE,
					      0, WL1271_RATE_AUTOMATIC);
		if (ret < 0)
			return ret;

		ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
					      wl->sched_scan_templ_id_5,
					      NULL,
					      WL1271_CMD_TEMPL_MAX_SIZE,
					      0, WL1271_RATE_AUTOMATIC);
		if (ret < 0)
			return ret;
	}

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_NULL_DATA, NULL,
				      sizeof(struct wl12xx_null_data_template),
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_PS_POLL, NULL,
				      sizeof(struct wl12xx_ps_poll_template),
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_QOS_NULL_DATA, NULL,
				      sizeof
				      (struct ieee80211_qos_hdr),
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_PROBE_RESPONSE, NULL,
				      WL1271_CMD_TEMPL_DFLT_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_BEACON, NULL,
				      WL1271_CMD_TEMPL_DFLT_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	max_size = sizeof(struct wl12xx_arp_rsp_template) +
		   WL1271_EXTRA_SPACE_MAX;
	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_ARP_RSP, NULL,
				      max_size,
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	/*
	 * Put very large empty placeholders for all templates. These
	 * reserve memory for later.
	 */
	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_AP_PROBE_RESPONSE, NULL,
				      WL1271_CMD_TEMPL_MAX_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_AP_BEACON, NULL,
				      WL1271_CMD_TEMPL_MAX_SIZE,
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
				      CMD_TEMPL_DEAUTH_AP, NULL,
				      sizeof
				      (struct wl12xx_disconn_template),
				      0, WL1271_RATE_AUTOMATIC);
	if (ret < 0)
		return ret;

	for (i = 0; i < WLCORE_MAX_KLV_TEMPLATES; i++) {
		ret = wl1271_cmd_template_set(wl, WL12XX_INVALID_ROLE_ID,
					      CMD_TEMPL_KLV, NULL,
					      sizeof(struct ieee80211_qos_hdr),
					      i, WL1271_RATE_AUTOMATIC);
		if (ret < 0)
			return ret;
	}

	return 0;
}