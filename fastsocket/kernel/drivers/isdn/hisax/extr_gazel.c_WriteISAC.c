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
typedef  int u_short ;
typedef  int u_char ;
struct TYPE_3__ {int /*<<< orphan*/  ipac; int /*<<< orphan*/  isac; } ;
struct TYPE_4__ {TYPE_1__ gazel; } ;
struct IsdnCardState {int subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
#define  R647 131 
#define  R685 130 
#define  R742 129 
#define  R753 128 
 int /*<<< orphan*/  writereg (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  writereg_ipac (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
WriteISAC(struct IsdnCardState *cs, u_char offset, u_char value)
{
	u_short off2 = offset;

	switch (cs->subtyp) {
		case R647:
			off2 = ((off2 << 8 & 0xf000) | (off2 & 0xf));
		case R685:
			writereg(cs->hw.gazel.isac, off2, value);
			break;
		case R753:
		case R742:
			writereg_ipac(cs->hw.gazel.ipac, 0x80 + off2, value);
			break;
	}
}