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
struct TYPE_2__ {int nr; int state; int /*<<< orphan*/  Flags; } ;
struct isar_ch {int /*<<< orphan*/  is; TYPE_1__ bch; int /*<<< orphan*/  dpath; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_DTMFSEND ; 
 int IOM_CTRL_ALAW ; 
 int IOM_CTRL_ENA ; 
 int IOM_CTRL_RCV ; 
 int IOM_P1_TXD ; 
 int ISAR_HIS_IOM2CFG ; 
 int ISAR_HIS_IOM2REQ ; 
#define  ISDN_P_B_HDLC 133 
#define  ISDN_P_B_L2DTMF 132 
#define  ISDN_P_B_MODEM_ASYNC 131 
#define  ISDN_P_B_RAW 130 
#define  ISDN_P_B_T30_FAX 129 
#define  ISDN_P_NONE 128 
 int SET_DPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_mbox (int /*<<< orphan*/ ,int,int,int,int*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
setup_iom2(struct isar_ch *ch) {
	u8 dps = SET_DPS(ch->dpath);
	u8 cmsb = IOM_CTRL_ENA, msg[5] = {IOM_P1_TXD, 0, 0, 0, 0};

	if (ch->bch.nr == 2) {
		msg[1] = 1;
		msg[3] = 1;
	}
	switch (ch->bch.state) {
	case ISDN_P_NONE:
		cmsb = 0;
		/* dummy slot */
		msg[1] = ch->dpath + 2;
		msg[3] = ch->dpath + 2;
		break;
	case ISDN_P_B_RAW:
	case ISDN_P_B_HDLC:
		break;
	case ISDN_P_B_MODEM_ASYNC:
	case ISDN_P_B_T30_FAX:
		cmsb |= IOM_CTRL_RCV;
	case ISDN_P_B_L2DTMF:
		if (test_bit(FLG_DTMFSEND, &ch->bch.Flags))
			cmsb |= IOM_CTRL_RCV;
		cmsb |= IOM_CTRL_ALAW;
		break;
	}
	send_mbox(ch->is, dps | ISAR_HIS_IOM2CFG, cmsb, 5, msg);
	udelay(1000);
	send_mbox(ch->is, dps | ISAR_HIS_IOM2REQ, 0, 0, NULL);
	udelay(1000);
}