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
struct TYPE_3__ {scalar_t__ isac; scalar_t__ cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ teles3; } ;
struct IsdnCardState {scalar_t__ typ; int irq; TYPE_2__ hw; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  HZDELAY (int) ; 
 scalar_t__ ISDN_CTYPE_COMPAQ_ISA ; 
 scalar_t__ ISDN_CTYPE_TELESPCMCIA ; 
 int /*<<< orphan*/  byteout (scalar_t__,int) ; 

__attribute__((used)) static int
reset_teles3(struct IsdnCardState *cs)
{
	u_char irqcfg;

	if (cs->typ != ISDN_CTYPE_TELESPCMCIA) {
		if ((cs->hw.teles3.cfg_reg) && (cs->typ != ISDN_CTYPE_COMPAQ_ISA)) {
			switch (cs->irq) {
				case 2:
				case 9:
					irqcfg = 0x00;
					break;
				case 3:
					irqcfg = 0x02;
					break;
				case 4:
					irqcfg = 0x04;
					break;
				case 5:
					irqcfg = 0x06;
					break;
				case 10:
					irqcfg = 0x08;
					break;
				case 11:
					irqcfg = 0x0A;
					break;
				case 12:
					irqcfg = 0x0C;
					break;
				case 15:
					irqcfg = 0x0E;
					break;
				default:
					return(1);
			}
			byteout(cs->hw.teles3.cfg_reg + 4, irqcfg);
			HZDELAY(HZ / 10 + 1);
			byteout(cs->hw.teles3.cfg_reg + 4, irqcfg | 1);
			HZDELAY(HZ / 10 + 1);
		} else if (cs->typ == ISDN_CTYPE_COMPAQ_ISA) {
			byteout(cs->hw.teles3.cfg_reg, 0xff);
			HZDELAY(2);
			byteout(cs->hw.teles3.cfg_reg, 0x00);
			HZDELAY(2);
		} else {
			/* Reset off for 16.3 PnP , thanks to Georg Acher */
			byteout(cs->hw.teles3.isac + 0x3c, 0);
			HZDELAY(2);
			byteout(cs->hw.teles3.isac + 0x3c, 1);
			HZDELAY(2);
		}
	}
	return(0);
}