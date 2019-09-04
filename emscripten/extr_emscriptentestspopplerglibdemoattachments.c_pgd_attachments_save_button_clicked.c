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
typedef  int /*<<< orphan*/  gpointer ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ PopplerAttachment ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkTreeView ;
typedef  int /*<<< orphan*/  GtkTreeSelection ;
typedef  int /*<<< orphan*/  GtkTreeModel ;
typedef  int /*<<< orphan*/  GtkTreeIter ;
typedef  int /*<<< orphan*/  GtkButton ;

/* Variables and functions */
 int /*<<< orphan*/  ATTACHMENTS_ATTACHMENT_COLUMN ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_FILE_CHOOSER_ACTION_SAVE ; 
 int /*<<< orphan*/  GTK_RESPONSE_ACCEPT ; 
 int /*<<< orphan*/  GTK_RESPONSE_CANCEL ; 
 int /*<<< orphan*/  GTK_STOCK_CANCEL ; 
 int /*<<< orphan*/  GTK_STOCK_SAVE ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_file_chooser_dialog_new (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_file_chooser_set_current_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_tree_model_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**,int) ; 
 int /*<<< orphan*/  gtk_tree_selection_get_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_tree_view_get_selection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_toplevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_attachments_save_dialog_response ; 

__attribute__((used)) static void
pgd_attachments_save_button_clicked (GtkButton   *button,
				     GtkTreeView *treeview)
{
	GtkTreeSelection  *selection;
	GtkTreeModel      *model;
	GtkTreeIter        iter;
	GtkWidget         *file_chooser;
	PopplerAttachment *attachment;

	selection = gtk_tree_view_get_selection (treeview);
	if (!gtk_tree_selection_get_selected (selection, &model, &iter)) 
		return;

	gtk_tree_model_get (model, &iter,
			    ATTACHMENTS_ATTACHMENT_COLUMN, &attachment,
			    -1);

	if (!attachment)
		return;

	file_chooser = gtk_file_chooser_dialog_new ("Save attachment",
						    GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (treeview))),
						    GTK_FILE_CHOOSER_ACTION_SAVE,
						    GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
						    GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
						    NULL);
	gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (file_chooser), attachment->name);
	g_signal_connect (G_OBJECT (file_chooser), "response",
			  G_CALLBACK (pgd_attachments_save_dialog_response),
			  (gpointer) attachment);
	gtk_widget_show (file_chooser);
		
}