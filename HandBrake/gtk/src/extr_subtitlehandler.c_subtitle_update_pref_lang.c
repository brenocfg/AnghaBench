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
struct TYPE_5__ {int /*<<< orphan*/  builder; int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_6__ {char* iso639_2; char* native_name; char* eng_name; } ;
typedef  TYPE_2__ iso639_lang_t ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkLabel ;
typedef  int /*<<< orphan*/  GtkButton ;

/* Variables and functions */
 int /*<<< orphan*/  GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * GTK_BUTTON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GTK_LABEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTK_WIDGET (int /*<<< orphan*/ *) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_strdup_printf (char*,...) ; 
 int /*<<< orphan*/  ghb_dict_set_string (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  gtk_button_set_label (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_label_set_text (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ ,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static void
subtitle_update_pref_lang(signal_user_data_t *ud, const iso639_lang_t *lang)
{
    GtkLabel *label;
    GtkButton *button;
    gchar *str;
    const char * name = _("None");
    const char * code = "und";

    label = GTK_LABEL(GHB_WIDGET(ud->builder, "subtitle_preferred_language"));
    if (lang != NULL)
    {
        code = lang->iso639_2;
        if (strncmp(code, "und", 4))
        {
            name = lang->native_name && lang->native_name[0] ?
                                lang->native_name : lang->eng_name;
        }
    }

    str = g_strdup_printf(_("Preferred Language: %s"), name);
    gtk_label_set_text(label, str);
    g_free(str);

    ghb_dict_set_string(ud->settings, "PreferredLanguage", code);

    // If there is no preferred language, disable options that require
    // a preferred language to be set.
    gboolean sensitive = !(lang == NULL || !strncmp(code, "und", 4));
    button = GTK_BUTTON(GHB_WIDGET(ud->builder,
                                  "SubtitleAddForeignAudioSubtitle"));
    if (sensitive)
    {
        str = g_strdup_printf(
            _("Add %s subtitle track if default audio is not %s"), name, name);
    }
    else
    {
        str = g_strdup_printf(
            _("Add subtitle track if default audio is not your preferred language"));
    }
    gtk_button_set_label(button, str);
    g_free(str);

    gtk_widget_set_sensitive(GTK_WIDGET(button), sensitive);
    button = GTK_BUTTON(GHB_WIDGET(ud->builder,
                                  "SubtitleAddForeignAudioSearch"));
    gtk_widget_set_sensitive(GTK_WIDGET(button), sensitive);
}