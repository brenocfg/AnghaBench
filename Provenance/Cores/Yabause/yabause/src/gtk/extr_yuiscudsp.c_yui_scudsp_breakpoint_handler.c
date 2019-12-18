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
typedef  TYPE_1__ scudspregs_struct ;
typedef  int /*<<< orphan*/  YuiScudsp ;

/* Variables and functions */
 int /*<<< orphan*/  ScuDspGetRegisters (TYPE_1__*) ; 
 int /*<<< orphan*/ * YUI_SCUDSP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugPauseLoop () ; 
 int /*<<< orphan*/  yui ; 
 int /*<<< orphan*/  yui_scudsp_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_scudsp_update_codelist (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_scudsp_update_reglist (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  yui_window_pause (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_scudsp_breakpoint_handler (u32 addr) {

  yui_window_pause(yui);
  {
    scudspregs_struct scudspregs;
    YuiScudsp* scudsp = YUI_SCUDSP(yui_scudsp_new( yui ));
    
    ScuDspGetRegisters(&scudspregs);
    yui_scudsp_update_reglist(scudsp, &scudspregs);
    yui_scudsp_update_codelist(scudsp, scudspregs.PC);  
  }
  debugPauseLoop(); /* execution is suspended inside a normal cycle - enter secondary gtk loop */
}