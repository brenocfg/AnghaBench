#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  buttonStep; int /*<<< orphan*/  regList; int /*<<< orphan*/  bpList; int /*<<< orphan*/  uLabel; } ;
typedef  TYPE_1__ YuiM68k ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_m68k_clear(YuiM68k * m68k) {
  
  gtk_widget_set_sensitive(m68k->uLabel, FALSE);
  gtk_widget_set_sensitive(m68k->bpList, FALSE);
  gtk_widget_set_sensitive(m68k->regList, FALSE);
  gtk_widget_set_sensitive(m68k->buttonStep, FALSE);
}