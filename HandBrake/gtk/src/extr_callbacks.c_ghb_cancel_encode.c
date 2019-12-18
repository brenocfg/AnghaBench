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
struct TYPE_3__ {int /*<<< orphan*/  cancel_encode; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  char gchar ;
typedef  int /*<<< orphan*/  GtkWindow ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  scalar_t__ GtkResponseType ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_CANCEL_ALL ; 
 int /*<<< orphan*/  GHB_CANCEL_CURRENT ; 
 int /*<<< orphan*/  GHB_CANCEL_FINISH ; 
 int /*<<< orphan*/  GHB_CANCEL_NONE ; 
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GTK_BUTTONS_NONE ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_DIALOG_MODAL ; 
 int /*<<< orphan*/  GTK_MESSAGE_WARNING ; 
 int /*<<< orphan*/ * GTK_WINDOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  ghb_stop_queue () ; 
 int /*<<< orphan*/  gtk_dialog_add_buttons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ gtk_dialog_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_message_dialog_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 

void
ghb_cancel_encode(signal_user_data_t *ud, const gchar *extra_msg)
{
    GtkWindow *hb_window;
    GtkWidget *dialog;
    GtkResponseType response;

    if (extra_msg == NULL) extra_msg = "";
    // Toss up a warning dialog
    hb_window = GTK_WINDOW(GHB_WIDGET(ud->builder, "hb_window"));
    dialog = gtk_message_dialog_new(hb_window, GTK_DIALOG_MODAL,
                GTK_MESSAGE_WARNING, GTK_BUTTONS_NONE,
                _("%sYour movie will be lost if you don't continue encoding."),
                extra_msg);
    gtk_dialog_add_buttons( GTK_DIALOG(dialog),
                           _("Cancel Current and Stop"), 1,
                           _("Cancel Current, Start Next"), 2,
                           _("Finish Current, then Stop"), 3,
                           _("Continue Encoding"), 4,
                           NULL);
    response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy (dialog);
    switch ((int)response)
    {
        case 1:
            ghb_stop_queue();
            ud->cancel_encode = GHB_CANCEL_ALL;
            break;
        case 2:
            ghb_stop_queue();
            ud->cancel_encode = GHB_CANCEL_CURRENT;
            break;
        case 3:
            ud->cancel_encode = GHB_CANCEL_FINISH;
            break;
        case 4:
        default:
            ud->cancel_encode = GHB_CANCEL_NONE;
            break;
    }
}