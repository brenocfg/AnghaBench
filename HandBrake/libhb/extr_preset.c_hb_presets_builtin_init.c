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
 int /*<<< orphan*/  hb_builtin_presets_json ; 
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 void* hb_preset_template ; 
 void* hb_preset_version_major ; 
 void* hb_preset_version_micro ; 
 void* hb_preset_version_minor ; 
 int /*<<< orphan*/  hb_presets ; 
 void* hb_presets_builtin ; 
 int /*<<< orphan*/  hb_presets_clean (void*) ; 
 int /*<<< orphan*/  hb_value_array_init () ; 
 void* hb_value_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 void* hb_value_get_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_json (int /*<<< orphan*/ ) ; 

void hb_presets_builtin_init(void)
{
    hb_value_t * dict = hb_value_json(hb_builtin_presets_json);
    hb_value_t * template = hb_dict_get(dict, "PresetTemplate");
    hb_preset_version_major = hb_value_get_int(
                              hb_dict_get(template, "VersionMajor"));
    hb_preset_version_minor = hb_value_get_int(
                              hb_dict_get(template, "VersionMinor"));
    hb_preset_version_micro = hb_value_get_int(
                              hb_dict_get(template, "VersionMicro"));
    hb_preset_template = hb_value_dup(hb_dict_get(template, "Preset"));

    hb_presets_builtin = hb_value_dup(hb_dict_get(dict, "PresetBuiltin"));
    hb_presets_clean(hb_presets_builtin);

    hb_presets = hb_value_array_init();
    hb_value_free(&dict);
}