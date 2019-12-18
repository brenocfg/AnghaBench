#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  settings; } ;
typedef  TYPE_1__ signal_user_data_t ;
struct TYPE_8__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_2__ hb_container_t ;
typedef  scalar_t__ gint ;
typedef  int gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int FALSE ; 
 int get_sub_source (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ghb_array_get (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_array_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int ghb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * ghb_get_job_subtitle_list (int /*<<< orphan*/ ) ; 
 TYPE_2__* ghb_lookup_container_by_name (char const*) ; 
 int /*<<< orphan*/  hb_subtitle_can_pass (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * subtitle_get_selected_settings (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subtitle_update_dialog_widgets (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
ghb_subtitle_prune(signal_user_data_t *ud)
{
    GhbValue *subtitle_list;
    GhbValue *subsettings;
    gint ii;
    gboolean one_burned = FALSE;

    subtitle_list = ghb_get_job_subtitle_list(ud->settings);
    if (subtitle_list == NULL)
        return;

    const char *mux_id;
    const hb_container_t *mux;

    mux_id = ghb_dict_get_string(ud->settings, "FileFormat");
    mux = ghb_lookup_container_by_name(mux_id);

    for (ii = 0; ii < ghb_array_len(subtitle_list); )
    {
        gboolean burned;
        int source;

        subsettings = ghb_array_get(subtitle_list, ii);
        burned = ghb_dict_get_bool(subsettings, "Burn");
        source = get_sub_source(ud->settings, subsettings);
        burned = burned || !hb_subtitle_can_pass(source, mux->format);
        if (burned && one_burned)
        {
            ghb_array_remove(subtitle_list, ii);
            continue;
        }
        one_burned = one_burned || burned;
        ghb_dict_set_bool(subsettings, "Burn", burned);
        ii++;
    }
    subsettings = subtitle_get_selected_settings(ud, NULL);
    if (subsettings != NULL)
    {
        subtitle_update_dialog_widgets(ud, subsettings);
    }
}