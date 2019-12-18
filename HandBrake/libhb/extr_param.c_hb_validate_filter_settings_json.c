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
 int hb_validate_filter_settings (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_value_json (char const*) ; 

int hb_validate_filter_settings_json(int filter_id, const char * json)
{
    hb_value_t * value  = hb_value_json(json);
    int          result = hb_validate_filter_settings(filter_id, value);
    hb_value_free(&value);

    return result;
}