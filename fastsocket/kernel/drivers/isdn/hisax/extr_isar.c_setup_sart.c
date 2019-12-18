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
typedef  char u_char ;
struct IsdnCardState {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  dpath; } ;
struct TYPE_4__ {TYPE_1__ isar; } ;
struct BCState {int mode; TYPE_2__ hw; struct IsdnCardState* cs; } ;

/* Variables and functions */
 char ISAR_HIS_BSTREQ ; 
 char ISAR_HIS_SARTCFG ; 
#define  L1_MODE_FAX 132 
#define  L1_MODE_HDLC 131 
#define  L1_MODE_NULL 130 
#define  L1_MODE_TRANS 129 
#define  L1_MODE_V32 128 
 char SCTRL_HDMC_BOTH ; 
 char SET_DPS (int /*<<< orphan*/ ) ; 
 char SMODE_BINARY ; 
 char SMODE_DISABLE ; 
 char SMODE_HDLC ; 
 char SMODE_V14 ; 
 char S_P1_CHS_8 ; 
 char S_P2_BFT_DEF ; 
 int /*<<< orphan*/  sendmsg (struct IsdnCardState*,char,char,int,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
setup_sart(struct BCState *bcs) {
	struct IsdnCardState *cs = bcs->cs;
	u_char dps = SET_DPS(bcs->hw.isar.dpath);
	u_char ctrl, param[2];
	
	switch (bcs->mode) {
		case L1_MODE_NULL:
			sendmsg(cs, dps | ISAR_HIS_SARTCFG, SMODE_DISABLE, 0,
				NULL);
			break;
		case L1_MODE_TRANS:
			sendmsg(cs, dps | ISAR_HIS_SARTCFG, SMODE_BINARY, 2,
				"\0\0");
			break;
		case L1_MODE_HDLC:
			param[0] = 0;
			sendmsg(cs, dps | ISAR_HIS_SARTCFG, SMODE_HDLC, 1,
				param);
			break;
		case L1_MODE_V32:
			ctrl = SMODE_V14 | SCTRL_HDMC_BOTH;
			param[0] = S_P1_CHS_8;
			param[1] = S_P2_BFT_DEF;
			sendmsg(cs, dps | ISAR_HIS_SARTCFG, ctrl, 2,
				param);
			break;
		case L1_MODE_FAX:
			/* SART must not configured with FAX */
			break;
	}
	udelay(1000);
	sendmsg(cs, dps | ISAR_HIS_BSTREQ, 0, 0, NULL);
	udelay(1000);
}