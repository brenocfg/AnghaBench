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
struct TYPE_6__ {int /*<<< orphan*/  settings; int /*<<< orphan*/  builder; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_7__ {int /*<<< orphan*/  list_subtitle; } ;
typedef  TYPE_2__ hb_title_t ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/ * GHB_WIDGET (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  clear_subtitle_list_settings (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_subtitle_list_ui (int /*<<< orphan*/ ) ; 
 int ghb_dict_get_int (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_dict_remove (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ghb_get_job_settings (int /*<<< orphan*/ ) ; 
 TYPE_2__* ghb_lookup_title (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_scan_handle () ; 
 int /*<<< orphan*/  gtk_widget_set_sensitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int hb_list_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_preset_job_add_subtitles (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subtitle_refresh_list_ui (TYPE_1__*) ; 

void
ghb_set_pref_subtitle(signal_user_data_t *ud)
{
    int               sub_count, title_id;
    GtkWidget        *widget;
    const hb_title_t *title;

    title_id = ghb_dict_get_int(ud->settings, "title");
    title    = ghb_lookup_title(title_id, NULL);

    clear_subtitle_list_ui(ud->builder);
    if (title == NULL)
    {
        // Clear the subtitle list
        clear_subtitle_list_settings(ud->settings);
        return;
    }
    sub_count = hb_list_count(title->list_subtitle);
    if (sub_count == 0)
    {
        // No source subtitles
        widget = GHB_WIDGET(ud->builder, "SubtitleSrtEnable");
        gtk_widget_set_sensitive(widget, TRUE);
    }
    else
    {
        widget = GHB_WIDGET(ud->builder, "SubtitleImportDisable");
        gtk_widget_set_sensitive(widget, TRUE);
    }
    GhbValue *job = ghb_get_job_settings(ud->settings);
    ghb_dict_remove(job, "Subtitle");
    hb_preset_job_add_subtitles(ghb_scan_handle(), title_id, ud->settings, job);
    subtitle_refresh_list_ui(ud);
}