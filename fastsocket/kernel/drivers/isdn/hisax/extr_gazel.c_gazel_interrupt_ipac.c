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
struct IsdnCardState {int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HSCX_ISTA ; 
 scalar_t__ IPAC_ISTA ; 
 scalar_t__ IPAC_MASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ ISAC_ISTA ; 
 int MAXCOUNT ; 
 int ReadHSCX (struct IsdnCardState*,int,int /*<<< orphan*/ ) ; 
 int ReadISAC (struct IsdnCardState*,scalar_t__) ; 
 int /*<<< orphan*/  WriteISAC (struct IsdnCardState*,scalar_t__,int) ; 
 int /*<<< orphan*/  hscx_int_main (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  isac_interrupt (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t
gazel_interrupt_ipac(int intno, void *dev_id)
{
	struct IsdnCardState *cs = dev_id;
	u_char ista, val;
	int count = 0;
	u_long flags;
	
	spin_lock_irqsave(&cs->lock, flags);
	ista = ReadISAC(cs, IPAC_ISTA - 0x80);
	do {
		if (ista & 0x0f) {
			val = ReadHSCX(cs, 1, HSCX_ISTA);
			if (ista & 0x01)
				val |= 0x01;
			if (ista & 0x04)
				val |= 0x02;
			if (ista & 0x08)
				val |= 0x04;
			if (val) {
				hscx_int_main(cs, val);
			}
		}
		if (ista & 0x20) {
			val = 0xfe & ReadISAC(cs, ISAC_ISTA);
			if (val) {
				isac_interrupt(cs, val);
			}
		}
		if (ista & 0x10) {
			val = 0x01;
			isac_interrupt(cs, val);
		}
		ista = ReadISAC(cs, IPAC_ISTA - 0x80);
		count++;
	}
	while ((ista & 0x3f) && (count < MAXCOUNT));

	WriteISAC(cs, IPAC_MASK - 0x80, 0xFF);
	WriteISAC(cs, IPAC_MASK - 0x80, 0xC0);
	spin_unlock_irqrestore(&cs->lock, flags);
	return IRQ_HANDLED;
}