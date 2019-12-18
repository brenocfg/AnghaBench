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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  PC; } ;
typedef  TYPE_1__ sh2regs_struct ;
struct TYPE_9__ {int /*<<< orphan*/  debugsh; } ;
typedef  TYPE_2__ YuiSh ;
typedef  int /*<<< orphan*/  SH2_struct ;

/* Variables and functions */
 int /*<<< orphan*/ * MSH2 ; 
 int /*<<< orphan*/  SH2GetRegisters (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SH2UpdateCodeList (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2UpdateRegList (TYPE_2__*,TYPE_1__*) ; 
 TYPE_2__* YUI_SH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugPauseLoop () ; 
 int /*<<< orphan*/  yui ; 
 int /*<<< orphan*/  yui_sh_new (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  yui_window_pause (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SH2BreakpointHandler (SH2_struct *context, u32 addr, void *userdata) {

  yui_window_pause(yui);
  {
    sh2regs_struct sh2regs;
    YuiSh* sh2 = YUI_SH(yui_sh_new( yui, context == MSH2 ));
    
    SH2GetRegisters(sh2->debugsh, &sh2regs);
    SH2UpdateRegList(sh2, &sh2regs);
    SH2UpdateCodeList(sh2, sh2regs.PC);  
  }
  debugPauseLoop(); /* execution is suspended inside a normal cycle - enter secondary gtk loop */
}