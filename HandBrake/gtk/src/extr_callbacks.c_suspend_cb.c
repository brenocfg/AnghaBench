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
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {scalar_t__ timeout; int /*<<< orphan*/  dlg; int /*<<< orphan*/  action; int /*<<< orphan*/  msg; } ;
typedef  TYPE_1__ countdown_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ghb_suspend_gpm () ; 
 int /*<<< orphan*/  gtk_message_dialog_set_markup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
suspend_cb(countdown_t *cd)
{
    gchar *str;

    cd->timeout--;
    if (cd->timeout == 0)
    {
        gtk_widget_destroy (GTK_WIDGET(cd->dlg));
        ghb_suspend_gpm();
        return FALSE;
    }
    str = g_strdup_printf(_("%s\n\n%s in %d seconds ..."),
                            cd->msg, cd->action, cd->timeout);
    gtk_message_dialog_set_markup(cd->dlg, str);
    g_free(str);
    return TRUE;
}