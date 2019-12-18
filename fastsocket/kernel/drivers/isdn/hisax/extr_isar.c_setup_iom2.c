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
struct TYPE_3__ {int /*<<< orphan*/  dpath; } ;
struct TYPE_4__ {TYPE_1__ isar; } ;
struct BCState {int mode; TYPE_2__ hw; scalar_t__ channel; struct IsdnCardState* cs; } ;

/* Variables and functions */
 int IOM_CTRL_ALAW ; 
 int IOM_CTRL_ENA ; 
 int IOM_CTRL_RCV ; 
 int IOM_P1_TXD ; 
 int ISAR_HIS_IOM2CFG ; 
 int ISAR_HIS_IOM2REQ ; 
#define  L1_MODE_FAX 132 
#define  L1_MODE_HDLC 131 
#define  L1_MODE_NULL 130 
#define  L1_MODE_TRANS 129 
#define  L1_MODE_V32 128 
 int SET_DPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sendmsg (struct IsdnCardState*,int,int,int,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void
setup_iom2(struct BCState *bcs) {
	struct IsdnCardState *cs = bcs->cs;
	u_char dps = SET_DPS(bcs->hw.isar.dpath);
	u_char cmsb = IOM_CTRL_ENA, msg[5] = {IOM_P1_TXD,0,0,0,0};
	
	if (bcs->channel)
		msg[1] = msg[3] = 1;
	switch (bcs->mode) {
		case L1_MODE_NULL:
			cmsb = 0;
			/* dummy slot */
			msg[1] = msg[3] = bcs->hw.isar.dpath + 2;
			break;
		case L1_MODE_TRANS:
		case L1_MODE_HDLC:
			break;
		case L1_MODE_V32:
		case L1_MODE_FAX:
			cmsb |= IOM_CTRL_ALAW | IOM_CTRL_RCV;
			break;
	}
	sendmsg(cs, dps | ISAR_HIS_IOM2CFG, cmsb, 5, msg);
	udelay(1000);
	sendmsg(cs, dps | ISAR_HIS_IOM2REQ, 0, 0, NULL);
	udelay(1000);
}