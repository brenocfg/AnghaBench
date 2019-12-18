#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_char ;
struct IsdnCardState {int (* BC_Read_Reg ) (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int debug; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int HFCD_ANYINT ; 
 int HFCD_BUSY_NBUSY ; 
 int /*<<< orphan*/  HFCD_DATA ; 
 int /*<<< orphan*/  HFCD_INT_S1 ; 
 int /*<<< orphan*/  HFCD_STAT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int L1_DEB_ISAC ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int,...) ; 
 int /*<<< orphan*/  hfc2bds0_interrupt (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
hfcs_interrupt(int intno, void *dev_id)
{
	struct IsdnCardState *cs = dev_id;
	u_char val, stat;
	u_long flags;

	spin_lock_irqsave(&cs->lock, flags);
	if ((HFCD_ANYINT | HFCD_BUSY_NBUSY) & 
		(stat = cs->BC_Read_Reg(cs, HFCD_DATA, HFCD_STAT))) {
		val = cs->BC_Read_Reg(cs, HFCD_DATA, HFCD_INT_S1);
		if (cs->debug & L1_DEB_ISAC)
			debugl1(cs, "HFCS: stat(%02x) s1(%02x)", stat, val);
		hfc2bds0_interrupt(cs, val);
	} else {
		if (cs->debug & L1_DEB_ISAC)
			debugl1(cs, "HFCS: irq_no_irq stat(%02x)", stat);
	}
	spin_unlock_irqrestore(&cs->lock, flags);
	return IRQ_HANDLED;
}