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
struct TYPE_3__ {char* settings_template; } ;
typedef  TYPE_1__ hb_filter_object_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hb_dict_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* hb_filter_get (int) ; 
 char* hb_filter_settings_string (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_log (char*,int) ; 
 int /*<<< orphan*/  hb_str_vfree (char**) ; 
 char** hb_str_vsplit (char*,char) ; 
 char* hb_value_get_string_xform (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_string (char*) ; 

__attribute__((used)) static void import_custom_11_1_0(hb_value_t * preset, int filter_id,
                                 const char * key)
{
    char *str = hb_value_get_string_xform(hb_dict_get(preset, key));
    if (str == NULL)
    {
        return;
    }
    hb_filter_object_t * filter = hb_filter_get(filter_id);
    if (filter == NULL)
    {
        hb_log("import_custom_11_1_0: invalid filter id %d\n", filter_id);
        return;
    }
    if (filter->settings_template == NULL)
    {
        return;
    }
    char ** values = hb_str_vsplit(str, ':');
    char ** tmpl   = hb_str_vsplit(filter->settings_template, ':');
    int     ii;

    free(str);
    hb_dict_t * dict = hb_dict_init();
    for (ii = 0; values[ii] != NULL; ii++)
    {
        if (tmpl[ii] == NULL)
        {
            // Incomplete template?
            break;
        }
        char ** pair = hb_str_vsplit(tmpl[ii], '=');
        if (pair[0] != NULL)
        {
            hb_dict_set(dict, pair[0], hb_value_string(values[ii]));
        }
        hb_str_vfree(pair);
    }
    hb_str_vfree(tmpl);
    hb_str_vfree(values);

    char * result = hb_filter_settings_string(filter_id, dict);
    hb_dict_set(preset, key, hb_value_string(result));
    free(result);
}