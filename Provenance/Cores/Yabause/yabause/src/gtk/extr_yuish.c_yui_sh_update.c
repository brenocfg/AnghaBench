#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  PC; } ;
typedef  TYPE_1__ sh2regs_struct ;
struct TYPE_12__ {TYPE_5__* debugsh; int /*<<< orphan*/  buttonStep; int /*<<< orphan*/  regList; int /*<<< orphan*/  mbpList; int /*<<< orphan*/  bpList; } ;
typedef  TYPE_2__ YuiSh ;
struct TYPE_14__ {int /*<<< orphan*/  isIdle; } ;
struct TYPE_13__ {int /*<<< orphan*/  IsSSH2Running; } ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2GetRegisters (TYPE_5__*,TYPE_1__*) ; 
 int /*<<< orphan*/  SH2UpdateCodeList (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2UpdateRegList (TYPE_2__*,TYPE_1__*) ; 
 TYPE_5__* SSH2 ; 
 int TRUE ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int) ; 
 TYPE_4__ yabsys ; 

void yui_sh_update(YuiSh * sh) {
  sh2regs_struct sh2regs;
  SH2GetRegisters(sh->debugsh, &sh2regs);
  SH2UpdateCodeList(sh,sh2regs.PC);
  SH2UpdateRegList(sh, &sh2regs);	
  gtk_widget_set_sensitive(sh->bpList, TRUE);
  gtk_widget_set_sensitive(sh->mbpList, TRUE);
  gtk_widget_set_sensitive(sh->regList, TRUE);
  gtk_widget_set_sensitive(GTK_WIDGET(sh->buttonStep), 
			   !sh->debugsh->isIdle && !(( sh->debugsh == SSH2 )&&( !yabsys.IsSSH2Running )));
}