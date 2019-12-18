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
typedef  TYPE_1__ m68kregs_struct ;
struct TYPE_9__ {int /*<<< orphan*/  buttonStep; int /*<<< orphan*/  regList; int /*<<< orphan*/  bpList; int /*<<< orphan*/  uLabel; } ;
typedef  TYPE_2__ YuiM68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68KGetRegisters (TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_m68k_update_codelist (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yui_m68k_update_reglist (TYPE_2__*,TYPE_1__*) ; 

void yui_m68k_update(YuiM68k * m68k) {
  m68kregs_struct m68kregs;
  M68KGetRegisters(&m68kregs);
  yui_m68k_update_codelist(m68k,m68kregs.PC);
  yui_m68k_update_reglist(m68k, &m68kregs);	
  gtk_widget_set_sensitive(m68k->uLabel, TRUE);
  gtk_widget_set_sensitive(m68k->bpList, TRUE);
  gtk_widget_set_sensitive(m68k->regList, TRUE);
  gtk_widget_set_sensitive(m68k->buttonStep, TRUE);
}