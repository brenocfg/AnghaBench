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
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GtkWindow ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  scalar_t__ GtkResponseType ;
typedef  int /*<<< orphan*/  GtkMessageType ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_BUTTONS_NONE ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_DIALOG_MODAL ; 
 scalar_t__ GTK_RESPONSE_NO ; 
 int /*<<< orphan*/  GTK_RESPONSE_YES ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  gtk_dialog_add_buttons (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_dialog_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_message_dialog_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 

gboolean
ghb_message_dialog(GtkWindow *parent, GtkMessageType type, const gchar *message, const gchar *no, const gchar *yes)
{
    GtkWidget *dialog;
    GtkResponseType response;

    // Toss up a warning dialog
    dialog = gtk_message_dialog_new(parent, GTK_DIALOG_MODAL,
                            type, GTK_BUTTONS_NONE,
                            "%s", message);
    gtk_dialog_add_buttons( GTK_DIALOG(dialog),
                           no, GTK_RESPONSE_NO,
                           yes, GTK_RESPONSE_YES, NULL);
    response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy (dialog);
    if (response == GTK_RESPONSE_NO)
    {
        return FALSE;
    }
    return TRUE;
}