#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_20__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_19__ ;
typedef  struct TYPE_29__   TYPE_18__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct carl9170_tally_rsp {int dummy; } ;
struct TYPE_24__ {int len; int cmd; int /*<<< orphan*/  seq; int /*<<< orphan*/  ext; } ;
struct TYPE_29__ {int /*<<< orphan*/  tick; } ;
struct TYPE_40__ {scalar_t__ tsf; } ;
struct TYPE_38__ {TYPE_18__* vals; } ;
struct TYPE_34__ {int /*<<< orphan*/ * vals; } ;
struct carl9170_rsp {TYPE_13__ hdr; TYPE_18__ tally; TYPE_9__ tsf; TYPE_7__ echo; TYPE_3__ rreg_res; } ;
struct TYPE_28__ {int len; int cmd; int /*<<< orphan*/  seq; int /*<<< orphan*/  ext; } ;
struct TYPE_27__ {int /*<<< orphan*/  state; } ;
struct TYPE_23__ {int mode; size_t vif_id; int /*<<< orphan*/  bcn_len; int /*<<< orphan*/  bcn_addr; } ;
struct TYPE_21__ {int /*<<< orphan*/  rx_filter; } ;
struct TYPE_39__ {int /*<<< orphan*/ * vals; } ;
struct TYPE_37__ {TYPE_5__* regs; } ;
struct TYPE_35__ {int /*<<< orphan*/ * regs; } ;
struct carl9170_cmd {TYPE_17__ hdr; TYPE_16__ psm; int /*<<< orphan*/  disablekey; int /*<<< orphan*/  setkey; TYPE_12__ bcn_ctrl; int /*<<< orphan*/  wol; TYPE_10__ rx_filter; TYPE_8__ echo; TYPE_6__ wreg; TYPE_4__ rreg; } ;
struct TYPE_36__ {int /*<<< orphan*/  val; int /*<<< orphan*/  addr; } ;
struct TYPE_31__ {struct carl9170_cmd cmd; } ;
struct TYPE_33__ {TYPE_1__ cmd; } ;
struct TYPE_32__ {TYPE_2__ reserved; } ;
struct TYPE_25__ {int /*<<< orphan*/  state; } ;
struct TYPE_26__ {TYPE_14__ psm; } ;
struct TYPE_22__ {int /*<<< orphan*/ * cab_flush_trigger; int /*<<< orphan*/  rx_filter; int /*<<< orphan*/  mac_reset; } ;
struct TYPE_30__ {int reboot; TYPE_15__ phy; TYPE_11__ wlan; int /*<<< orphan*/  tally; int /*<<< orphan*/  ticks_per_usec; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_BCN_CTRL_READY ; 
 int /*<<< orphan*/  AR9170_MAC_REG_BCN_ADDR ; 
 int /*<<< orphan*/  AR9170_MAC_REG_BCN_CTRL ; 
 int /*<<< orphan*/  AR9170_MAC_REG_BCN_LENGTH ; 
 int /*<<< orphan*/  BUG (char*,int) ; 
 int CARL9170_BCN_CTRL_CAB_TRIGGER ; 
 int /*<<< orphan*/  CARL9170_CAB_TRIGGER_EMPTY ; 
 int CARL9170_CMD_ASYNC_FLAG ; 
#define  CARL9170_CMD_BCN_CTRL 143 
#define  CARL9170_CMD_DKEY 142 
#define  CARL9170_CMD_ECHO 141 
#define  CARL9170_CMD_EKEY 140 
#define  CARL9170_CMD_FREQUENCY 139 
#define  CARL9170_CMD_FREQ_START 138 
#define  CARL9170_CMD_PSM 137 
#define  CARL9170_CMD_READ_TSF 136 
#define  CARL9170_CMD_REBOOT 135 
#define  CARL9170_CMD_RF_INIT 134 
#define  CARL9170_CMD_RREG 133 
#define  CARL9170_CMD_RX_FILTER 132 
#define  CARL9170_CMD_SWRST 131 
#define  CARL9170_CMD_TALLY 130 
#define  CARL9170_CMD_WOL 129 
#define  CARL9170_CMD_WREG 128 
 int /*<<< orphan*/  CARL9170_MAC_RESET_FORCE ; 
 int /*<<< orphan*/  disable_key (int /*<<< orphan*/ *) ; 
 TYPE_20__ dma_mem ; 
 TYPE_19__ fw ; 
 int /*<<< orphan*/  get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_18__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_tsf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rf_cmd (struct carl9170_cmd*,struct carl9170_rsp*) ; 
 int /*<<< orphan*/  rf_notify_set_channel () ; 
 int /*<<< orphan*/  rf_psm () ; 
 int /*<<< orphan*/  set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlan_cab_flush_queue (size_t) ; 
 int /*<<< orphan*/  wlan_modify_beacon (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wol_cmd (int /*<<< orphan*/ *) ; 

void handle_cmd(struct carl9170_rsp *resp)
{
	struct carl9170_cmd *cmd = &dma_mem.reserved.cmd.cmd;
	unsigned int i;

	/* copies cmd, len and extra fields */
	resp->hdr.len = cmd->hdr.len;
	resp->hdr.cmd = cmd->hdr.cmd;
	resp->hdr.ext = cmd->hdr.ext;
	resp->hdr.seq |= cmd->hdr.seq;

	switch (cmd->hdr.cmd & ~CARL9170_CMD_ASYNC_FLAG) {
	case CARL9170_CMD_RREG:
		for (i = 0; i < (cmd->hdr.len / 4); i++)
			resp->rreg_res.vals[i] = get(cmd->rreg.regs[i]);
		break;

	case CARL9170_CMD_WREG:
		resp->hdr.len = 0;
		for (i = 0; i < (cmd->hdr.len / 8); i++)
			set(cmd->wreg.regs[i].addr, cmd->wreg.regs[i].val);
		break;

	case CARL9170_CMD_ECHO:
		memcpy(resp->echo.vals, cmd->echo.vals, cmd->hdr.len);
		break;

	case CARL9170_CMD_SWRST:
#ifdef CONFIG_CARL9170FW_FW_MAC_RESET
		/*
		 * Command has no payload, so the response
		 * has no payload either.
		 * resp->hdr.len = 0;
		 */
		fw.wlan.mac_reset = CARL9170_MAC_RESET_FORCE;
#endif /* CONFIG_CARL9170FW_FW_MAC_RESET */
		break;

	case CARL9170_CMD_REBOOT:
		/*
		 * resp->len = 0;
		 */
		fw.reboot = 1;
		break;

	case CARL9170_CMD_READ_TSF:
		resp->hdr.len = 8;
		read_tsf((uint32_t *)resp->tsf.tsf);
		break;

	case CARL9170_CMD_RX_FILTER:
		resp->hdr.len = 0;
		fw.wlan.rx_filter = cmd->rx_filter.rx_filter;
		break;

	case CARL9170_CMD_WOL:
		wol_cmd(&cmd->wol);
		break;

	case CARL9170_CMD_TALLY:
		resp->hdr.len = sizeof(struct carl9170_tally_rsp);
		memcpy(&resp->tally, &fw.tally, sizeof(struct carl9170_tally_rsp));
		resp->tally.tick = fw.ticks_per_usec;
		memset(&fw.tally, 0, sizeof(struct carl9170_tally_rsp));
		break;

#ifdef CONFIG_CARL9170FW_CAB_QUEUE
	case CARL9170_CMD_BCN_CTRL:
		resp->hdr.len = 0;

		if (cmd->bcn_ctrl.mode & CARL9170_BCN_CTRL_CAB_TRIGGER) {
			wlan_modify_beacon(cmd->bcn_ctrl.vif_id,
				cmd->bcn_ctrl.bcn_addr, cmd->bcn_ctrl.bcn_len);
			set(AR9170_MAC_REG_BCN_ADDR, cmd->bcn_ctrl.bcn_addr);
			set(AR9170_MAC_REG_BCN_LENGTH, cmd->bcn_ctrl.bcn_len);
			set(AR9170_MAC_REG_BCN_CTRL, AR9170_BCN_CTRL_READY);
		} else {
			wlan_cab_flush_queue(cmd->bcn_ctrl.vif_id);
			fw.wlan.cab_flush_trigger[cmd->bcn_ctrl.vif_id] = CARL9170_CAB_TRIGGER_EMPTY;
		}
		break;
#endif /* CONFIG_CARL9170FW_CAB_QUEUE */

#ifdef CONFIG_CARL9170FW_SECURITY_ENGINE
	case CARL9170_CMD_EKEY:
		resp->hdr.len = 0;
		set_key(&cmd->setkey);
		break;

	case CARL9170_CMD_DKEY:
		resp->hdr.len = 0;
		disable_key(&cmd->disablekey);
		break;
#endif /* CONFIG_CARL9170FW_SECURITY_ENGINE */

#ifdef CONFIG_CARL9170FW_RADIO_FUNCTIONS
	case CARL9170_CMD_FREQUENCY:
	case CARL9170_CMD_RF_INIT:
		rf_cmd(cmd, resp);
		break;

	case CARL9170_CMD_FREQ_START:
		/*
		 * resp->hdr.len = 0;
		 */
		rf_notify_set_channel();
		break;

	case CARL9170_CMD_PSM:
		resp->hdr.len = 0;
		fw.phy.psm.state = le32_to_cpu(cmd->psm.state);
		rf_psm();
		break;
#endif /* CONFIG_CARL9170FW_RADIO_FUNCTIONS */

	default:
		BUG("Unknown command %x\n", cmd->hdr.cmd);
		break;
	}
}