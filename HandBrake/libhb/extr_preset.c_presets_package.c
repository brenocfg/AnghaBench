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
typedef  int /*<<< orphan*/  hb_dict_t ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_DICT ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/ * hb_dict_init () ; 
 int /*<<< orphan*/  hb_dict_set (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_preset_template ; 
 int /*<<< orphan*/  hb_preset_version_major ; 
 int /*<<< orphan*/  hb_preset_version_micro ; 
 int /*<<< orphan*/  hb_preset_version_minor ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_array_init () ; 
 int /*<<< orphan*/ * hb_value_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * hb_value_int (int /*<<< orphan*/ ) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  presets_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static hb_value_t * presets_package(const hb_value_t *presets)
{
    hb_dict_t *packaged_presets;
    if (hb_value_type(presets) != HB_VALUE_TYPE_DICT ||
        hb_dict_get(presets, "VersionMajor") == NULL)
    {
        // Preset is not packaged
        packaged_presets = hb_dict_init();
        hb_dict_set(packaged_presets, "VersionMajor",
                    hb_value_int(hb_preset_version_major));
        hb_dict_set(packaged_presets, "VersionMinor",
                    hb_value_int(hb_preset_version_minor));
        hb_dict_set(packaged_presets, "VersionMicro",
                    hb_value_int(hb_preset_version_micro));

        // TODO: What else do we want in the preset containers header?
        hb_dict_t *tmp = hb_value_dup(presets);
        if (hb_value_type(presets) == HB_VALUE_TYPE_DICT)
        {
            hb_value_array_t *array = hb_value_array_init();
            hb_value_array_append(array, tmp);
            tmp = array;
        }
        presets_clean(tmp, hb_preset_template);
        hb_dict_set(packaged_presets, "PresetList", tmp);
    }
    else
    {
        // Preset is already packaged
        hb_dict_t *tmp = hb_value_dup(presets);
        presets_clean(tmp, hb_preset_template);
        packaged_presets = tmp;
    }
    return packaged_presets;
}