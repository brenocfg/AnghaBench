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
typedef  scalar_t__ u32 ;
struct ieee80211_vif {int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int cmd; scalar_t__ len; } ;
struct TYPE_5__ {int gpio; } ;
struct carl9170_rsp {TYPE_4__ hdr; TYPE_1__ gpio; } ;
struct TYPE_6__ {int pbc_state; int /*<<< orphan*/  pbc; } ;
struct ar9170 {TYPE_3__* hw; int /*<<< orphan*/  fw_boot_wait; TYPE_2__ wps; } ;
struct TYPE_7__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_GPIO_PORT_WPS_BUTTON_PRESSED ; 
 int CARL9170_CMD_ASYNC_FLAG ; 
 int /*<<< orphan*/  CARL9170_RR_WATCHDOG ; 
#define  CARL9170_RSP_ATIM 141 
#define  CARL9170_RSP_BEACON_CONFIG 140 
#define  CARL9170_RSP_BOOT 139 
 int CARL9170_RSP_FLAG ; 
#define  CARL9170_RSP_GPIO 138 
#define  CARL9170_RSP_HEXDUMP 137 
#define  CARL9170_RSP_PRETBTT 136 
#define  CARL9170_RSP_RADAR 135 
#define  CARL9170_RSP_TEXT 134 
#define  CARL9170_RSP_TXCOMP 133 
#define  CARL9170_RSP_WATCHDOG 132 
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  KEY_WPS_BUTTON ; 
#define  NL80211_IFTYPE_ADHOC 131 
#define  NL80211_IFTYPE_AP 130 
#define  NL80211_IFTYPE_MESH_POINT 129 
#define  NL80211_IFTYPE_STATION 128 
 int /*<<< orphan*/  carl9170_cmd_callback (struct ar9170*,scalar_t__,void*) ; 
 int /*<<< orphan*/  carl9170_dbg_message (struct ar9170*,char*,scalar_t__) ; 
 struct ieee80211_vif* carl9170_get_main_vif (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_handle_ps (struct ar9170*,struct carl9170_rsp*) ; 
 int /*<<< orphan*/  carl9170_restart (struct ar9170*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carl9170_tx_process_status (struct ar9170*,struct carl9170_rsp*) ; 
 int /*<<< orphan*/  carl9170_update_beacon (struct ar9170*,int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  print_hex_dump_bytes (char*,int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wiphy_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  wiphy_info (int /*<<< orphan*/ ,char*) ; 

void carl9170_handle_command_response(struct ar9170 *ar, void *buf, u32 len)
{
	struct carl9170_rsp *cmd = buf;
	struct ieee80211_vif *vif;

	if ((cmd->hdr.cmd & CARL9170_RSP_FLAG) != CARL9170_RSP_FLAG) {
		if (!(cmd->hdr.cmd & CARL9170_CMD_ASYNC_FLAG))
			carl9170_cmd_callback(ar, len, buf);

		return;
	}

	if (unlikely(cmd->hdr.len != (len - 4))) {
		if (net_ratelimit()) {
			wiphy_err(ar->hw->wiphy, "FW: received over-/under"
				"sized event %x (%d, but should be %d).\n",
			       cmd->hdr.cmd, cmd->hdr.len, len - 4);

			print_hex_dump_bytes("dump:", DUMP_PREFIX_NONE,
					     buf, len);
		}

		return;
	}

	/* hardware event handlers */
	switch (cmd->hdr.cmd) {
	case CARL9170_RSP_PRETBTT:
		/* pre-TBTT event */
		rcu_read_lock();
		vif = carl9170_get_main_vif(ar);

		if (!vif) {
			rcu_read_unlock();
			break;
		}

		switch (vif->type) {
		case NL80211_IFTYPE_STATION:
			carl9170_handle_ps(ar, cmd);
			break;

		case NL80211_IFTYPE_AP:
		case NL80211_IFTYPE_ADHOC:
		case NL80211_IFTYPE_MESH_POINT:
			carl9170_update_beacon(ar, true);
			break;

		default:
			break;
		}
		rcu_read_unlock();

		break;


	case CARL9170_RSP_TXCOMP:
		/* TX status notification */
		carl9170_tx_process_status(ar, cmd);
		break;

	case CARL9170_RSP_BEACON_CONFIG:
		/*
		 * (IBSS) beacon send notification
		 * bytes: 04 c2 XX YY B4 B3 B2 B1
		 *
		 * XX always 80
		 * YY always 00
		 * B1-B4 "should" be the number of send out beacons.
		 */
		break;

	case CARL9170_RSP_ATIM:
		/* End of Atim Window */
		break;

	case CARL9170_RSP_WATCHDOG:
		/* Watchdog Interrupt */
		carl9170_restart(ar, CARL9170_RR_WATCHDOG);
		break;

	case CARL9170_RSP_TEXT:
		/* firmware debug */
		carl9170_dbg_message(ar, (char *)buf + 4, len - 4);
		break;

	case CARL9170_RSP_HEXDUMP:
		wiphy_dbg(ar->hw->wiphy, "FW: HD %d\n", len - 4);
		print_hex_dump_bytes("FW:", DUMP_PREFIX_NONE,
				     (char *)buf + 4, len - 4);
		break;

	case CARL9170_RSP_RADAR:
		if (!net_ratelimit())
			break;

		wiphy_info(ar->hw->wiphy, "FW: RADAR! Please report this "
		       "incident to linux-wireless@vger.kernel.org !\n");
		break;

	case CARL9170_RSP_GPIO:
#ifdef CONFIG_CARL9170_WPC
		if (ar->wps.pbc) {
			bool state = !!(cmd->gpio.gpio & cpu_to_le32(
				AR9170_GPIO_PORT_WPS_BUTTON_PRESSED));

			if (state != ar->wps.pbc_state) {
				ar->wps.pbc_state = state;
				input_report_key(ar->wps.pbc, KEY_WPS_BUTTON,
						 state);
				input_sync(ar->wps.pbc);
			}
		}
#endif /* CONFIG_CARL9170_WPC */
		break;

	case CARL9170_RSP_BOOT:
		complete(&ar->fw_boot_wait);
		break;

	default:
		wiphy_err(ar->hw->wiphy, "FW: received unhandled event %x\n",
			cmd->hdr.cmd);
		print_hex_dump_bytes("dump:", DUMP_PREFIX_NONE, buf, len);
		break;
	}
}