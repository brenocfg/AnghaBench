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
typedef  scalar_t__ gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_4__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  PopplerAttachment ;
typedef  int /*<<< orphan*/  GtkFileChooser ;
typedef  TYPE_1__ GError ;

/* Variables and functions */
 scalar_t__ GTK_RESPONSE_ACCEPT ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_file_chooser_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poppler_attachment_save (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 

__attribute__((used)) static void
pgd_attachments_save_dialog_response (GtkFileChooser    *file_chooser,
				      gint               response,
				      PopplerAttachment *attachment)
{
	gchar  *filename;
	GError *error = NULL;
	
	if (response != GTK_RESPONSE_ACCEPT) {
		g_object_unref (attachment);
		gtk_widget_destroy (GTK_WIDGET (file_chooser));
		return;
	}

	filename = gtk_file_chooser_get_filename (file_chooser);
	if (!poppler_attachment_save (attachment, filename, &error)) {
		g_warning ("%s", error->message);
		g_error_free (error);
	}
	g_free (filename);
	g_object_unref (attachment);
	gtk_widget_destroy (GTK_WIDGET (file_chooser));
}