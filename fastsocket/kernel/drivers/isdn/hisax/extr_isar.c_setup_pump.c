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
struct TYPE_3__ {int /*<<< orphan*/  newmod; int /*<<< orphan*/  newcmd; int /*<<< orphan*/  state; int /*<<< orphan*/  dpath; } ;
struct TYPE_4__ {TYPE_1__ isar; } ;
struct BCState {int mode; int /*<<< orphan*/  Flag; TYPE_2__ hw; struct IsdnCardState* cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_FTI_RUN ; 
 int /*<<< orphan*/  BC_FLG_ORIG ; 
 int ISAR_HIS_PSTREQ ; 
 int ISAR_HIS_PUMPCFG ; 
#define  L1_MODE_FAX 132 
#define  L1_MODE_HDLC 131 
#define  L1_MODE_NULL 130 
#define  L1_MODE_TRANS 129 
#define  L1_MODE_V32 128 
 int PCTRL_ORIG ; 
 int PFAXP2_ATN ; 
 int PFAXP2_CTN ; 
 int PMOD_BYPASS ; 
 int PMOD_DATAMODEM ; 
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
 int para_TOA ; 
 int /*<<< orphan*/  sendmsg (struct IsdnCardState*,int,int,int,int*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
setup_pump(struct BCState *bcs) {
	struct IsdnCardState *cs = bcs->cs;
	u_char dps = SET_DPS(bcs->hw.isar.dpath);
	u_char ctrl, param[6];

	switch (bcs->mode) {
		case L1_MODE_NULL:
		case L1_MODE_TRANS:
		case L1_MODE_HDLC:
			sendmsg(cs, dps | ISAR_HIS_PUMPCFG, PMOD_BYPASS, 0, NULL);
			break;
		case L1_MODE_V32:
			ctrl = PMOD_DATAMODEM;
			if (test_bit(BC_FLG_ORIG, &bcs->Flag)) {
				ctrl |= PCTRL_ORIG;
				param[5] = PV32P6_CTN;
			} else {
				param[5] = PV32P6_ATN;
			}
			param[0] = para_TOA; /* 6 db */
			param[1] = PV32P2_V23R | PV32P2_V22A | PV32P2_V22B |
				   PV32P2_V22C | PV32P2_V21 | PV32P2_BEL; 
			param[2] = PV32P3_AMOD | PV32P3_V32B | PV32P3_V23B;
			param[3] = PV32P4_UT144;
			param[4] = PV32P5_UT144;
			sendmsg(cs, dps | ISAR_HIS_PUMPCFG, ctrl, 6, param);
			break;
		case L1_MODE_FAX:
			ctrl = PMOD_FAX;
			if (test_bit(BC_FLG_ORIG, &bcs->Flag)) {
				ctrl |= PCTRL_ORIG;
				param[1] = PFAXP2_CTN;
			} else {
				param[1] = PFAXP2_ATN;
			}
			param[0] = para_TOA; /* 6 db */
			sendmsg(cs, dps | ISAR_HIS_PUMPCFG, ctrl, 2, param);
			bcs->hw.isar.state = STFAX_NULL;
			bcs->hw.isar.newcmd = 0;
			bcs->hw.isar.newmod = 0;
			test_and_set_bit(BC_FLG_FTI_RUN, &bcs->Flag);
			break;
	}
	udelay(1000);
	sendmsg(cs, dps | ISAR_HIS_PSTREQ, 0, 0, NULL);
	udelay(1000);
}