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
struct TYPE_3__ {int /*<<< orphan*/  ipac; int /*<<< orphan*/  cfg_reg; int /*<<< orphan*/ * hscx; } ;
struct TYPE_4__ {TYPE_1__ gazel; } ;
struct IsdnCardState {int subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
#define  R647 131 
#define  R685 130 
#define  R742 129 
#define  R753 128 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
release_io_gazel(struct IsdnCardState *cs)
{
	unsigned int i;

	switch (cs->subtyp) {
		case R647:
			for (i = 0x0000; i < 0xC000; i += 0x1000)
				release_region(i + cs->hw.gazel.hscx[0], 16);
			release_region(0xC000 + cs->hw.gazel.hscx[0], 1);
			break;

		case R685:
			release_region(cs->hw.gazel.hscx[0], 0x100);
			release_region(cs->hw.gazel.cfg_reg, 0x80);
			break;

		case R753:
			release_region(cs->hw.gazel.ipac, 0x8);
			release_region(cs->hw.gazel.cfg_reg, 0x80);
			break;

		case R742:
			release_region(cs->hw.gazel.ipac, 8);
			break;
	}
}