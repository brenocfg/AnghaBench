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
 scalar_t__ HB_VALUE_TYPE_DICT ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int hb_value_get_int (int /*<<< orphan*/ *) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 

int hb_presets_version(hb_value_t *preset, int *major, int *minor, int *micro)
{
    *major = 0; *minor = 0; *micro = 0;
    if (hb_value_type(preset) == HB_VALUE_TYPE_DICT)
    {
        // Is this a single preset or a packaged collection of presets?
        hb_value_t *val = hb_dict_get(preset, "PresetName");
        if (val == NULL)
        {
            val = hb_dict_get(preset, "VersionMajor");
            if (val != NULL)
            {
                *major = hb_value_get_int(hb_dict_get(preset, "VersionMajor"));
                *minor = hb_value_get_int(hb_dict_get(preset, "VersionMinor"));
                *micro = hb_value_get_int(hb_dict_get(preset, "VersionMicro"));
                return 0;
            }
        }
    }
    return -1;
}