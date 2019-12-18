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
struct TYPE_3__ {int /*<<< orphan*/  store; int /*<<< orphan*/  buttonStep; int /*<<< orphan*/  regList; int /*<<< orphan*/  mbpList; int /*<<< orphan*/  bpList; } ;
typedef  TYPE_1__ YuiSh ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_list_store_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void yui_sh_clear(YuiSh * sh) {
  
  gtk_widget_set_sensitive(sh->bpList, FALSE);
  gtk_widget_set_sensitive(sh->mbpList, FALSE);
  gtk_widget_set_sensitive(sh->regList, FALSE);
  gtk_widget_set_sensitive(GTK_WIDGET(sh->buttonStep), FALSE);

  gtk_list_store_clear(sh->store);
}