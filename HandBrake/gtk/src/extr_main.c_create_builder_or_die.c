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
typedef  scalar_t__ guint ;
typedef  int /*<<< orphan*/  gsize ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_3__ {int /*<<< orphan*/  message; } ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GtkBuilder ;
typedef  int /*<<< orphan*/  GResource ;
typedef  TYPE_1__ GError ;
typedef  int /*<<< orphan*/  GBytes ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  GTK_BUTTONS_CLOSE ; 
 int /*<<< orphan*/  GTK_DIALOG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_DIALOG_MODAL ; 
 int /*<<< orphan*/  GTK_MESSAGE_ERROR ; 
 int /*<<< orphan*/ * N_ (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_bytes_get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 int /*<<< orphan*/ * g_resource_lookup_data (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gettext (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * ghb_ui_get_resource () ; 
 scalar_t__ gtk_builder_add_from_string (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,TYPE_1__**) ; 
 int /*<<< orphan*/ * gtk_builder_new () ; 
 int /*<<< orphan*/  gtk_dialog_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_message_dialog_new_with_markup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ *) ; 

GtkBuilder*
create_builder_or_die(const gchar * name)
{
    guint res = 0;
    GError *error = NULL;
    const gchar *ghb_ui;
    gsize data_size;

    GResource *ui_res = ghb_ui_get_resource();
    GBytes *gbytes = g_resource_lookup_data(ui_res,
                                            "/fr/handbrake/ghb/ui/ghb.ui",
                                            0, NULL);
    ghb_ui = g_bytes_get_data(gbytes, &data_size);

    const gchar *markup =
        N_("<b><big>Unable to create %s.</big></b>\n"
        "\n"
        "Internal error. Could not parse UI description.\n"
        "%s");
    g_debug("create_builder_or_die()\n");
    GtkBuilder *xml = gtk_builder_new();
    if (xml != NULL)
        res = gtk_builder_add_from_string(xml, ghb_ui, -1, &error);
    if (!xml || !res)
    {
        GtkWidget *dialog = gtk_message_dialog_new_with_markup(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_ERROR,
            GTK_BUTTONS_CLOSE,
            gettext(markup),
            name, error->message);
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        exit(EXIT_FAILURE);
    }
    return xml;
}