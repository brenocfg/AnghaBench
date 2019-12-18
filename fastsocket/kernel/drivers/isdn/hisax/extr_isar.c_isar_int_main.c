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
typedef  int /*<<< orphan*/  u_char ;
struct isar_reg {int iis; int cmsb; int bstat; int /*<<< orphan*/  clsb; scalar_t__ par; } ;
struct IsdnCardState {int debug; int /*<<< orphan*/  (* BC_Write_Reg ) (struct IsdnCardState*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_3__* bcs; } ;
struct BCState {int /*<<< orphan*/  mode; int /*<<< orphan*/  err_rdo; int /*<<< orphan*/  err_tx; } ;
struct TYPE_4__ {struct isar_reg* reg; } ;
struct TYPE_5__ {TYPE_1__ isar; } ;
struct TYPE_6__ {TYPE_2__ hw; } ;

/* Variables and functions */
 int BSTEV_RBO ; 
 int BSTEV_TBO ; 
 int /*<<< orphan*/  ISAR_IIA ; 
#define  ISAR_IIS_BSTEV 136 
#define  ISAR_IIS_BSTRSP 135 
#define  ISAR_IIS_DIAG 134 
#define  ISAR_IIS_GSTEV 133 
#define  ISAR_IIS_INVMSG 132 
#define  ISAR_IIS_IOM2RSP 131 
 int ISAR_IIS_MSCMSD ; 
#define  ISAR_IIS_PSTEV 130 
#define  ISAR_IIS_PSTRSP 129 
#define  ISAR_IIS_RDATA 128 
 int L1_DEB_HSCX ; 
 int L1_DEB_HSCX_FIFO ; 
 int L1_DEB_WARN ; 
 int /*<<< orphan*/  L1_MODE_FAX ; 
 int /*<<< orphan*/  L1_MODE_V32 ; 
 int PSEV_10MS_TIMER ; 
 int /*<<< orphan*/  QuickHex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_send (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/ * debbuf ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,...) ; 
 int /*<<< orphan*/  get_irq_infos (struct IsdnCardState*,struct isar_reg*) ; 
 int /*<<< orphan*/  isar_pump_statev_fax (struct BCState*,int) ; 
 int /*<<< orphan*/  isar_pump_statev_modem (struct BCState*,int) ; 
 int /*<<< orphan*/  isar_pump_status_rsp (struct BCState*,struct isar_reg*) ; 
 int /*<<< orphan*/  isar_rcv_frame (struct IsdnCardState*,struct BCState*) ; 
 int /*<<< orphan*/  rcv_mbox (struct IsdnCardState*,struct isar_reg*,int /*<<< orphan*/ *) ; 
 struct BCState* sel_bcs_isar (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct IsdnCardState*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
isar_int_main(struct IsdnCardState *cs)
{
	struct isar_reg *ireg = cs->bcs[0].hw.isar.reg;
	struct BCState *bcs;

	get_irq_infos(cs, ireg);
	switch (ireg->iis & ISAR_IIS_MSCMSD) {
		case ISAR_IIS_RDATA:
			if ((bcs = sel_bcs_isar(cs, ireg->iis >> 6))) {
				isar_rcv_frame(cs, bcs);
			} else {
				debugl1(cs, "isar spurious IIS_RDATA %x/%x/%x",
					ireg->iis, ireg->cmsb, ireg->clsb);
				cs->BC_Write_Reg(cs, 1, ISAR_IIA, 0);
			}
			break;
		case ISAR_IIS_GSTEV:
			cs->BC_Write_Reg(cs, 1, ISAR_IIA, 0);
			ireg->bstat |= ireg->cmsb;
			check_send(cs, ireg->cmsb);
			break;
		case ISAR_IIS_BSTEV:
#ifdef ERROR_STATISTIC
			if ((bcs = sel_bcs_isar(cs, ireg->iis >> 6))) {
				if (ireg->cmsb == BSTEV_TBO)
					bcs->err_tx++;
				if (ireg->cmsb == BSTEV_RBO)
					bcs->err_rdo++;
			}
#endif
			if (cs->debug & L1_DEB_WARN)
				debugl1(cs, "Buffer STEV dpath%d msb(%x)",
					ireg->iis>>6, ireg->cmsb);
			cs->BC_Write_Reg(cs, 1, ISAR_IIA, 0);
			break;
		case ISAR_IIS_PSTEV:
			if ((bcs = sel_bcs_isar(cs, ireg->iis >> 6))) {
				rcv_mbox(cs, ireg, (u_char *)ireg->par);
				if (bcs->mode == L1_MODE_V32) {
					isar_pump_statev_modem(bcs, ireg->cmsb);
				} else if (bcs->mode == L1_MODE_FAX) {
					isar_pump_statev_fax(bcs, ireg->cmsb);
				} else if (ireg->cmsb == PSEV_10MS_TIMER) {
					if (cs->debug & L1_DEB_HSCX)
						debugl1(cs, "pump stev TIMER");
				} else {
					if (cs->debug & L1_DEB_WARN)
						debugl1(cs, "isar IIS_PSTEV pmode %d stat %x",
							bcs->mode, ireg->cmsb);
				}
			} else {
				debugl1(cs, "isar spurious IIS_PSTEV %x/%x/%x",
					ireg->iis, ireg->cmsb, ireg->clsb);
				cs->BC_Write_Reg(cs, 1, ISAR_IIA, 0);
			}
			break;
		case ISAR_IIS_PSTRSP:
			if ((bcs = sel_bcs_isar(cs, ireg->iis >> 6))) {
				rcv_mbox(cs, ireg, (u_char *)ireg->par);
				isar_pump_status_rsp(bcs, ireg);
			} else {
				debugl1(cs, "isar spurious IIS_PSTRSP %x/%x/%x",
					ireg->iis, ireg->cmsb, ireg->clsb);
				cs->BC_Write_Reg(cs, 1, ISAR_IIA, 0);
			}
			break;
		case ISAR_IIS_DIAG:
		case ISAR_IIS_BSTRSP:
		case ISAR_IIS_IOM2RSP:
			rcv_mbox(cs, ireg, (u_char *)ireg->par);
			if ((cs->debug & (L1_DEB_HSCX | L1_DEB_HSCX_FIFO))
				== L1_DEB_HSCX) {
				u_char *tp=debbuf;

				tp += sprintf(debbuf, "msg iis(%x) msb(%x)",
					ireg->iis, ireg->cmsb);
				QuickHex(tp, (u_char *)ireg->par, ireg->clsb);
				debugl1(cs, debbuf);
			}
			break;
		case ISAR_IIS_INVMSG:
			rcv_mbox(cs, ireg, debbuf);
			if (cs->debug & L1_DEB_WARN)
				debugl1(cs, "invalid msg his:%x",
					ireg->cmsb);
			break;
		default:
			rcv_mbox(cs, ireg, debbuf);
			if (cs->debug & L1_DEB_WARN)
				debugl1(cs, "unhandled msg iis(%x) ctrl(%x/%x)",
					ireg->iis, ireg->cmsb, ireg->clsb);
			break;
	}
}