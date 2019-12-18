#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sync; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {TYPE_1__ st; } ;
struct atafb_par {int /*<<< orphan*/  screen_base; TYPE_2__ hw; } ;
struct TYPE_8__ {int bas_hi; int bas_md; int bas_lo; int /*<<< orphan*/  syncmode; } ;
struct TYPE_7__ {int /*<<< orphan*/  st_shiftmode; } ;

/* Variables and functions */
 scalar_t__ ATARIHW_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTD_SHIFTER ; 
 int /*<<< orphan*/  phys_to_virt (unsigned long) ; 
 TYPE_4__ shifter ; 
 TYPE_3__ shifter_tt ; 

__attribute__((used)) static void stste_get_par(struct atafb_par *par)
{
	unsigned long addr;
	par->hw.st.mode = shifter_tt.st_shiftmode;
	par->hw.st.sync = shifter.syncmode;
	addr = ((shifter.bas_hi & 0xff) << 16) |
	       ((shifter.bas_md & 0xff) << 8);
	if (ATARIHW_PRESENT(EXTD_SHIFTER))
		addr |= (shifter.bas_lo & 0xff);
	par->screen_base = phys_to_virt(addr);
}