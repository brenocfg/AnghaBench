#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int state; int /*<<< orphan*/  Flags; } ;
struct isar_ch {int /*<<< orphan*/  is; TYPE_1__ bch; int /*<<< orphan*/  newmod; int /*<<< orphan*/  newcmd; int /*<<< orphan*/  state; int /*<<< orphan*/  dpath; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_DTMFSEND ; 
 int /*<<< orphan*/  FLG_FTI_RUN ; 
 int /*<<< orphan*/  FLG_ORIGIN ; 
 int ISAR_HIS_PSTREQ ; 
 int ISAR_HIS_PUMPCFG ; 
#define  ISDN_P_B_HDLC 133 
#define  ISDN_P_B_L2DTMF 132 
#define  ISDN_P_B_MODEM_ASYNC 131 
#define  ISDN_P_B_RAW 130 
#define  ISDN_P_B_T30_FAX 129 
#define  ISDN_P_NONE 128 
 int PCTRL_ORIG ; 
 int PFAXP2_ATN ; 
 int PFAXP2_CTN ; 
 int PMOD_BYPASS ; 
 int PMOD_DATAMODEM ; 
 int PMOD_DTMF ; 
 int PMOD_DTMF_TRANS ; 
 int PMOD_FAX ; 
 int PV32P2_BEL ; 
 int PV32P2_V21 ; 
 int PV32P2_V22A ; 
 int PV32P2_V22B ; 
 int PV32P2_V22C ; 
 int PV32P2_V23R ; 
 int PV32P3_AMOD ; 
 int PV32P3_V23B ; 
 int PV32P3_V32B ; 
 int PV32P4_UT144 ; 
 int PV32P5_UT144 ; 
 int PV32P6_ATN ; 
 int PV32P6_CTN ; 
 int SET_DPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STFAX_NULL ; 
 int /*<<< orphan*/  send_mbox (int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
setup_pump(struct isar_ch *ch) {
	u8 dps = SET_DPS(ch->dpath);
	u8 ctrl, param[6];

	switch (ch->bch.state) {
	case ISDN_P_NONE:
	case ISDN_P_B_RAW:
	case ISDN_P_B_HDLC:
		send_mbox(ch->is, dps | ISAR_HIS_PUMPCFG, PMOD_BYPASS, 0, NULL);
		break;
	case ISDN_P_B_L2DTMF:
		if (test_bit(FLG_DTMFSEND, &ch->bch.Flags)) {
			param[0] = 5; /* TOA 5 db */
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCFG,
				PMOD_DTMF_TRANS, 1, param);
		} else {
			param[0] = 40; /* REL -46 dbm */
			send_mbox(ch->is, dps | ISAR_HIS_PUMPCFG,
				PMOD_DTMF, 1, param);
		}
	case ISDN_P_B_MODEM_ASYNC:
		ctrl = PMOD_DATAMODEM;
		if (test_bit(FLG_ORIGIN, &ch->bch.Flags)) {
			ctrl |= PCTRL_ORIG;
			param[5] = PV32P6_CTN;
		} else {
			param[5] = PV32P6_ATN;
		}
		param[0] = 6; /* 6 db */
		param[1] = PV32P2_V23R | PV32P2_V22A | PV32P2_V22B |
			PV32P2_V22C | PV32P2_V21 | PV32P2_BEL;
		param[2] = PV32P3_AMOD | PV32P3_V32B | PV32P3_V23B;
		param[3] = PV32P4_UT144;
		param[4] = PV32P5_UT144;
		send_mbox(ch->is, dps | ISAR_HIS_PUMPCFG, ctrl, 6, param);
		break;
	case ISDN_P_B_T30_FAX:
		ctrl = PMOD_FAX;
		if (test_bit(FLG_ORIGIN, &ch->bch.Flags)) {
			ctrl |= PCTRL_ORIG;
			param[1] = PFAXP2_CTN;
		} else {
			param[1] = PFAXP2_ATN;
		}
		param[0] = 6; /* 6 db */
		send_mbox(ch->is, dps | ISAR_HIS_PUMPCFG, ctrl, 2, param);
		ch->state = STFAX_NULL;
		ch->newcmd = 0;
		ch->newmod = 0;
		test_and_set_bit(FLG_FTI_RUN, &ch->bch.Flags);
		break;
	}
	udelay(1000);
	send_mbox(ch->is, dps | ISAR_HIS_PSTREQ, 0, 0, NULL);
	udelay(1000);
}