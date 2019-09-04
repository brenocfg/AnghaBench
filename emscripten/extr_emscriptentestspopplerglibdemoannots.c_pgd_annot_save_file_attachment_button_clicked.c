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
typedef  int /*<<< orphan*/  PopplerAnnotFileAttachment ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkButton ;

/* Variables and functions */
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
 int /*<<< orphan*/  gtk_widget_get_toplevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_annots_file_attachment_save_dialog_response ; 
 TYPE_1__* poppler_annot_file_attachment_get_attachment (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_annot_save_file_attachment_button_clicked (GtkButton                  *button,
					       PopplerAnnotFileAttachment *annot)
{
    GtkWidget         *file_chooser;
    PopplerAttachment *attachment;

    attachment = poppler_annot_file_attachment_get_attachment (annot);
    if (!attachment)
        return;

    file_chooser = gtk_file_chooser_dialog_new ("Save attachment",
						GTK_WINDOW (gtk_widget_get_toplevel (GTK_WIDGET (button))),
						GTK_FILE_CHOOSER_ACTION_SAVE,
						GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
						GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
						NULL);
    gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (file_chooser), attachment->name);
    g_signal_connect (G_OBJECT (file_chooser), "response",
		      G_CALLBACK (pgd_annots_file_attachment_save_dialog_response),
		      (gpointer) attachment);
    gtk_widget_show (file_chooser);
}