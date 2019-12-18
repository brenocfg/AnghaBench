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
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_preset_version_major ; 
 int /*<<< orphan*/  hb_preset_version_micro ; 
 int /*<<< orphan*/  hb_preset_version_minor ; 
 int /*<<< orphan*/  hb_value_incref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_int (int /*<<< orphan*/ ) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * presets_package (int /*<<< orphan*/ *) ; 

hb_value_t * hb_presets_update_version(hb_value_t *presets)
{
    if (hb_value_type(presets) == HB_VALUE_TYPE_DICT)
    {
        // Is this a single preset or a packaged collection of presets?
        hb_value_t *val = hb_dict_get(presets, "PresetName");
        if (val == NULL)
        {
            val = hb_dict_get(presets, "VersionMajor");
            if (val != NULL)
            {
                hb_dict_set(presets, "VersionMajor",
                            hb_value_int(hb_preset_version_major));
                hb_dict_set(presets, "VersionMinor",
                            hb_value_int(hb_preset_version_minor));
                hb_dict_set(presets, "VersionMicro",
                            hb_value_int(hb_preset_version_micro));
                hb_value_incref(presets);
                return presets;
            }
            // Unrecognizable preset file format
            return NULL;
        }
    }
    return presets_package(presets);
}