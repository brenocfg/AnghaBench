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
typedef  int /*<<< orphan*/  hb_value_array_t ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_ARRAY ; 
 scalar_t__ HB_VALUE_TYPE_DICT ; 
 char* append_string (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* hb_filter_settings_string (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 char* strdup (char*) ; 

__attribute__((used)) static char * stringify_array(int filter_id, hb_value_array_t * array)
{
    char * result = strdup("");
    int    ii;
    int    len = hb_value_array_len(array);
    int    first = 1;

    if (hb_value_array_len(array) == 0)
    {
        return result;
    }
    for (ii = 0; ii < len; ii++)
    {
        hb_value_t * val = hb_value_array_get(array, ii);
        char       * str = hb_filter_settings_string(filter_id, val);
        if (str != NULL)
        {
            if (!first)
            {
                result = append_string(result, ",");
            }
            first = 0;
            if (hb_value_type(val) == HB_VALUE_TYPE_DICT)
            {
                result = append_string(result, str);
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

    return result;
}