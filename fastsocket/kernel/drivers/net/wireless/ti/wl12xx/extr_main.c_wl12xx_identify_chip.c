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
struct TYPE_7__ {int id; } ;
struct TYPE_5__ {int /*<<< orphan*/  mem; } ;
struct wl1271 {int quirks; int /*<<< orphan*/  ba_rx_session_count_max; int /*<<< orphan*/  max_channels_5; int /*<<< orphan*/  sched_scan_templ_id_5; int /*<<< orphan*/  sched_scan_templ_id_2_4; int /*<<< orphan*/  scan_templ_id_5; int /*<<< orphan*/  scan_templ_id_2_4; TYPE_3__ chip; void* mr_fw_name; void* sr_fw_name; int /*<<< orphan*/  plt_fw_name; TYPE_2__* ops; TYPE_1__ conf; } ;
struct TYPE_8__ {int /*<<< orphan*/  mem_wl127x; } ;
struct TYPE_6__ {void* prepare_read; } ;

/* Variables and functions */
#define  CHIP_ID_127X_PG10 131 
#define  CHIP_ID_127X_PG20 130 
#define  CHIP_ID_128X_PG10 129 
#define  CHIP_ID_128X_PG20 128 
 int /*<<< orphan*/  CMD_TEMPL_APP_PROBE_REQ_2_4_LEGACY ; 
 int /*<<< orphan*/  CMD_TEMPL_APP_PROBE_REQ_5_LEGACY ; 
 int /*<<< orphan*/  CMD_TEMPL_CFG_PROBE_REQ_2_4 ; 
 int /*<<< orphan*/  CMD_TEMPL_CFG_PROBE_REQ_5 ; 
 int /*<<< orphan*/  DEBUG_BOOT ; 
 int ENODEV ; 
 int /*<<< orphan*/  WL127X_CHIP_VER ; 
 void* WL127X_FW_NAME_MULTI ; 
 void* WL127X_FW_NAME_SINGLE ; 
 int /*<<< orphan*/  WL127X_IFTYPE_MR_VER ; 
 int /*<<< orphan*/  WL127X_IFTYPE_SR_VER ; 
 int /*<<< orphan*/  WL127X_MAJOR_MR_VER ; 
 int /*<<< orphan*/  WL127X_MAJOR_SR_VER ; 
 int /*<<< orphan*/  WL127X_MINOR_MR_VER ; 
 int /*<<< orphan*/  WL127X_MINOR_SR_VER ; 
 int /*<<< orphan*/  WL127X_PLT_FW_NAME ; 
 int /*<<< orphan*/  WL127X_SUBTYPE_MR_VER ; 
 int /*<<< orphan*/  WL127X_SUBTYPE_SR_VER ; 
 int /*<<< orphan*/  WL128X_CHIP_VER ; 
 void* WL128X_FW_NAME_MULTI ; 
 void* WL128X_FW_NAME_SINGLE ; 
 int /*<<< orphan*/  WL128X_IFTYPE_MR_VER ; 
 int /*<<< orphan*/  WL128X_IFTYPE_SR_VER ; 
 int /*<<< orphan*/  WL128X_MAJOR_MR_VER ; 
 int /*<<< orphan*/  WL128X_MAJOR_SR_VER ; 
 int /*<<< orphan*/  WL128X_MINOR_MR_VER ; 
 int /*<<< orphan*/  WL128X_MINOR_SR_VER ; 
 int /*<<< orphan*/  WL128X_PLT_FW_NAME ; 
 int /*<<< orphan*/  WL128X_SUBTYPE_MR_VER ; 
 int /*<<< orphan*/  WL128X_SUBTYPE_SR_VER ; 
 int /*<<< orphan*/  WL12XX_MAX_CHANNELS_5GHZ ; 
 int /*<<< orphan*/  WL12XX_RX_BA_MAX_SESSIONS ; 
 int WLCORE_QUIRK_AP_ZERO_SESSION_ID ; 
 int WLCORE_QUIRK_DUAL_PROBE_TMPL ; 
 int WLCORE_QUIRK_LEGACY_NVS ; 
 int WLCORE_QUIRK_START_STA_FAILS ; 
 int WLCORE_QUIRK_TKIP_HEADER_SPACE ; 
 int WLCORE_QUIRK_TX_BLOCKSIZE_ALIGN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wl1271_warning (char*,int) ; 
 void* wl127x_prepare_read ; 
 TYPE_4__ wl12xx_default_priv_conf ; 
 int /*<<< orphan*/  wlcore_set_min_fw_ver (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl12xx_identify_chip(struct wl1271 *wl)
{
	int ret = 0;

	switch (wl->chip.id) {
	case CHIP_ID_127X_PG10:
		wl1271_warning("chip id 0x%x (1271 PG10) support is obsolete",
			       wl->chip.id);

		wl->quirks |= WLCORE_QUIRK_LEGACY_NVS |
			      WLCORE_QUIRK_DUAL_PROBE_TMPL |
			      WLCORE_QUIRK_TKIP_HEADER_SPACE |
			      WLCORE_QUIRK_START_STA_FAILS |
			      WLCORE_QUIRK_AP_ZERO_SESSION_ID;
		wl->sr_fw_name = WL127X_FW_NAME_SINGLE;
		wl->mr_fw_name = WL127X_FW_NAME_MULTI;
		memcpy(&wl->conf.mem, &wl12xx_default_priv_conf.mem_wl127x,
		       sizeof(wl->conf.mem));

		/* read data preparation is only needed by wl127x */
		wl->ops->prepare_read = wl127x_prepare_read;

		wlcore_set_min_fw_ver(wl, WL127X_CHIP_VER,
			      WL127X_IFTYPE_SR_VER,  WL127X_MAJOR_SR_VER,
			      WL127X_SUBTYPE_SR_VER, WL127X_MINOR_SR_VER,
			      WL127X_IFTYPE_MR_VER,  WL127X_MAJOR_MR_VER,
			      WL127X_SUBTYPE_MR_VER, WL127X_MINOR_MR_VER);
		break;

	case CHIP_ID_127X_PG20:
		wl1271_debug(DEBUG_BOOT, "chip id 0x%x (1271 PG20)",
			     wl->chip.id);

		wl->quirks |= WLCORE_QUIRK_LEGACY_NVS |
			      WLCORE_QUIRK_DUAL_PROBE_TMPL |
			      WLCORE_QUIRK_TKIP_HEADER_SPACE |
			      WLCORE_QUIRK_START_STA_FAILS |
			      WLCORE_QUIRK_AP_ZERO_SESSION_ID;
		wl->plt_fw_name = WL127X_PLT_FW_NAME;
		wl->sr_fw_name = WL127X_FW_NAME_SINGLE;
		wl->mr_fw_name = WL127X_FW_NAME_MULTI;
		memcpy(&wl->conf.mem, &wl12xx_default_priv_conf.mem_wl127x,
		       sizeof(wl->conf.mem));

		/* read data preparation is only needed by wl127x */
		wl->ops->prepare_read = wl127x_prepare_read;

		wlcore_set_min_fw_ver(wl, WL127X_CHIP_VER,
			      WL127X_IFTYPE_SR_VER,  WL127X_MAJOR_SR_VER,
			      WL127X_SUBTYPE_SR_VER, WL127X_MINOR_SR_VER,
			      WL127X_IFTYPE_MR_VER,  WL127X_MAJOR_MR_VER,
			      WL127X_SUBTYPE_MR_VER, WL127X_MINOR_MR_VER);
		break;

	case CHIP_ID_128X_PG20:
		wl1271_debug(DEBUG_BOOT, "chip id 0x%x (1283 PG20)",
			     wl->chip.id);
		wl->plt_fw_name = WL128X_PLT_FW_NAME;
		wl->sr_fw_name = WL128X_FW_NAME_SINGLE;
		wl->mr_fw_name = WL128X_FW_NAME_MULTI;

		/* wl128x requires TX blocksize alignment */
		wl->quirks |= WLCORE_QUIRK_TX_BLOCKSIZE_ALIGN |
			      WLCORE_QUIRK_DUAL_PROBE_TMPL |
			      WLCORE_QUIRK_TKIP_HEADER_SPACE |
			      WLCORE_QUIRK_START_STA_FAILS |
			      WLCORE_QUIRK_AP_ZERO_SESSION_ID;

		wlcore_set_min_fw_ver(wl, WL128X_CHIP_VER,
			      WL128X_IFTYPE_SR_VER,  WL128X_MAJOR_SR_VER,
			      WL128X_SUBTYPE_SR_VER, WL128X_MINOR_SR_VER,
			      WL128X_IFTYPE_MR_VER,  WL128X_MAJOR_MR_VER,
			      WL128X_SUBTYPE_MR_VER, WL128X_MINOR_MR_VER);
		break;
	case CHIP_ID_128X_PG10:
	default:
		wl1271_warning("unsupported chip id: 0x%x", wl->chip.id);
		ret = -ENODEV;
		goto out;
	}

	/* common settings */
	wl->scan_templ_id_2_4 = CMD_TEMPL_APP_PROBE_REQ_2_4_LEGACY;
	wl->scan_templ_id_5 = CMD_TEMPL_APP_PROBE_REQ_5_LEGACY;
	wl->sched_scan_templ_id_2_4 = CMD_TEMPL_CFG_PROBE_REQ_2_4;
	wl->sched_scan_templ_id_5 = CMD_TEMPL_CFG_PROBE_REQ_5;
	wl->max_channels_5 = WL12XX_MAX_CHANNELS_5GHZ;
	wl->ba_rx_session_count_max = WL12XX_RX_BA_MAX_SESSIONS;
out:
	return ret;
}