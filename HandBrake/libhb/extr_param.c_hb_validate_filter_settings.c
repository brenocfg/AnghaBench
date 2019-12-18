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
typedef  int /*<<< orphan*/  hb_value_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * settings_template; } ;
typedef  TYPE_1__ hb_filter_object_t ;
typedef  int /*<<< orphan*/  const hb_dict_t ;
typedef  scalar_t__ hb_dict_iter_t ;

/* Variables and functions */
 scalar_t__ HB_DICT_ITER_DONE ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/  const*,char const*) ; 
 scalar_t__ hb_dict_iter_init (int /*<<< orphan*/  const*) ; 
 char* hb_dict_iter_key (scalar_t__) ; 
 scalar_t__ hb_dict_iter_next (int /*<<< orphan*/  const*,scalar_t__) ; 
 TYPE_1__* hb_filter_get (int) ; 
 int /*<<< orphan*/  hb_log (char*,...) ; 
 int /*<<< orphan*/  const* hb_parse_filter_settings (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_validate_param_string (char const*,char*) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/  const**) ; 
 char* hb_value_get_string (int /*<<< orphan*/ *) ; 
 char* hb_value_get_string_xform (int /*<<< orphan*/ *) ; 

int hb_validate_filter_settings(int filter_id, const hb_dict_t * settings)
{
    hb_filter_object_t * filter;
    hb_dict_t          * settings_template;
    hb_dict_iter_t       iter;

    if (settings == NULL)
        return 0;

    // Verify that all keys in settings are in the filter settings template
    filter = hb_filter_get(filter_id);
    if (filter == NULL)
    {
        hb_log("hb_validate_filter_settings: Unrecognized filter (%d).\n",
               filter_id);
        return 1;
    }
    if (filter->settings_template == NULL)
    {
        // filter has no template to verify settings against
        return 0;
    }
    settings_template = hb_parse_filter_settings(filter->settings_template);
    if (settings_template == NULL)
    {
        hb_log("hb_validate_filter_settings: invalid template!");
        return 0;
    }

    for (iter = hb_dict_iter_init(settings);
         iter != HB_DICT_ITER_DONE;
         iter = hb_dict_iter_next(settings, iter))
    {
        const char * key;
        hb_value_t * val;

        key = hb_dict_iter_key(iter);

        // Check if key found in settings is also found in the template
        val = hb_dict_get(settings_template, key);
        if (val == NULL)
        {
            // Key is missing from template, indicate invalid settings
            hb_log("Invalid filter key (%s) for filter %s",
                    key, filter->name);
            return 1;
        }

        // If a string value is found, and it is non-empty,
        // it is a regex pattern for allowed values.
        const char * regex_pattern = hb_value_get_string(val);
        if (regex_pattern != NULL && regex_pattern[0] != 0)
        {
            char * param;
            param = hb_value_get_string_xform(hb_dict_get(settings, key));
            if (hb_validate_param_string(regex_pattern, param) != 0)
            {
                hb_log("Invalid filter value (%s) for key %s filter %s",
                        param, key, filter->name);
                free(param);
                return 1;
            }
            free(param);
        }
    }
    hb_value_free(&settings_template);

    return 0;
}