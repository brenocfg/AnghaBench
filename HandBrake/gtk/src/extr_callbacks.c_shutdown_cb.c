#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_4__ {scalar_t__ timeout; int /*<<< orphan*/  dlg; int /*<<< orphan*/  action; int /*<<< orphan*/  msg; TYPE_3__* ud; } ;
typedef  TYPE_1__ countdown_t ;
struct TYPE_5__ {int /*<<< orphan*/  app; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  G_APPLICATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  g_application_quit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ghb_hb_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_shutdown_gsm () ; 
 int /*<<< orphan*/  gtk_message_dialog_set_markup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prune_logs (TYPE_3__*) ; 

__attribute__((used)) static gboolean
shutdown_cb(countdown_t *cd)
{
    gchar *str;

    cd->timeout--;
    if (cd->timeout == 0)
    {
        ghb_hb_cleanup(FALSE);
        prune_logs(cd->ud);

        ghb_shutdown_gsm();
        g_application_quit(G_APPLICATION(cd->ud->app));
        return FALSE;
    }
    str = g_strdup_printf(_("%s\n\n%s in %d seconds ..."),
                            cd->msg, cd->action, cd->timeout);
    gtk_message_dialog_set_markup(cd->dlg, str);
    g_free(str);
    return TRUE;
}