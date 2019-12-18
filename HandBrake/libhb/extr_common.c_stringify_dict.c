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
typedef  int /*<<< orphan*/  hb_value_t ;
typedef  int /*<<< orphan*/  hb_filter_object_t ;
typedef  int /*<<< orphan*/  hb_dict_t ;
typedef  int /*<<< orphan*/  hb_dict_iter_t ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_ARRAY ; 
 scalar_t__ HB_VALUE_TYPE_DICT ; 
 scalar_t__ HB_VALUE_TYPE_INT ; 
 scalar_t__ HB_VALUE_TYPE_NULL ; 
 char* append_string (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int hb_dict_elements (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  hb_dict_iter_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_dict_iter_next_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_filter_get (int) ; 
 char** hb_filter_get_keys (int) ; 
 char* hb_filter_settings_string (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_str_vfree (char**) ; 
 char* hb_strdup_printf (char*,int,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int hb_value_get_int (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char * stringify_dict(int filter_id, hb_dict_t * dict)
{
    char            * result = strdup("");
    const char      * key;
    char           ** keys = NULL;
    hb_value_t      * val;
    hb_dict_iter_t    iter;
    int               first = 1;

    if (hb_dict_elements(dict) == 0)
    {
        return result;
    }
    // Check for dict containing rational value
    if (hb_dict_elements(dict) == 2)
    {
        hb_value_t *num_val = hb_dict_get(dict, "Num");
        hb_value_t *den_val = hb_dict_get(dict, "Den");
        if (num_val != NULL && den_val != NULL &&
            hb_value_type(num_val) == HB_VALUE_TYPE_INT &&
            hb_value_type(den_val) == HB_VALUE_TYPE_INT)
        {
            int num = hb_value_get_int(num_val);
            int den = hb_value_get_int(den_val);
            char * str = hb_strdup_printf("%d/%d", num, den);
            result = append_string(result, str);
            free(str);
            return result;
        }
    }
    hb_filter_object_t * filter = hb_filter_get(filter_id);
    if (filter != NULL)
    {
        keys = hb_filter_get_keys(filter_id);
        if (keys != NULL && keys[0] == NULL)
        {
            hb_str_vfree(keys);
            keys = NULL;
        }
    }

    int done, ii = 0;
    iter = hb_dict_iter_init(dict);
    if (keys == NULL)
    {
        done = !hb_dict_iter_next_ex(dict, &iter, &key, NULL);
    }
    else
    {
        done = (key = keys[ii]) == NULL;
    }
    while (!done)
    {
        val = hb_dict_get(dict, key);
        if (val != NULL)
        {
            if (!first)
            {
                result = append_string(result, ":");
            }
            first = 0;
            result = append_string(result, key);
            int elements = 1;

            if (hb_value_type(val) == HB_VALUE_TYPE_NULL)
            {
                elements = 0;
            }
            else if (hb_value_type(val) == HB_VALUE_TYPE_DICT)
            {
                elements = hb_dict_elements(val);
            }
            else if (hb_value_type(val) == HB_VALUE_TYPE_ARRAY)
            {
                elements = hb_value_array_len(val);
            }
            if (elements != 0)
            {
                char * str = hb_filter_settings_string(filter_id, val);
                if (str != NULL)
                {
                    result = append_string(result, "=");
                    if (hb_value_type(val) == HB_VALUE_TYPE_DICT)
                    {
                        result = append_string(result, "'");
                        result = append_string(result, str);
                        result = append_string(result, "'");
                    }
                    else if (hb_value_type(val) == HB_VALUE_TYPE_ARRAY)
                    {
                        result = append_string(result, "[");
                        result = append_string(result, str);
                        result = append_string(result, "]");
                    }
                    else
                    {
                        result = append_string(result, str);
                    }
                    free(str);
                }
            }
        }
        ii++;
        if (keys == NULL)
        {
            done = !hb_dict_iter_next_ex(dict, &iter, &key, NULL);
        }
        else
        {
            done = (key = keys[ii]) == NULL;
        }
    }
    hb_str_vfree(keys);

    return result;
}