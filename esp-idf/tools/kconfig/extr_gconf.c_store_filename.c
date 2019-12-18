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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkFileSelection ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_FILE_SELECTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ conf_write (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * gtk_file_selection_get_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  text_insert_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
store_filename(GtkFileSelection * file_selector, gpointer user_data)
{
	const gchar *fn;

	fn = gtk_file_selection_get_filename(GTK_FILE_SELECTION
					     (user_data));

	if (conf_write(fn))
		text_insert_msg(_("Error"), _("Unable to save configuration !"));

	gtk_widget_destroy(GTK_WIDGET(user_data));
}