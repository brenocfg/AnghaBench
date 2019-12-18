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

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_ARRAY ; 
 scalar_t__ HB_VALUE_TYPE_DICT ; 
 scalar_t__ HB_VALUE_TYPE_NULL ; 
 char* hb_value_get_string_xform (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 char* strdup (char*) ; 
 char* stringify_array (int,int /*<<< orphan*/ *) ; 
 char* stringify_dict (int,int /*<<< orphan*/ *) ; 

char * hb_filter_settings_string(int filter_id, hb_value_t * value)
{
    if (value == NULL || hb_value_type(value) == HB_VALUE_TYPE_NULL)
    {
        return strdup("");
    }
    if (hb_value_type(value) == HB_VALUE_TYPE_DICT)
    {
        return stringify_dict(filter_id, value);
    }
    if (hb_value_type(value) == HB_VALUE_TYPE_ARRAY)
    {
        return stringify_array(filter_id, value);
    }
    return hb_value_get_string_xform(value);
}