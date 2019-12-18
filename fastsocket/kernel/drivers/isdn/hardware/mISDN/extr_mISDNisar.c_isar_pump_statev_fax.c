#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_5__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  expires; } ;
struct isar_ch {void* state; int cmd; int mod; int newcmd; int newmod; int try_mod; TYPE_2__* is; TYPE_1__ bch; TYPE_3__ ftimer; int /*<<< orphan*/  dpath; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  Flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_ORIG ; 
 int /*<<< orphan*/  FLG_FTI_RUN ; 
 int /*<<< orphan*/  FLG_LL_CONN ; 
 int /*<<< orphan*/  FLG_LL_OK ; 
 int /*<<< orphan*/  HW_MOD_CONNECT ; 
 int /*<<< orphan*/  HW_MOD_FCERROR ; 
 int /*<<< orphan*/  HW_MOD_FRH ; 
 int /*<<< orphan*/  HW_MOD_FTH ; 
 int /*<<< orphan*/  HW_MOD_NOCARR ; 
 int /*<<< orphan*/  HW_MOD_OK ; 
 int /*<<< orphan*/  HW_MOD_READY ; 
 int HZ ; 
 int ISAR_HIS_PSTREQ ; 
 int ISAR_HIS_PUMPCTRL ; 
 int /*<<< orphan*/  ISAR_RATE_REQ ; 
 int PCTRL_CMD_CONT ; 
 int PCTRL_CMD_ESC ; 
#define  PCTRL_CMD_FRH 143 
#define  PCTRL_CMD_FRM 142 
#define  PCTRL_CMD_FTH 141 
#define  PCTRL_CMD_FTM 140 
 int PCTRL_CMD_SILON ; 
#define  PSEV_10MS_TIMER 139 
#define  PSEV_FLAGS_DET 138 
#define  PSEV_LINE_RX_B 137 
#define  PSEV_LINE_RX_H 136 
#define  PSEV_LINE_TX_B 135 
#define  PSEV_LINE_TX_H 134 
#define  PSEV_RSP_CONN 133 
#define  PSEV_RSP_DISC 132 
#define  PSEV_RSP_FCERR 131 
#define  PSEV_RSP_READY 130 
#define  PSEV_RSP_SILDET 129 
#define  PSEV_RSP_SILOFF 128 
 int SET_DPS (int /*<<< orphan*/ ) ; 
 void* STFAX_ACTIV ; 
 void* STFAX_CONT ; 
 void* STFAX_ESCAPE ; 
 void* STFAX_LINE ; 
 void* STFAX_READY ; 
 void* STFAX_SILDET ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  bch ; 
 int /*<<< orphan*/  del_timer (TYPE_3__*) ; 
 int /*<<< orphan*/  deliver_status (struct isar_ch*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isar_pump_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  send_mbox (TYPE_2__*,int,int,int,int*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isar_pump_statev_fax(struct isar_ch *ch, u8 devt) {
	u8 dps = SET_DPS(ch->dpath);
	u8 p1;

	switch (devt) {
	case PSEV_10MS_TIMER:
		pr_debug("%s: pump stev TIMER\n", ch->is->name);
		break;
	case PSEV_RSP_READY:
		pr_debug("%s: pump stev RSP_READY\n", ch->is->name);
		ch->state = STFAX_READY;
		deliver_status(ch, HW_MOD_READY);
#ifdef AUTOCON
		if (test_bit(BC_FLG_ORIG, &ch->bch.Flags))
			isar_pump_cmd(bch, HW_MOD_FRH, 3);
		else
			isar_pump_cmd(bch, HW_MOD_FTH, 3);
#endif
		break;
	case PSEV_LINE_TX_H:
		if (ch->state == STFAX_LINE) {
			pr_debug("%s: pump stev LINE_TX_H\n", ch->is->name);
			ch->state = STFAX_CONT;
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
				PCTRL_CMD_CONT, 0, NULL);
		} else {
			pr_debug("%s: pump stev LINE_TX_H wrong st %x\n",
				ch->is->name, ch->state);
		}
		break;
	case PSEV_LINE_RX_H:
		if (ch->state == STFAX_LINE) {
			pr_debug("%s: pump stev LINE_RX_H\n", ch->is->name);
			ch->state = STFAX_CONT;
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
				PCTRL_CMD_CONT, 0, NULL);
		} else {
			pr_debug("%s: pump stev LINE_RX_H wrong st %x\n",
				ch->is->name, ch->state);
		}
		break;
	case PSEV_LINE_TX_B:
		if (ch->state == STFAX_LINE) {
			pr_debug("%s: pump stev LINE_TX_B\n", ch->is->name);
			ch->state = STFAX_CONT;
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
				PCTRL_CMD_CONT, 0, NULL);
		} else {
			pr_debug("%s: pump stev LINE_TX_B wrong st %x\n",
				ch->is->name, ch->state);
		}
		break;
	case PSEV_LINE_RX_B:
		if (ch->state == STFAX_LINE) {
			pr_debug("%s: pump stev LINE_RX_B\n", ch->is->name);
			ch->state = STFAX_CONT;
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
				PCTRL_CMD_CONT, 0, NULL);
		} else {
			pr_debug("%s: pump stev LINE_RX_B wrong st %x\n",
				ch->is->name, ch->state);
		}
		break;
	case PSEV_RSP_CONN:
		if (ch->state == STFAX_CONT) {
			pr_debug("%s: pump stev RSP_CONN\n", ch->is->name);
			ch->state = STFAX_ACTIV;
			test_and_set_bit(ISAR_RATE_REQ, &ch->is->Flags);
			send_mbox(ch->is, dps | ISAR_HIS_PSTREQ, 0, 0, NULL);
			if (ch->cmd == PCTRL_CMD_FTH) {
				int delay = (ch->mod == 3) ? 1000 : 200;
				/* 1s (200 ms) Flags before data */
				if (test_and_set_bit(FLG_FTI_RUN,
				    &ch->bch.Flags))
					del_timer(&ch->ftimer);
				ch->ftimer.expires =
					jiffies + ((delay * HZ)/1000);
				test_and_set_bit(FLG_LL_CONN,
					&ch->bch.Flags);
				add_timer(&ch->ftimer);
			} else {
				deliver_status(ch, HW_MOD_CONNECT);
			}
		} else {
			pr_debug("%s: pump stev RSP_CONN wrong st %x\n",
				ch->is->name, ch->state);
		}
		break;
	case PSEV_FLAGS_DET:
		pr_debug("%s: pump stev FLAGS_DET\n", ch->is->name);
		break;
	case PSEV_RSP_DISC:
		pr_debug("%s: pump stev RSP_DISC state(%d)\n",
			ch->is->name, ch->state);
		if (ch->state == STFAX_ESCAPE) {
			p1 = 5;
			switch (ch->newcmd) {
			case 0:
				ch->state = STFAX_READY;
				break;
			case PCTRL_CMD_FTM:
				p1 = 2;
			case PCTRL_CMD_FTH:
				send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
					PCTRL_CMD_SILON, 1, &p1);
				ch->state = STFAX_SILDET;
				break;
			case PCTRL_CMD_FRH:
			case PCTRL_CMD_FRM:
				ch->mod = ch->newmod;
				p1 = ch->newmod;
				ch->newmod = 0;
				ch->cmd = ch->newcmd;
				ch->newcmd = 0;
				send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
					ch->cmd, 1, &p1);
				ch->state = STFAX_LINE;
				ch->try_mod = 3;
				break;
			default:
				pr_debug("%s: RSP_DISC unknown newcmd %x\n",
					ch->is->name, ch->newcmd);
				break;
			}
		} else if (ch->state == STFAX_ACTIV) {
			if (test_and_clear_bit(FLG_LL_OK, &ch->bch.Flags))
				deliver_status(ch, HW_MOD_OK);
			else if (ch->cmd == PCTRL_CMD_FRM)
				deliver_status(ch, HW_MOD_NOCARR);
			else
				deliver_status(ch, HW_MOD_FCERROR);
			ch->state = STFAX_READY;
		} else if (ch->state != STFAX_SILDET) {
			/* ignore in STFAX_SILDET */
			ch->state = STFAX_READY;
			deliver_status(ch, HW_MOD_FCERROR);
		}
		break;
	case PSEV_RSP_SILDET:
		pr_debug("%s: pump stev RSP_SILDET\n", ch->is->name);
		if (ch->state == STFAX_SILDET) {
			ch->mod = ch->newmod;
			p1 = ch->newmod;
			ch->newmod = 0;
			ch->cmd = ch->newcmd;
			ch->newcmd = 0;
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
				ch->cmd, 1, &p1);
			ch->state = STFAX_LINE;
			ch->try_mod = 3;
		}
		break;
	case PSEV_RSP_SILOFF:
		pr_debug("%s: pump stev RSP_SILOFF\n", ch->is->name);
		break;
	case PSEV_RSP_FCERR:
		if (ch->state == STFAX_LINE) {
			pr_debug("%s: pump stev RSP_FCERR try %d\n",
				ch->is->name, ch->try_mod);
			if (ch->try_mod--) {
				send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL,
					ch->cmd, 1, &ch->mod);
				break;
			}
		}
		pr_debug("%s: pump stev RSP_FCERR\n", ch->is->name);
		ch->state = STFAX_ESCAPE;
		send_mbox(ch->is, dps | ISAR_HIS_PUMPCTRL, PCTRL_CMD_ESC,
			0, NULL);
		deliver_status(ch, HW_MOD_FCERROR);
		break;
	default:
		break;
	}
}