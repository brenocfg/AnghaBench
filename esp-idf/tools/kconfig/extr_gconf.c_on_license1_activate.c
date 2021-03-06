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
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkMenuItem ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_BUTTONS_CLOSE ; 
 int /*<<< orphan*/  GTK_DIALOG_DESTROY_WITH_PARENT ; 
 int /*<<< orphan*/  GTK_MESSAGE_INFO ; 
 int /*<<< orphan*/  GTK_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_CALLBACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * _ (char*) ; 
 int /*<<< orphan*/  g_signal_connect_swapped (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_message_dialog_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gtk_widget_destroy ; 
 int /*<<< orphan*/  gtk_widget_show_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  main_wnd ; 

void on_license1_activate(GtkMenuItem * menuitem, gpointer user_data)
{
	GtkWidget *dialog;
	const gchar *license_text =
	    _("gkc is released under the terms of the GNU GPL v2.\n"
	      "For more information, please see the source code or\n"
	      "visit http://www.fsf.org/licenses/licenses.html\n");

	dialog = gtk_message_dialog_new(GTK_WINDOW(main_wnd),
					GTK_DIALOG_DESTROY_WITH_PARENT,
					GTK_MESSAGE_INFO,
					GTK_BUTTONS_CLOSE, "%s", license_text);
	g_signal_connect_swapped(GTK_OBJECT(dialog), "response",
				 G_CALLBACK(gtk_widget_destroy),
				 GTK_OBJECT(dialog));
	gtk_widget_show_all(dialog);
}