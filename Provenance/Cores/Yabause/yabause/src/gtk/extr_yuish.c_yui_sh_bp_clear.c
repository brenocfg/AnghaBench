#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  PC; } ;
typedef  TYPE_1__ sh2regs_struct ;
typedef  TYPE_2__* gpointer ;
struct TYPE_9__ {int /*<<< orphan*/  debugsh; } ;
typedef  TYPE_2__ YuiSh ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  SH2ClearCodeBreakpoints (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2GetRegisters (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SH2UpdateBreakpointList (TYPE_2__*) ; 
 int /*<<< orphan*/  SH2UpdateCodeList (TYPE_2__*,int /*<<< orphan*/ ) ; 

void yui_sh_bp_clear(GtkWidget * menuitem, gpointer user_data) {
	YuiSh * sh2 = user_data;

	SH2ClearCodeBreakpoints(sh2->debugsh);

	{
		sh2regs_struct sh2regs;
		SH2GetRegisters(sh2->debugsh, &sh2regs);
		SH2UpdateCodeList(sh2,sh2regs.PC);
		SH2UpdateBreakpointList(sh2);
	}
}