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
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ conf_read (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  display_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_file_selection_get_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rootmenu ; 
 int /*<<< orphan*/  text_insert_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
load_filename(GtkFileSelection * file_selector, gpointer user_data)
{
	const gchar *fn;

	fn = gtk_file_selection_get_filename(GTK_FILE_SELECTION
					     (user_data));

	if (conf_read(fn))
		text_insert_msg(_("Error"), _("Unable to load configuration !"));
	else
		display_tree(&rootmenu);
}