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
 int /*<<< orphan*/  audio_deps (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * audio_get_selected_settings (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ block_updates ; 
 int /*<<< orphan*/  ghb_audio_list_refresh_selected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_dict_remove (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_live_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_update_summary_info (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_value_free (int /*<<< orphan*/ **) ; 

void
audio_update_setting(
    GhbValue           *val,
    const char         *name,
    signal_user_data_t *ud)
{
    GhbValue *asettings;

    if (block_updates)
    {
        ghb_value_free(&val);
        return;
    }

    asettings = audio_get_selected_settings(ud, NULL);
    if (asettings != NULL)
    {
        if (val != NULL)
            ghb_dict_set(asettings, name, val);
        else
            ghb_dict_remove(asettings, name);
        audio_deps(ud, asettings, NULL);
        ghb_update_summary_info(ud);
        ghb_audio_list_refresh_selected(ud);
        ghb_live_reset(ud);
    }
    else
    {
        ghb_value_free(&val);
    }
}