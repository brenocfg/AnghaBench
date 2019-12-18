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
struct TYPE_3__ {scalar_t__ bus; scalar_t__ cfg_reg; } ;
struct TYPE_4__ {TYPE_1__ sedl; } ;
struct IsdnCardState {scalar_t__ subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ SEDL_BUS_PCI ; 
 scalar_t__ SEDL_SPEED_FAX ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 

__attribute__((used)) static void
release_io_sedlbauer(struct IsdnCardState *cs)
{
	int bytecnt = 8;

	if (cs->subtyp == SEDL_SPEED_FAX) {
		bytecnt = 16;
	} else if (cs->hw.sedl.bus == SEDL_BUS_PCI) {
		bytecnt = 256;
	}
	if (cs->hw.sedl.cfg_reg)
		release_region(cs->hw.sedl.cfg_reg, bytecnt);
}