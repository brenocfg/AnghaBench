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
struct TYPE_3__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ hb_container_t ;
typedef  scalar_t__ gint ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GhbValue ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  g_warning (char*) ; 
 scalar_t__ get_sub_source (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ghb_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_array_len (int /*<<< orphan*/ *) ; 
 scalar_t__ ghb_dict_get_bool (int /*<<< orphan*/ *,char*) ; 
 char* ghb_dict_get_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ghb_dict_set_bool (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/ * ghb_get_job_subtitle_list (int /*<<< orphan*/ *) ; 
 TYPE_1__* ghb_lookup_container_by_name (char const*) ; 
 int /*<<< orphan*/  hb_subtitle_can_burn (scalar_t__) ; 
 int /*<<< orphan*/  hb_subtitle_can_force (scalar_t__) ; 
 int /*<<< orphan*/  hb_subtitle_can_pass (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  subtitle_exclusive_burn_settings (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  subtitle_exclusive_default_settings (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
subtitle_add_to_settings(GhbValue *settings, GhbValue *subsettings)
{
    // Add the current subtitle settings to the list.
    GhbValue *subtitle_list;
    gint count;
    gboolean burn, forced, def;
    gint source;

    subtitle_list = ghb_get_job_subtitle_list(settings);
    if (subtitle_list == NULL)
    {
        g_warning("No subtitle list!");
        return;
    }

    // Validate some settings
    const char *mux_id;
    const hb_container_t *mux;

    mux_id = ghb_dict_get_string(settings, "FileFormat");
    mux = ghb_lookup_container_by_name(mux_id);

    source = get_sub_source(settings, subsettings);
    burn = ghb_dict_get_bool(subsettings, "Burn");
    if (burn && !hb_subtitle_can_burn(source))
    {
        burn = FALSE;
        ghb_dict_set_bool(subsettings, "Burn", burn);
    }
    if (!burn && !hb_subtitle_can_pass(source, mux->format))
    {
        burn = TRUE;
        ghb_dict_set_bool(subsettings, "Burn", burn);
        ghb_dict_set_bool(subsettings, "Default", FALSE);
    }
    def = ghb_dict_get_bool(subsettings, "Default");
    forced = ghb_dict_get_bool(subsettings, "Forced");
    if (forced && !hb_subtitle_can_force(source))
    {
        forced = FALSE;
        ghb_dict_set_bool(subsettings, "Forced", forced);
    }

    ghb_array_append(subtitle_list, subsettings);

    // Check consistency of exclusive flags
    count = ghb_array_len(subtitle_list);
    if (burn)
        subtitle_exclusive_burn_settings(settings, count-1);
    if (def)
        subtitle_exclusive_default_settings(settings, count-1);
}