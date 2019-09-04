#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  gpointer ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  PopplerAnnotFileAttachment ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_TABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_button_new_with_label (char*) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_annot_save_file_attachment_button_clicked ; 
 int /*<<< orphan*/  pgd_table_add_property (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgd_table_add_property_with_custom_widget (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * poppler_annot_file_attachment_get_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pgd_annot_view_set_annot_file_attachment (GtkWidget                  *table,
					  PopplerAnnotFileAttachment *annot,
					  gint                       *row)
{
    GtkWidget *button;
    gchar *text;

    text = poppler_annot_file_attachment_get_name (annot);
    pgd_table_add_property (GTK_TABLE (table), "<b>Attachment Name:</b>", text, row);
    g_free (text);

    button = gtk_button_new_with_label ("Save Attachment");
    g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (pgd_annot_save_file_attachment_button_clicked),
		      (gpointer)annot);
    pgd_table_add_property_with_custom_widget (GTK_TABLE (table), "<b>File Attachment:</b>", button, row);
    gtk_widget_show (button);

}