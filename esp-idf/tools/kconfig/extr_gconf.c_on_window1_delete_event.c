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
typedef  int /*<<< orphan*/  gpointer ;
typedef  int gint ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_4__ {int /*<<< orphan*/  vbox; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkDialogFlags ;
typedef  int /*<<< orphan*/  GdkEvent ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_CONTAINER (int /*<<< orphan*/ ) ; 
 TYPE_1__* GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int GTK_DIALOG_DESTROY_WITH_PARENT ; 
 int GTK_DIALOG_MODAL ; 
#define  GTK_RESPONSE_CANCEL 131 
#define  GTK_RESPONSE_DELETE_EVENT 130 
#define  GTK_RESPONSE_NO 129 
#define  GTK_RESPONSE_YES 128 
 int /*<<< orphan*/  GTK_STOCK_CANCEL ; 
 int /*<<< orphan*/  GTK_STOCK_NO ; 
 int /*<<< orphan*/  GTK_STOCK_OK ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  conf_get_changed () ; 
 int /*<<< orphan*/  gtk_container_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_dialog_new_with_buttons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int gtk_dialog_run (TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_dialog_set_default_response (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * gtk_label_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_wnd ; 
 int /*<<< orphan*/  on_save_activate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

gboolean on_window1_delete_event(GtkWidget * widget, GdkEvent * event,
				 gpointer user_data)
{
	GtkWidget *dialog, *label;
	gint result;

	if (!conf_get_changed())
		return FALSE;

	dialog = gtk_dialog_new_with_buttons(_("Warning !"),
					     GTK_WINDOW(main_wnd),
					     (GtkDialogFlags)
					     (GTK_DIALOG_MODAL |
					      GTK_DIALOG_DESTROY_WITH_PARENT),
					     GTK_STOCK_OK,
					     GTK_RESPONSE_YES,
					     GTK_STOCK_NO,
					     GTK_RESPONSE_NO,
					     GTK_STOCK_CANCEL,
					     GTK_RESPONSE_CANCEL, NULL);
	gtk_dialog_set_default_response(GTK_DIALOG(dialog),
					GTK_RESPONSE_CANCEL);

	label = gtk_label_new(_("\nSave configuration ?\n"));
	gtk_container_add(GTK_CONTAINER(GTK_DIALOG(dialog)->vbox), label);
	gtk_widget_show(label);

	result = gtk_dialog_run(GTK_DIALOG(dialog));
	switch (result) {
	case GTK_RESPONSE_YES:
		on_save_activate(NULL, NULL);
		return FALSE;
	case GTK_RESPONSE_NO:
		return FALSE;
	case GTK_RESPONSE_CANCEL:
	case GTK_RESPONSE_DELETE_EVENT:
	default:
		gtk_widget_destroy(dialog);
		return TRUE;
	}

	return FALSE;
}