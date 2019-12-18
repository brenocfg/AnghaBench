#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct IsdnCardState {int debug; } ;
struct TYPE_5__ {TYPE_1__* reg; int /*<<< orphan*/  dpath; } ;
struct TYPE_6__ {TYPE_2__ isar; } ;
struct BCState {TYPE_3__ hw; int /*<<< orphan*/  st; struct IsdnCardState* cs; } ;
struct TYPE_4__ {int /*<<< orphan*/  Flags; } ;

/* Variables and functions */
 int ISAR_HIS_PSTREQ ; 
 int /*<<< orphan*/  ISAR_RATE_REQ ; 
 int L1_DEB_HSCX ; 
 int PH_ACTIVATE ; 
 int PH_DEACTIVATE ; 
#define  PSEV_10MS_TIMER 140 
#define  PSEV_CON_OFF 139 
#define  PSEV_CON_ON 138 
#define  PSEV_CTS_OFF 137 
#define  PSEV_CTS_ON 136 
#define  PSEV_DCD_OFF 135 
#define  PSEV_DCD_ON 134 
#define  PSEV_DSR_OFF 133 
#define  PSEV_DSR_ON 132 
#define  PSEV_GSTN_CLR 131 
#define  PSEV_REM_REN 130 
#define  PSEV_REM_RET 129 
#define  PSEV_V24_OFF 128 
 int REQUEST ; 
 int SET_DPS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,...) ; 
 int /*<<< orphan*/  l1_msg_b (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sendmsg (struct IsdnCardState*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isar_pump_statev_modem(struct BCState *bcs, u_char devt) {
	struct IsdnCardState *cs = bcs->cs;
	u_char dps = SET_DPS(bcs->hw.isar.dpath);

	switch(devt) {
		case PSEV_10MS_TIMER:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev TIMER");
			break;
		case PSEV_CON_ON:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev CONNECT");
			l1_msg_b(bcs->st, PH_ACTIVATE | REQUEST, NULL);
			break;
		case PSEV_CON_OFF:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev NO CONNECT");
			sendmsg(cs, dps | ISAR_HIS_PSTREQ, 0, 0, NULL);
			l1_msg_b(bcs->st, PH_DEACTIVATE | REQUEST, NULL);
			break;
		case PSEV_V24_OFF:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev V24 OFF");
			break;
		case PSEV_CTS_ON:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev CTS ON");
			break;
		case PSEV_CTS_OFF:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev CTS OFF");
			break;
		case PSEV_DCD_ON:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev CARRIER ON");
			test_and_set_bit(ISAR_RATE_REQ, &bcs->hw.isar.reg->Flags); 
			sendmsg(cs, dps | ISAR_HIS_PSTREQ, 0, 0, NULL);
			break;
		case PSEV_DCD_OFF:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev CARRIER OFF");
			break;
		case PSEV_DSR_ON:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev DSR ON");
			break;
		case PSEV_DSR_OFF:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev DSR_OFF");
			break;
		case PSEV_REM_RET:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev REMOTE RETRAIN");
			break;
		case PSEV_REM_REN:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev REMOTE RENEGOTIATE");
			break;
		case PSEV_GSTN_CLR:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "pump stev GSTN CLEAR", devt);
			break;
		default:
			if (cs->debug & L1_DEB_HSCX)
				debugl1(cs, "unknown pump stev %x", devt);
			break;
	}
}