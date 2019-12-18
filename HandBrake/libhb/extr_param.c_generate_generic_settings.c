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
typedef  int /*<<< orphan*/  hb_value_t ;
struct TYPE_6__ {char const* settings; } ;
typedef  TYPE_1__ hb_filter_param_t ;

/* Variables and functions */
 TYPE_1__* filter_param_get_entry (TYPE_1__*,char const*,int) ; 
 TYPE_1__* filter_param_get_presets_internal (int,int*) ; 
 TYPE_1__* filter_param_get_tunes_internal (int,int*) ; 
 int /*<<< orphan*/  hb_dict_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_parse_filter_settings (char const*) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char*) ; 

__attribute__((used)) static hb_value_t *
generate_generic_settings(int filter_id, const char * preset,
                          const char * tune, const char * custom)
{
    if ((preset == NULL || !strcasecmp(preset, "custom")))
    {
        return hb_parse_filter_settings(custom);
    }

    int count;
    hb_filter_param_t *table;
    hb_filter_param_t *entry;

    hb_value_t * settings = NULL, * tune_settings = NULL;

    table = filter_param_get_presets_internal(filter_id, &count);
    entry = filter_param_get_entry(table, preset, count);
    if (entry != NULL && entry->settings != NULL)
    {
        settings = hb_parse_filter_settings(entry->settings);
        if (settings == NULL)
        {
            return NULL;
        }

        table = filter_param_get_tunes_internal(filter_id, &count);
        entry = filter_param_get_entry(table, tune, count);
        if (entry != NULL && entry->settings != NULL)
        {
            tune_settings = hb_parse_filter_settings(entry->settings);
            if (tune_settings == NULL)
            {
                hb_value_free(&settings);
                return NULL;
            }
            hb_dict_merge(settings, tune_settings);
            hb_value_free(&tune_settings);
        }
    }

    return settings;
}