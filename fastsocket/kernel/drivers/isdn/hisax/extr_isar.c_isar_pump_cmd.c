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
typedef  int u_char ;
struct IsdnCardState {int dummy; } ;
struct TYPE_4__ {int cmd; int mod; int newmod; int try_mod; void* state; void* newcmd; int /*<<< orphan*/  dpath; } ;
struct TYPE_3__ {TYPE_2__ isar; } ;
struct BCState {TYPE_1__ hw; int /*<<< orphan*/  Flag; struct IsdnCardState* cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_FRH_WAIT ; 
 int ISAR_HIS_PUMPCTRL ; 
#define  ISDN_FAXPUMP_HALT 132 
 int /*<<< orphan*/  ISDN_FAX_CLASS1_CONNECT ; 
#define  ISDN_FAX_CLASS1_FRH 131 
#define  ISDN_FAX_CLASS1_FRM 130 
#define  ISDN_FAX_CLASS1_FTH 129 
#define  ISDN_FAX_CLASS1_FTM 128 
 int PCTRL_CMD_ESC ; 
 void* PCTRL_CMD_FRH ; 
 void* PCTRL_CMD_FRM ; 
 void* PCTRL_CMD_FTH ; 
 void* PCTRL_CMD_FTM ; 
 int PCTRL_CMD_HALT ; 
 int SET_DPS (int /*<<< orphan*/ ) ; 
 void* STFAX_ACTIV ; 
 void* STFAX_ESCAPE ; 
 void* STFAX_LINE ; 
 void* STFAX_NULL ; 
 void* STFAX_READY ; 
 int /*<<< orphan*/  ll_deliver_faxstat (struct BCState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendmsg (struct IsdnCardState*,int,int,int,int*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isar_pump_cmd(struct BCState *bcs, u_char cmd, u_char para) 
{
	struct IsdnCardState *cs = bcs->cs;
	u_char dps = SET_DPS(bcs->hw.isar.dpath);
	u_char ctrl = 0, nom = 0, p1 = 0;

	switch(cmd) {
		case ISDN_FAX_CLASS1_FTM:
			test_and_clear_bit(BC_FLG_FRH_WAIT, &bcs->Flag);
			if (bcs->hw.isar.state == STFAX_READY) {
				p1 = para;
				ctrl = PCTRL_CMD_FTM;
				nom = 1;
				bcs->hw.isar.state = STFAX_LINE;
				bcs->hw.isar.cmd = ctrl;
				bcs->hw.isar.mod = para;
				bcs->hw.isar.newmod = 0;
				bcs->hw.isar.newcmd = 0;
				bcs->hw.isar.try_mod = 3; 
			} else if ((bcs->hw.isar.state == STFAX_ACTIV) &&
				(bcs->hw.isar.cmd == PCTRL_CMD_FTM) &&
				(bcs->hw.isar.mod == para)) {
				ll_deliver_faxstat(bcs, ISDN_FAX_CLASS1_CONNECT);
			} else {
				bcs->hw.isar.newmod = para;
				bcs->hw.isar.newcmd = PCTRL_CMD_FTM;
				nom = 0;
				ctrl = PCTRL_CMD_ESC;
				bcs->hw.isar.state = STFAX_ESCAPE; 
			}
			break;
		case ISDN_FAX_CLASS1_FTH:
			test_and_clear_bit(BC_FLG_FRH_WAIT, &bcs->Flag);
			if (bcs->hw.isar.state == STFAX_READY) {
				p1 = para;
				ctrl = PCTRL_CMD_FTH;
				nom = 1;
				bcs->hw.isar.state = STFAX_LINE;
				bcs->hw.isar.cmd = ctrl;
				bcs->hw.isar.mod = para;
				bcs->hw.isar.newmod = 0;
				bcs->hw.isar.newcmd = 0;
				bcs->hw.isar.try_mod = 3; 
			} else if ((bcs->hw.isar.state == STFAX_ACTIV) &&
				(bcs->hw.isar.cmd == PCTRL_CMD_FTH) &&
				(bcs->hw.isar.mod == para)) {
				ll_deliver_faxstat(bcs, ISDN_FAX_CLASS1_CONNECT);
			} else {
				bcs->hw.isar.newmod = para;
				bcs->hw.isar.newcmd = PCTRL_CMD_FTH;
				nom = 0;
				ctrl = PCTRL_CMD_ESC;
				bcs->hw.isar.state = STFAX_ESCAPE; 
			}
			break;
		case ISDN_FAX_CLASS1_FRM:
			test_and_clear_bit(BC_FLG_FRH_WAIT, &bcs->Flag);
			if (bcs->hw.isar.state == STFAX_READY) {
				p1 = para;
				ctrl = PCTRL_CMD_FRM;
				nom = 1;
				bcs->hw.isar.state = STFAX_LINE;
				bcs->hw.isar.cmd = ctrl;
				bcs->hw.isar.mod = para;
				bcs->hw.isar.newmod = 0;
				bcs->hw.isar.newcmd = 0;
				bcs->hw.isar.try_mod = 3; 
			} else if ((bcs->hw.isar.state == STFAX_ACTIV) &&
				(bcs->hw.isar.cmd == PCTRL_CMD_FRM) &&
				(bcs->hw.isar.mod == para)) {
				ll_deliver_faxstat(bcs, ISDN_FAX_CLASS1_CONNECT);
			} else {
				bcs->hw.isar.newmod = para;
				bcs->hw.isar.newcmd = PCTRL_CMD_FRM;
				nom = 0;
				ctrl = PCTRL_CMD_ESC;
				bcs->hw.isar.state = STFAX_ESCAPE; 
			}
			break;
		case ISDN_FAX_CLASS1_FRH:
			test_and_set_bit(BC_FLG_FRH_WAIT, &bcs->Flag);
			if (bcs->hw.isar.state == STFAX_READY) {
				p1 = para;
				ctrl = PCTRL_CMD_FRH;
				nom = 1;
				bcs->hw.isar.state = STFAX_LINE;
				bcs->hw.isar.cmd = ctrl;
				bcs->hw.isar.mod = para;
				bcs->hw.isar.newmod = 0;
				bcs->hw.isar.newcmd = 0;
				bcs->hw.isar.try_mod = 3; 
			} else if ((bcs->hw.isar.state == STFAX_ACTIV) &&
				(bcs->hw.isar.cmd == PCTRL_CMD_FRH) &&
				(bcs->hw.isar.mod == para)) {
				ll_deliver_faxstat(bcs, ISDN_FAX_CLASS1_CONNECT);
			} else {
				bcs->hw.isar.newmod = para;
				bcs->hw.isar.newcmd = PCTRL_CMD_FRH;
				nom = 0;
				ctrl = PCTRL_CMD_ESC;
				bcs->hw.isar.state = STFAX_ESCAPE; 
			}
			break;
		case ISDN_FAXPUMP_HALT:
			bcs->hw.isar.state = STFAX_NULL;
			nom = 0;
			ctrl = PCTRL_CMD_HALT;
			break;
	}
	if (ctrl)
		sendmsg(cs, dps | ISAR_HIS_PUMPCTRL, ctrl, nom, &p1);
}