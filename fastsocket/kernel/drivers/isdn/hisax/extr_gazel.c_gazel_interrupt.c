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
typedef  scalar_t__ u_char ;
struct IsdnCardState {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HSCX_ISTA ; 
 int /*<<< orphan*/  HSCX_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ISAC_ISTA ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int MAXCOUNT ; 
 scalar_t__ ReadHSCX (struct IsdnCardState*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ReadISAC (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteHSCX (struct IsdnCardState*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WriteISAC (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hscx_int_main (struct IsdnCardState*,scalar_t__) ; 
 int /*<<< orphan*/  isac_interrupt (struct IsdnCardState*,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
gazel_interrupt(int intno, void *dev_id)
{
#define MAXCOUNT 5
	struct IsdnCardState *cs = dev_id;
	u_char valisac, valhscx;
	int count = 0;
	u_long flags;

	spin_lock_irqsave(&cs->lock, flags);
	do {
		valhscx = ReadHSCX(cs, 1, HSCX_ISTA);
		if (valhscx)
			hscx_int_main(cs, valhscx);
		valisac = ReadISAC(cs, ISAC_ISTA);
		if (valisac)
			isac_interrupt(cs, valisac);
		count++;
	} while ((valhscx || valisac) && (count < MAXCOUNT));

	WriteHSCX(cs, 0, HSCX_MASK, 0xFF);
	WriteHSCX(cs, 1, HSCX_MASK, 0xFF);
	WriteISAC(cs, ISAC_MASK, 0xFF);
	WriteISAC(cs, ISAC_MASK, 0x0);
	WriteHSCX(cs, 0, HSCX_MASK, 0x0);
	WriteHSCX(cs, 1, HSCX_MASK, 0x0);
	spin_unlock_irqrestore(&cs->lock, flags);
	return IRQ_HANDLED;
}