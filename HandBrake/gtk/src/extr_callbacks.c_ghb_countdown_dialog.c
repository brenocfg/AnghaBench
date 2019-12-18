#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  guint ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_6__ {int /*<<< orphan*/  dlg; TYPE_1__* ud; int /*<<< orphan*/  timeout; int /*<<< orphan*/  const* action; int /*<<< orphan*/  const* msg; } ;
typedef  TYPE_2__ countdown_t ;
typedef  int /*<<< orphan*/  GtkWindow ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  scalar_t__ GtkResponseType ;
typedef  int /*<<< orphan*/  GtkMessageType ;
typedef  int /*<<< orphan*/  GSourceFunc ;
typedef  int /*<<< orphan*/  GSource ;
typedef  int /*<<< orphan*/  GMainContext ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_BUTTONS_NONE ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_DIALOG_MODAL ; 
 int /*<<< orphan*/  GTK_MESSAGE_DIALOG (int /*<<< orphan*/ *) ; 
 scalar_t__ GTK_RESPONSE_CANCEL ; 
 int /*<<< orphan*/ * GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * g_main_context_default () ; 
 int /*<<< orphan*/ * g_main_context_find_source_by_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_source_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_timeout_add (int,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  gtk_dialog_add_buttons (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_dialog_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_message_dialog_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 

void
ghb_countdown_dialog(
    GtkMessageType type,
    const gchar *message,
    const gchar *action,
    const gchar *cancel,
    GSourceFunc action_func,
    signal_user_data_t *ud,
    gint timeout)
{
    GtkWindow *hb_window;
    GtkWidget *dialog;
    GtkResponseType response;
    guint timeout_id;
    countdown_t cd;

    cd.msg = message;
    cd.action = action;
    cd.timeout = timeout;
    cd.ud = ud;

    // Toss up a warning dialog
    hb_window = GTK_WINDOW(GHB_WIDGET(ud->builder, "hb_window"));
    dialog = gtk_message_dialog_new(hb_window, GTK_DIALOG_MODAL,
                            type, GTK_BUTTONS_NONE,
                            _("%s\n\n%s in %d seconds ..."),
                            message, action, timeout);
    gtk_dialog_add_buttons( GTK_DIALOG(dialog),
                           cancel, GTK_RESPONSE_CANCEL,
                           NULL);

    cd.dlg = GTK_MESSAGE_DIALOG(dialog);
    timeout_id = g_timeout_add(1000, action_func, &cd);
    response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy (dialog);
    if (response == GTK_RESPONSE_CANCEL)
    {
        GMainContext *mc;
        GSource *source;

        mc = g_main_context_default();
        source = g_main_context_find_source_by_id(mc, timeout_id);
        if (source != NULL)
            g_source_destroy(source);
    }
}