#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  builder; int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_7__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ hb_container_t ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int IMPORTSRT ; 
 int IMPORTSSA ; 
 int TRUE ; 
 int get_sub_source (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_boolean_value (int) ; 
 int /*<<< orphan*/ * ghb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int ghb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_2__* ghb_lookup_container_by_name (char const*) ; 
 int /*<<< orphan*/ * ghb_string_value (char*) ; 
 int /*<<< orphan*/  ghb_ui_update (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_widget_set_visible (int /*<<< orphan*/ *,int) ; 
 scalar_t__ hb_subtitle_can_burn (int) ; 
 int hb_subtitle_can_force (int) ; 
 int hb_subtitle_can_pass (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
subtitle_update_dialog_widgets(signal_user_data_t *ud, GhbValue *subsettings)
{
    GtkWidget *widget;

    if (subsettings != NULL)
    {
        // Update widgets with subsettings
        GhbValue *val, *import;
        gboolean burn, force, def;
        int source;

        const char *mux_id;
        const hb_container_t *mux;

        mux_id = ghb_dict_get_string(ud->settings, "FileFormat");
        mux    = ghb_lookup_container_by_name(mux_id);

        import = ghb_dict_get(subsettings, "Import");
        source = get_sub_source(ud->settings, subsettings);

        val = ghb_dict_get_value(subsettings, "Name");
        if (val != NULL)
        {
            ghb_ui_update(ud, "SubtitleTrackName", val);
        }
        else
        {
            ghb_ui_update(ud, "SubtitleTrackName", ghb_string_value(""));
        }

        val    = ghb_dict_get(subsettings, "Track");
        if (val != NULL)
        {
            ghb_ui_update(ud, "SubtitleTrack", val);

            // Hide regular subtitle widgets
            widget = GHB_WIDGET(ud->builder, "subtitle_track_label");
            gtk_widget_set_visible(widget, import == NULL);
            widget = GHB_WIDGET(ud->builder, "SubtitleTrack");
            gtk_widget_set_visible(widget, import == NULL);

            // Show import subitle widgets
            widget = GHB_WIDGET(ud->builder, "subtitle_import_grid");
            gtk_widget_set_visible(widget, source == IMPORTSRT ||
                                           source == IMPORTSSA);
            widget = GHB_WIDGET(ud->builder, "srt_code_label");
            gtk_widget_set_visible(widget, source == IMPORTSRT);
            widget = GHB_WIDGET(ud->builder, "SrtCodeset");
            gtk_widget_set_visible(widget, source == IMPORTSRT);

            widget = GHB_WIDGET(ud->builder, "subtitle_import_switch_box");
            gtk_widget_set_visible(widget, TRUE);
        }
        else
        {
            // Hide widgets not needed for "Foreign audio search"
            widget = GHB_WIDGET(ud->builder, "subtitle_track_label");
            gtk_widget_set_visible(widget, FALSE);
            widget = GHB_WIDGET(ud->builder, "SubtitleTrack");
            gtk_widget_set_visible(widget, FALSE);

            widget = GHB_WIDGET(ud->builder, "subtitle_import_grid");
            gtk_widget_set_visible(widget, FALSE);

            widget = GHB_WIDGET(ud->builder, "subtitle_import_switch_box");
            gtk_widget_set_visible(widget, FALSE);
        }

        if (import != NULL)
        {
            if (source == IMPORTSSA)
            {
                ghb_ui_update(ud, "SubtitleSsaEnable", ghb_boolean_value(TRUE));
            }
            else
            {
                ghb_ui_update(ud, "SubtitleSrtEnable", ghb_boolean_value(TRUE));
            }
            val = ghb_dict_get(import, "Language");
            ghb_ui_update(ud, "ImportLanguage", val);
            val = ghb_dict_get(import, "Codeset");
            ghb_ui_update(ud, "SrtCodeset", val);
            val = ghb_dict_get(import, "Filename");
            ghb_ui_update(ud, "ImportFile", val);
            val = ghb_dict_get(subsettings, "Offset");
            ghb_ui_update(ud, "ImportOffset", val);
        }
        else
        {
            ghb_ui_update(ud, "SubtitleImportDisable", ghb_boolean_value(TRUE));
        }

        widget = GHB_WIDGET(ud->builder, "SubtitleBurned");
        gtk_widget_set_sensitive(widget, hb_subtitle_can_burn(source) &&
                                 hb_subtitle_can_pass(source, mux->format));

        widget = GHB_WIDGET(ud->builder, "SubtitleForced");
        gtk_widget_set_sensitive(widget, hb_subtitle_can_force(source));

        widget = GHB_WIDGET(ud->builder, "SubtitleDefaultTrack");
        gtk_widget_set_sensitive(widget,
                                 hb_subtitle_can_pass(source, mux->format));

        burn = ghb_dict_get_bool(subsettings, "Burn");
        force = ghb_dict_get_bool(subsettings, "Forced");
        def = ghb_dict_get_bool(subsettings, "Default");

        if (!hb_subtitle_can_burn(source))
        {
            burn = FALSE;
        }
        if (!hb_subtitle_can_force(source))
        {
            force = FALSE;
        }
        if (!hb_subtitle_can_pass(source, mux->format))
        {
            def = FALSE;
            burn = TRUE;
        }
        ghb_dict_set_bool(subsettings, "Burn", burn);
        ghb_dict_set_bool(subsettings, "Forced", force);
        ghb_dict_set_bool(subsettings, "Default", def);
        ghb_ui_update(ud, "SubtitleBurned", ghb_boolean_value(burn));
        ghb_ui_update(ud, "SubtitleForced", ghb_boolean_value(force));
        ghb_ui_update(ud, "SubtitleDefaultTrack", ghb_boolean_value(def));

    }
    else
    {
        // Hide SRT subitle widgets
        widget = GHB_WIDGET(ud->builder, "subtitle_import_grid");
        gtk_widget_set_visible(widget, FALSE);

        // Show regular subtitle widgets
        widget = GHB_WIDGET(ud->builder, "subtitle_track_label");
        gtk_widget_set_visible(widget, TRUE);
        widget = GHB_WIDGET(ud->builder, "SubtitleTrack");
        gtk_widget_set_visible(widget, TRUE);
    }
}