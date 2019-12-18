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
struct TYPE_9__ {int /*<<< orphan*/  debugsh; int /*<<< orphan*/  view; } ;
typedef  TYPE_2__ YuiSh ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkMenuItem ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_TREE_VIEW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SH2AddCodeBreakpoint (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SH2GetRegisters (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SH2UpdateBreakpointList (TYPE_2__*) ; 
 int /*<<< orphan*/  SH2UpdateCodeList (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sscanf (int /*<<< orphan*/ *,char*,unsigned int*) ; 

void yui_sh_popup_add_bp(GtkMenuItem * menuitem, gpointer user_data) {
	YuiSh * sh2 = user_data;
	GtkTreeView * view = GTK_TREE_VIEW(sh2->view);
	GtkTreeSelection * selection;
	GtkTreeModel * model;
	GtkTreeIter iter;
	gchar * address_s;
	unsigned int address;

	selection = gtk_tree_view_get_selection(view);

	gtk_tree_selection_get_selected(selection, &model, &iter);

	gtk_tree_model_get(model, &iter, 1, &address_s, -1);

	sscanf(address_s, "0x%08X", &address);

	SH2AddCodeBreakpoint(sh2->debugsh, address);

	g_free(address_s);

	{
		sh2regs_struct sh2regs;
		SH2GetRegisters(sh2->debugsh, &sh2regs);
		SH2UpdateCodeList(sh2,sh2regs.PC);
		SH2UpdateBreakpointList(sh2);
	}
}