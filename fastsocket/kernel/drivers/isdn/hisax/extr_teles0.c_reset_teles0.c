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
struct TYPE_3__ {int phymem; scalar_t__ membase; scalar_t__ cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ teles0; } ;
struct IsdnCardState {int irq; TYPE_2__ hw; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  HZDELAY (int) ; 
 int /*<<< orphan*/  byteout (scalar_t__,int) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static int
reset_teles0(struct IsdnCardState *cs)
{
	u_char cfval;

	if (cs->hw.teles0.cfg_reg) {
		switch (cs->irq) {
			case 2:
			case 9:
				cfval = 0x00;
				break;
			case 3:
				cfval = 0x02;
				break;
			case 4:
				cfval = 0x04;
				break;
			case 5:
				cfval = 0x06;
				break;
			case 10:
				cfval = 0x08;
				break;
			case 11:
				cfval = 0x0A;
				break;
			case 12:
				cfval = 0x0C;
				break;
			case 15:
				cfval = 0x0E;
				break;
			default:
				return(1);
		}
		cfval |= ((cs->hw.teles0.phymem >> 9) & 0xF0);
		byteout(cs->hw.teles0.cfg_reg + 4, cfval);
		HZDELAY(HZ / 10 + 1);
		byteout(cs->hw.teles0.cfg_reg + 4, cfval | 1);
		HZDELAY(HZ / 10 + 1);
	}
	writeb(0, cs->hw.teles0.membase + 0x80); mb();
	HZDELAY(HZ / 5 + 1);
	writeb(1, cs->hw.teles0.membase + 0x80); mb();
	HZDELAY(HZ / 5 + 1);
	return(0);
}