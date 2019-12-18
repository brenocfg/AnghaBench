#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  PC; } ;
typedef  TYPE_1__ m68kregs_struct ;
typedef  int /*<<< orphan*/  YuiM68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68KGetRegisters (TYPE_1__*) ; 
 int /*<<< orphan*/ * YUI_M68K (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugPauseLoop () ; 
 int /*<<< orphan*/  yui ; 
 int /*<<< orphan*/  yui_m68k_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_m68k_update_codelist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_m68k_update_reglist (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  yui_window_pause (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_m68k_breakpoint_handler (u32 addr) {

  yui_window_pause(yui);
  {
    m68kregs_struct regs;
    YuiM68k* m68k = YUI_M68K(yui_m68k_new( yui ));
    
    M68KGetRegisters(&regs);
    yui_m68k_update_codelist(m68k,regs.PC);
    yui_m68k_update_reglist(m68k,&regs);
  }
  debugPauseLoop(); /* execution is suspended inside a normal cycle - enter secondary gtk loop */
}