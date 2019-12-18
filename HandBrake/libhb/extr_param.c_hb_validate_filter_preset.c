#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ hb_filter_param_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 TYPE_1__* filter_param_get_entry (TYPE_1__*,char const*,int) ; 
 TYPE_1__* filter_param_get_presets_internal (int,int*) ; 
 TYPE_1__* filter_param_get_tunes_internal (int,int*) ; 
 int /*<<< orphan*/ * hb_parse_filter_settings (char const*) ; 
 int hb_validate_filter_settings (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

int
hb_validate_filter_preset(int filter_id, const char *preset, const char *tune,
                          const char *custom)
{
    if (preset == NULL)
        return 1;

    int preset_count, tune_count;
    hb_filter_param_t *preset_table, *tune_table;
    hb_filter_param_t *preset_entry, *tune_entry;

    preset_table = filter_param_get_presets_internal(filter_id, &preset_count);
    preset_entry = filter_param_get_entry(preset_table, preset, preset_count);
    if (preset_entry == NULL || preset_entry->name == NULL)
        return 1;
    if (!strcasecmp(preset, "custom") && custom != NULL)
    {
        hb_dict_t * settings = hb_parse_filter_settings(custom);
        if (settings == NULL)
        {
            return 1;
        }
        int result = hb_validate_filter_settings(filter_id, settings);
        hb_value_free(&settings);
        return result;
    }
    if (tune != NULL)
    {
        tune_table = filter_param_get_tunes_internal(filter_id, &tune_count);
        tune_entry = filter_param_get_entry(tune_table, tune, tune_count);
        if (tune_entry == NULL)
        {
            return 1;
        }
    }
    return 0;
}