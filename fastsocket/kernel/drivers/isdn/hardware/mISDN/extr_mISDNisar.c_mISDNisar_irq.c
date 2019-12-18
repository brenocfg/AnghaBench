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
typedef  int /*<<< orphan*/  tt ;
struct isar_hw {int iis; int cmsb; int bstat; int /*<<< orphan*/  clsb; int /*<<< orphan*/  name; int /*<<< orphan*/  hw; int /*<<< orphan*/  (* write_reg ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  state; int /*<<< orphan*/  ch; int /*<<< orphan*/  err_rdo; int /*<<< orphan*/  err_tx; } ;
struct isar_ch {TYPE_1__ bch; } ;

/* Variables and functions */
 int BSTEV_RBO ; 
 int BSTEV_TBO ; 
 int DTMF_TONE_VAL ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
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
 int /*<<< orphan*/  ISDN_P_B_MODEM_ASYNC ; 
 int /*<<< orphan*/  ISDN_P_B_RAW ; 
 int /*<<< orphan*/  ISDN_P_B_T30_FAX ; 
 int /*<<< orphan*/  MISDN_ID_ANY ; 
 int /*<<< orphan*/  PH_CONTROL_IND ; 
 int /*<<< orphan*/  _queue_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_send (struct isar_hw*,int) ; 
 int /*<<< orphan*/  get_irq_infos (struct isar_hw*) ; 
 int /*<<< orphan*/  isar_pump_statev_fax (struct isar_ch*,int) ; 
 int /*<<< orphan*/  isar_pump_statev_modem (struct isar_ch*,int) ; 
 int /*<<< orphan*/  isar_pump_status_rsp (struct isar_ch*) ; 
 int /*<<< orphan*/  isar_rcv_frame (struct isar_ch*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  rcv_mbox (struct isar_hw*,int /*<<< orphan*/ *) ; 
 struct isar_ch* sel_bch_isar (struct isar_hw*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mISDNisar_irq(struct isar_hw *isar)
{
	struct isar_ch *ch;

	get_irq_infos(isar);
	switch (isar->iis & ISAR_IIS_MSCMSD) {
	case ISAR_IIS_RDATA:
		ch = sel_bch_isar(isar, isar->iis >> 6);
		if (ch)
			isar_rcv_frame(ch);
		else {
			pr_debug("%s: ISAR spurious IIS_RDATA %x/%x/%x\n",
				isar->name, isar->iis, isar->cmsb,
				isar->clsb);
			isar->write_reg(isar->hw, ISAR_IIA, 0);
		}
		break;
	case ISAR_IIS_GSTEV:
		isar->write_reg(isar->hw, ISAR_IIA, 0);
		isar->bstat |= isar->cmsb;
		check_send(isar, isar->cmsb);
		break;
	case ISAR_IIS_BSTEV:
#ifdef ERROR_STATISTIC
		ch = sel_bch_isar(isar, isar->iis >> 6);
		if (ch) {
			if (isar->cmsb == BSTEV_TBO)
				ch->bch.err_tx++;
			if (isar->cmsb == BSTEV_RBO)
				ch->bch.err_rdo++;
		}
#endif
		pr_debug("%s: Buffer STEV dpath%d msb(%x)\n",
			isar->name, isar->iis>>6, isar->cmsb);
		isar->write_reg(isar->hw, ISAR_IIA, 0);
		break;
	case ISAR_IIS_PSTEV:
		ch = sel_bch_isar(isar, isar->iis >> 6);
		if (ch) {
			rcv_mbox(isar, NULL);
			if (ch->bch.state == ISDN_P_B_MODEM_ASYNC)
				isar_pump_statev_modem(ch, isar->cmsb);
			else if (ch->bch.state == ISDN_P_B_T30_FAX)
				isar_pump_statev_fax(ch, isar->cmsb);
			else if (ch->bch.state == ISDN_P_B_RAW) {
				int	tt;
				tt = isar->cmsb | 0x30;
				if (tt == 0x3e)
					tt = '*';
				else if (tt == 0x3f)
					tt = '#';
				else if (tt > '9')
					tt += 7;
				tt |= DTMF_TONE_VAL;
				_queue_data(&ch->bch.ch, PH_CONTROL_IND,
					MISDN_ID_ANY, sizeof(tt), &tt,
					GFP_ATOMIC);
			} else
				pr_debug("%s: ISAR IIS_PSTEV pm %d sta %x\n",
					isar->name, ch->bch.state,
					isar->cmsb);
		} else {
			pr_debug("%s: ISAR spurious IIS_PSTEV %x/%x/%x\n",
				isar->name, isar->iis, isar->cmsb,
				isar->clsb);
			isar->write_reg(isar->hw, ISAR_IIA, 0);
		}
		break;
	case ISAR_IIS_PSTRSP:
		ch = sel_bch_isar(isar, isar->iis >> 6);
		if (ch) {
			rcv_mbox(isar, NULL);
			isar_pump_status_rsp(ch);
		} else {
			pr_debug("%s: ISAR spurious IIS_PSTRSP %x/%x/%x\n",
				isar->name, isar->iis, isar->cmsb,
				isar->clsb);
			isar->write_reg(isar->hw, ISAR_IIA, 0);
		}
		break;
	case ISAR_IIS_DIAG:
	case ISAR_IIS_BSTRSP:
	case ISAR_IIS_IOM2RSP:
		rcv_mbox(isar, NULL);
		break;
	case ISAR_IIS_INVMSG:
		rcv_mbox(isar, NULL);
		pr_debug("%s: invalid msg his:%x\n", isar->name, isar->cmsb);
		break;
	default:
		rcv_mbox(isar, NULL);
		pr_debug("%s: unhandled msg iis(%x) ctrl(%x/%x)\n",
			isar->name, isar->iis, isar->cmsb, isar->clsb);
		break;
	}
}