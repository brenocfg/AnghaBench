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
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_9__ {int /*<<< orphan*/  debugsh; int /*<<< orphan*/  bpList; } ;
typedef  TYPE_2__ YuiSh ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2DelCodeBreakpoint (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SH2GetRegisters (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SH2UpdateBreakpointList (TYPE_2__*) ; 
 int /*<<< orphan*/  SH2UpdateCodeList (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ *,char*,unsigned int*) ; 

void yui_sh_bp_remove(GtkWidget * menuitem, gpointer user_data) {
	GtkTreeSelection * selection;
	YuiSh * sh2 = user_data;
	GtkTreeIter iter;
	GtkTreeModel * model;
	gchar * address_s;
	unsigned int address;
	GtkTreeView * view;

	view  = GTK_TREE_VIEW(sh2->bpList);

	  selection = gtk_tree_view_get_selection(view);

	  gtk_tree_selection_get_selected(selection, &model, &iter);

	  gtk_tree_model_get(model, &iter, 0, &address_s, -1);
          sscanf(address_s, "%8X", &address);

          SH2DelCodeBreakpoint(sh2->debugsh, address);

	{
		sh2regs_struct sh2regs;
		SH2GetRegisters(sh2->debugsh, &sh2regs);
		SH2UpdateCodeList(sh2,sh2regs.PC);
		SH2UpdateBreakpointList(sh2);
	}
}