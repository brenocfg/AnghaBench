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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkWindow ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_BUTTONS_CLOSE ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_DIALOG_DESTROY_WITH_PARENT ; 
 int /*<<< orphan*/  GTK_MESSAGE_INFO ; 
 int /*<<< orphan*/  gtk_dialog_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_message_dialog_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
message_dialog_run (GtkWindow   *parent,
		    const gchar *message)
{
	GtkWidget *dialog;

	dialog = gtk_message_dialog_new (parent,
					 GTK_DIALOG_DESTROY_WITH_PARENT,
					 GTK_MESSAGE_INFO,
					 GTK_BUTTONS_CLOSE,
					 "%s", message);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}