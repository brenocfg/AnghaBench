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
typedef  int /*<<< orphan*/  signal_user_data_t ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 int /*<<< orphan*/  ghb_dict_remove (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_live_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_update_summary_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * subtitle_get_selected_settings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  subtitle_list_refresh_selected (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GhbValue*
subtitle_update_setting(GhbValue *val, const char *name, signal_user_data_t *ud)
{
    GhbValue *subsettings;

    subsettings = subtitle_get_selected_settings(ud, NULL);
    if (subsettings != NULL)
    {
        if (val != NULL)
            ghb_dict_set(subsettings, name, val);
        else
            ghb_dict_remove(subsettings, name);
        subtitle_list_refresh_selected(ud, subsettings);
        ghb_update_summary_info(ud);
        ghb_live_reset(ud);
    }
    else
    {
        ghb_value_free(&val);
    }
    return subsettings;
}