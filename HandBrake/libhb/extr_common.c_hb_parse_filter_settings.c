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
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hb_dict_case_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_log (char*,char const*) ; 
 int /*<<< orphan*/  hb_str_vfree (char**) ; 
 char** hb_str_vsplit (char const*,char) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_value_string (char*) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 

hb_dict_t * hb_parse_filter_settings(const char * settings_str)
{
    hb_dict_t  * dict = hb_dict_init();
    char      ** settings_list = hb_str_vsplit(settings_str, ':');
    int          ii;

    for (ii = 0; settings_list[ii] != NULL; ii++)
    {
        char * key, * value;
        char ** settings_pair = hb_str_vsplit(settings_list[ii], '=');
        if (settings_pair[0] == NULL || settings_pair[1] == NULL)
        {
            // Parse error. Not key=value pair.
            hb_str_vfree(settings_list);
            hb_str_vfree(settings_pair);
            hb_value_free(&dict);
            hb_log("hb_parse_filter_settings: Error parsing (%s)",
                   settings_str);
            return NULL;
        }
        key   = settings_pair[0];
        value = settings_pair[1];

        int last = strlen(value) - 1;
        // Check if value was quoted dictionary and remove quotes
        // and parse the sub-dictionary.  This should only happen
        // for avfilter settings.
        if (last > 0 && value[0] == '\'' && value[last] == '\'')
        {
            char * str = strdup(value + 1);
            str[last - 1] = 0;
            hb_dict_t * sub_dict = hb_parse_filter_settings(str);
            free(str);
            if (sub_dict == NULL)
            {
                // Parse error. Not key=value pair.
                hb_str_vfree(settings_list);
                hb_str_vfree(settings_pair);
                hb_value_free(&dict);
                hb_log("hb_parse_filter_settings: Error parsing (%s)",
                       settings_str);
                return NULL;
            }
            hb_dict_case_set(dict, key, sub_dict);
        }
        // Check if value was quoted string and remove quotes
        else if (last > 0 && value[0] == '"' && value[last] == '"')
        {
            char * str = strdup(value + 1);
            str[last - 1] = 0;
            hb_dict_case_set(dict, key, hb_value_string(str));
            free(str);
        }
        else
        {
            hb_dict_case_set(dict, key, hb_value_string(value));
        }

        hb_str_vfree(settings_pair);
    }
    hb_str_vfree(settings_list);

    return dict;
}