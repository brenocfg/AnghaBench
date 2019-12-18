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
 int /*<<< orphan*/  hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int hb_presets_add_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_presets_clean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_presets_cli_default ; 
 int /*<<< orphan*/  hb_value_dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_value_json (int /*<<< orphan*/ ) ; 

int hb_presets_cli_default_init(void)
{
    hb_value_t * dict = hb_value_json(hb_builtin_presets_json);
    hb_presets_cli_default = hb_value_dup(hb_dict_get(dict, "PresetCLIDefault"));
    hb_presets_clean(hb_presets_cli_default);

    int result = hb_presets_add_internal(hb_presets_cli_default);
    hb_value_free(&dict);
    return result;
}