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
 int /*<<< orphan*/ * hb_parse_filter_settings (char const*) ; 
 int hb_validate_filter_settings (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 

int hb_validate_filter_string(int filter_id, const char * filter_str)
{
    hb_dict_t * settings = hb_parse_filter_settings(filter_str);
    if (settings == NULL)
    {
        return 1;
    }
    int result = hb_validate_filter_settings(filter_id, settings);
    hb_value_free(&settings);
    return result;
}