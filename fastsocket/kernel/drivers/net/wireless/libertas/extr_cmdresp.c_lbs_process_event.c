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
typedef  int u32 ;
struct lbs_private {int /*<<< orphan*/  sync_channel; int /*<<< orphan*/  mode; int /*<<< orphan*/  mesh_dev; int /*<<< orphan*/  tx_pending_len; int /*<<< orphan*/  mesh_open; int /*<<< orphan*/  mesh_connect_status; int /*<<< orphan*/  mesh_autostart_enabled; int /*<<< orphan*/  needtowakeup; int /*<<< orphan*/  psstate; } ;

/* Variables and functions */
 int /*<<< orphan*/  IW_MODE_ADHOC ; 
 int /*<<< orphan*/  LBS_CONNECTED ; 
 int /*<<< orphan*/  LBS_DEB_CMD ; 
#define  MACREG_INT_CODE_ADHOC_BCN_LOST 145 
#define  MACREG_INT_CODE_DEAUTHENTICATED 144 
#define  MACREG_INT_CODE_DISASSOCIATED 143 
#define  MACREG_INT_CODE_HOST_AWAKE 142 
#define  MACREG_INT_CODE_INIT_DONE 141 
#define  MACREG_INT_CODE_LINK_LOST_NO_SCAN 140 
#define  MACREG_INT_CODE_LINK_SENSED 139 
#define  MACREG_INT_CODE_MAX_FAIL 138 
#define  MACREG_INT_CODE_MESH_AUTO_STARTED 137 
#define  MACREG_INT_CODE_MIB_CHANGED 136 
#define  MACREG_INT_CODE_MIC_ERR_MULTICAST 135 
#define  MACREG_INT_CODE_MIC_ERR_UNICAST 134 
#define  MACREG_INT_CODE_PS_AWAKE 133 
#define  MACREG_INT_CODE_PS_SLEEP 132 
#define  MACREG_INT_CODE_RSSI_HIGH 131 
#define  MACREG_INT_CODE_RSSI_LOW 130 
#define  MACREG_INT_CODE_SNR_HIGH 129 
#define  MACREG_INT_CODE_SNR_LOW 128 
 int /*<<< orphan*/  PS_STATE_AWAKE ; 
 int /*<<< orphan*/  PS_STATE_FULL_POWER ; 
 int /*<<< orphan*/  PS_STATE_PRE_SLEEP ; 
 int /*<<< orphan*/  handle_mic_failureevent (struct lbs_private*,int const) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*) ; 
 int /*<<< orphan*/  lbs_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lbs_mac_event_disconnected (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_pr_alert (char*,...) ; 
 int /*<<< orphan*/  lbs_pr_info (char*) ; 
 int /*<<< orphan*/  lbs_ps_confirm_sleep (struct lbs_private*) ; 
 int /*<<< orphan*/  lbs_ps_wakeup (struct lbs_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_send_confirmwake (struct lbs_private*) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

int lbs_process_event(struct lbs_private *priv, u32 event)
{
	int ret = 0;

	lbs_deb_enter(LBS_DEB_CMD);

	switch (event) {
	case MACREG_INT_CODE_LINK_SENSED:
		lbs_deb_cmd("EVENT: link sensed\n");
		break;

	case MACREG_INT_CODE_DEAUTHENTICATED:
		lbs_deb_cmd("EVENT: deauthenticated\n");
		lbs_mac_event_disconnected(priv);
		break;

	case MACREG_INT_CODE_DISASSOCIATED:
		lbs_deb_cmd("EVENT: disassociated\n");
		lbs_mac_event_disconnected(priv);
		break;

	case MACREG_INT_CODE_LINK_LOST_NO_SCAN:
		lbs_deb_cmd("EVENT: link lost\n");
		lbs_mac_event_disconnected(priv);
		break;

	case MACREG_INT_CODE_PS_SLEEP:
		lbs_deb_cmd("EVENT: ps sleep\n");

		/* handle unexpected PS SLEEP event */
		if (priv->psstate == PS_STATE_FULL_POWER) {
			lbs_deb_cmd(
			       "EVENT: in FULL POWER mode, ignoreing PS_SLEEP\n");
			break;
		}
		priv->psstate = PS_STATE_PRE_SLEEP;

		lbs_ps_confirm_sleep(priv);

		break;

	case MACREG_INT_CODE_HOST_AWAKE:
		lbs_deb_cmd("EVENT: host awake\n");
		lbs_send_confirmwake(priv);
		break;

	case MACREG_INT_CODE_PS_AWAKE:
		lbs_deb_cmd("EVENT: ps awake\n");
		/* handle unexpected PS AWAKE event */
		if (priv->psstate == PS_STATE_FULL_POWER) {
			lbs_deb_cmd(
			       "EVENT: In FULL POWER mode - ignore PS AWAKE\n");
			break;
		}

		priv->psstate = PS_STATE_AWAKE;

		if (priv->needtowakeup) {
			/*
			 * wait for the command processing to finish
			 * before resuming sending
			 * priv->needtowakeup will be set to FALSE
			 * in lbs_ps_wakeup()
			 */
			lbs_deb_cmd("waking up ...\n");
			lbs_ps_wakeup(priv, 0);
		}
		break;

	case MACREG_INT_CODE_MIC_ERR_UNICAST:
		lbs_deb_cmd("EVENT: UNICAST MIC ERROR\n");
		handle_mic_failureevent(priv, MACREG_INT_CODE_MIC_ERR_UNICAST);
		break;

	case MACREG_INT_CODE_MIC_ERR_MULTICAST:
		lbs_deb_cmd("EVENT: MULTICAST MIC ERROR\n");
		handle_mic_failureevent(priv, MACREG_INT_CODE_MIC_ERR_MULTICAST);
		break;

	case MACREG_INT_CODE_MIB_CHANGED:
		lbs_deb_cmd("EVENT: MIB CHANGED\n");
		break;
	case MACREG_INT_CODE_INIT_DONE:
		lbs_deb_cmd("EVENT: INIT DONE\n");
		break;
	case MACREG_INT_CODE_ADHOC_BCN_LOST:
		lbs_deb_cmd("EVENT: ADHOC beacon lost\n");
		break;
	case MACREG_INT_CODE_RSSI_LOW:
		lbs_pr_alert("EVENT: rssi low\n");
		break;
	case MACREG_INT_CODE_SNR_LOW:
		lbs_pr_alert("EVENT: snr low\n");
		break;
	case MACREG_INT_CODE_MAX_FAIL:
		lbs_pr_alert("EVENT: max fail\n");
		break;
	case MACREG_INT_CODE_RSSI_HIGH:
		lbs_pr_alert("EVENT: rssi high\n");
		break;
	case MACREG_INT_CODE_SNR_HIGH:
		lbs_pr_alert("EVENT: snr high\n");
		break;

	case MACREG_INT_CODE_MESH_AUTO_STARTED:
		/* Ignore spurious autostart events if autostart is disabled */
		if (!priv->mesh_autostart_enabled) {
			lbs_pr_info("EVENT: MESH_AUTO_STARTED (ignoring)\n");
			break;
		}
		lbs_pr_info("EVENT: MESH_AUTO_STARTED\n");
		priv->mesh_connect_status = LBS_CONNECTED;
		if (priv->mesh_open) {
			netif_carrier_on(priv->mesh_dev);
			if (!priv->tx_pending_len)
				netif_wake_queue(priv->mesh_dev);
		}
		priv->mode = IW_MODE_ADHOC;
		schedule_work(&priv->sync_channel);
		break;

	default:
		lbs_pr_alert("EVENT: unknown event id %d\n", event);
		break;
	}

	lbs_deb_leave_args(LBS_DEB_CMD, "ret %d", ret);
	return ret;
}