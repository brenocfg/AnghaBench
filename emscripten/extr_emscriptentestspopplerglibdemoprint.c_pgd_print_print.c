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
struct TYPE_4__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  PgdPrintDemo ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkPrintOperation ;
typedef  TYPE_1__ GError ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_BUTTONS_CLOSE ; 
 int /*<<< orphan*/  GTK_DIALOG_DESTROY_WITH_PARENT ; 
 int /*<<< orphan*/  GTK_MESSAGE_ERROR ; 
 int /*<<< orphan*/  GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_message_dialog_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_print_operation_new () ; 
 int /*<<< orphan*/  gtk_print_operation_run (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  gtk_print_operation_set_custom_tab_label (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  gtk_widget_destroy ; 
 int /*<<< orphan*/  gtk_widget_get_toplevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_print_begin_print ; 
 int /*<<< orphan*/  pgd_print_create_custom_widget ; 
 int /*<<< orphan*/  pgd_print_custom_widget_apply ; 
 int /*<<< orphan*/  pgd_print_draw_page ; 

__attribute__((used)) static void
pgd_print_print (GtkWidget    *button,
		 PgdPrintDemo *demo)
{
	GtkPrintOperation *op;
	GError            *error = NULL;

	op = gtk_print_operation_new ();
        gtk_print_operation_set_custom_tab_label (op, "PDF Options");
	g_signal_connect (op, "begin-print",
			  G_CALLBACK (pgd_print_begin_print),
			  demo);
	g_signal_connect (op, "draw-page",
			  G_CALLBACK (pgd_print_draw_page),
			  demo);
        g_signal_connect (op, "create_custom_widget",
                          G_CALLBACK (pgd_print_create_custom_widget),
                          demo);
        g_signal_connect (op, "custom_widget_apply",
                          G_CALLBACK (pgd_print_custom_widget_apply),
                          demo);
	gtk_print_operation_run (op,
				 GTK_PRINT_OPERATION_ACTION_PRINT_DIALOG,
				 GTK_WINDOW (gtk_widget_get_toplevel (button)),
				 &error);
	if (error) {
		GtkWidget *dialog;

		dialog = gtk_message_dialog_new (GTK_WINDOW (gtk_widget_get_toplevel (button)),
						 GTK_DIALOG_DESTROY_WITH_PARENT,
						 GTK_MESSAGE_ERROR,
						 GTK_BUTTONS_CLOSE,
						 "%s", error->message);
		g_error_free (error);

		g_signal_connect (dialog, "response",
				  G_CALLBACK (gtk_widget_destroy), NULL);

		gtk_widget_show (dialog);
	}
	g_object_unref (op);
}