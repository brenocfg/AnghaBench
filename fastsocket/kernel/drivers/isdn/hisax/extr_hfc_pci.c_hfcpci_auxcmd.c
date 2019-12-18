#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_15__ {int int_m1; int sctrl; int nt_mode; int trm; int fifo_en; int sctrl_r; int conn; int ctmt; scalar_t__ bswapped; scalar_t__ nt_timer; } ;
struct TYPE_16__ {TYPE_6__ hfcpci; } ;
struct TYPE_11__ {int ph_state; } ;
struct TYPE_12__ {TYPE_2__ hfcpci; } ;
struct IsdnCardState {int chanlimit; int logecho; int /*<<< orphan*/  lock; TYPE_7__ hw; TYPE_5__* stlist; TYPE_3__ dc; } ;
struct TYPE_10__ {scalar_t__ num; } ;
struct TYPE_17__ {int arg; TYPE_1__ parm; } ;
typedef  TYPE_8__ isdn_ctrl ;
struct TYPE_13__ {int /*<<< orphan*/  l2l1; } ;
struct TYPE_14__ {TYPE_4__ l2; } ;

/* Variables and functions */
 int CLKDEL_NT ; 
 int EINVAL ; 
 int HFCPCI_ACTIVATE ; 
 int /*<<< orphan*/  HFCPCI_CLKDEL ; 
 int /*<<< orphan*/  HFCPCI_CONNECT ; 
 int /*<<< orphan*/  HFCPCI_CTMT ; 
 int HFCPCI_DO_ACTION ; 
 int HFCPCI_FIFOEN_B2RX ; 
 int /*<<< orphan*/  HFCPCI_FIFO_EN ; 
 int HFCPCI_INTS_B1REC ; 
 int HFCPCI_INTS_B1TRANS ; 
 int HFCPCI_INTS_B2REC ; 
 int HFCPCI_INTS_B2TRANS ; 
 int /*<<< orphan*/  HFCPCI_INT_M1 ; 
 int HFCPCI_LOAD_STATE ; 
 int /*<<< orphan*/  HFCPCI_SCTRL ; 
 int /*<<< orphan*/  HFCPCI_SCTRL_R ; 
 int /*<<< orphan*/  HFCPCI_STATES ; 
 int /*<<< orphan*/  HFCPCI_TRM ; 
 int SCTRL_B2_ENA ; 
 int SCTRL_MODE_NT ; 
 int /*<<< orphan*/  Write_hfc (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dch_nt_l2l1 ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
hfcpci_auxcmd(struct IsdnCardState *cs, isdn_ctrl * ic)
{
	u_long	flags;
	int	i = *(unsigned int *) ic->parm.num;

	if ((ic->arg == 98) &&
	    (!(cs->hw.hfcpci.int_m1 & (HFCPCI_INTS_B2TRANS + HFCPCI_INTS_B2REC + HFCPCI_INTS_B1TRANS + HFCPCI_INTS_B1REC)))) {
	    	spin_lock_irqsave(&cs->lock, flags);
		Write_hfc(cs, HFCPCI_CLKDEL, CLKDEL_NT); /* ST-Bit delay for NT-Mode */
		Write_hfc(cs, HFCPCI_STATES, HFCPCI_LOAD_STATE | 0);	/* HFC ST G0 */
		udelay(10);
		cs->hw.hfcpci.sctrl |= SCTRL_MODE_NT;
		Write_hfc(cs, HFCPCI_SCTRL, cs->hw.hfcpci.sctrl);	/* set NT-mode */
		udelay(10);
		Write_hfc(cs, HFCPCI_STATES, HFCPCI_LOAD_STATE | 1);	/* HFC ST G1 */
		udelay(10);
		Write_hfc(cs, HFCPCI_STATES, 1 | HFCPCI_ACTIVATE | HFCPCI_DO_ACTION);
		cs->dc.hfcpci.ph_state = 1;
		cs->hw.hfcpci.nt_mode = 1;
		cs->hw.hfcpci.nt_timer = 0;
		cs->stlist->l2.l2l1 = dch_nt_l2l1;
		spin_unlock_irqrestore(&cs->lock, flags);
		debugl1(cs, "NT mode activated");
		return (0);
	}
	if ((cs->chanlimit > 1) || (cs->hw.hfcpci.bswapped) ||
	    (cs->hw.hfcpci.nt_mode) || (ic->arg != 12))
		return (-EINVAL);

	spin_lock_irqsave(&cs->lock, flags);
	if (i) {
		cs->logecho = 1;
		cs->hw.hfcpci.trm |= 0x20;	/* enable echo chan */
		cs->hw.hfcpci.int_m1 |= HFCPCI_INTS_B2REC;
		cs->hw.hfcpci.fifo_en |= HFCPCI_FIFOEN_B2RX;
	} else {
		cs->logecho = 0;
		cs->hw.hfcpci.trm &= ~0x20;	/* disable echo chan */
		cs->hw.hfcpci.int_m1 &= ~HFCPCI_INTS_B2REC;
		cs->hw.hfcpci.fifo_en &= ~HFCPCI_FIFOEN_B2RX;
	}
	cs->hw.hfcpci.sctrl_r &= ~SCTRL_B2_ENA;
	cs->hw.hfcpci.sctrl &= ~SCTRL_B2_ENA;
	cs->hw.hfcpci.conn |= 0x10;	/* B2-IOM -> B2-ST */
	cs->hw.hfcpci.ctmt &= ~2;
	Write_hfc(cs, HFCPCI_CTMT, cs->hw.hfcpci.ctmt);
	Write_hfc(cs, HFCPCI_SCTRL_R, cs->hw.hfcpci.sctrl_r);
	Write_hfc(cs, HFCPCI_SCTRL, cs->hw.hfcpci.sctrl);
	Write_hfc(cs, HFCPCI_CONNECT, cs->hw.hfcpci.conn);
	Write_hfc(cs, HFCPCI_TRM, cs->hw.hfcpci.trm);
	Write_hfc(cs, HFCPCI_FIFO_EN, cs->hw.hfcpci.fifo_en);
	Write_hfc(cs, HFCPCI_INT_M1, cs->hw.hfcpci.int_m1);
	spin_unlock_irqrestore(&cs->lock, flags);
	return (0);
}