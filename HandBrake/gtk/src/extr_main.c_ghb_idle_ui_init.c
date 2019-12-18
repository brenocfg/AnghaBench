#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  globals; int /*<<< orphan*/  prefs; } ;
typedef  TYPE_1__ signal_user_data_t ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;
typedef  int /*<<< orphan*/  GSourceFunc ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HB_PRESET_TYPE_ALL ; 
 int /*<<< orphan*/ * arg_preset ; 
 int /*<<< orphan*/ * dvd_device ; 
 int /*<<< orphan*/  g_idle_add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_check_all_depencencies (TYPE_1__*) ; 
 int /*<<< orphan*/ * ghb_dict_get_value (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ghb_dict_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_dict_set_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_idle_scan ; 
 int /*<<< orphan*/  ghb_select_default_preset (TYPE_1__*) ; 
 int /*<<< orphan*/  ghb_select_preset (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_settings_to_ui (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghb_value_dup (int /*<<< orphan*/ *) ; 

gboolean
ghb_idle_ui_init(signal_user_data_t *ud)
{
    ghb_settings_to_ui(ud, ud->globals);
    ghb_settings_to_ui(ud, ud->prefs);
    // Note that ghb_settings_to_ui(ud->settings) happens when initial
    // empty title is initialized.

    // Init settings that are dependent on command line args
    if (dvd_device != NULL)
    {
        // Source overridden from command line option
        ghb_dict_set_string(ud->globals, "scan_source", dvd_device);
        g_idle_add((GSourceFunc)ghb_idle_scan, ud);
    }
    else
    {
        GhbValue *gval = ghb_dict_get_value(ud->prefs, "default_source");
        ghb_dict_set(ud->globals, "scan_source", ghb_value_dup(gval));
    }

    if (arg_preset != NULL)
    {
        ghb_select_preset(ud, arg_preset, HB_PRESET_TYPE_ALL);
    }
    else
    {
        ghb_select_default_preset(ud);
    }

    // Grey out widgets that are dependent on a disabled feature
    ghb_check_all_depencencies(ud);

    return FALSE;
}