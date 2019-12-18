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
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  hb_presets_import (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * hb_value_array_init () ; 
 int /*<<< orphan*/ * hb_value_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  hb_value_incref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static hb_value_t * presets_unpackage(const hb_value_t *packaged_presets)
{
    // Do any legacy translations.
    hb_value_t * imported;
    hb_value_t * tmp = hb_value_dup(packaged_presets);
    hb_presets_import(tmp, &imported);
    hb_value_free(&tmp);
    if (imported == NULL)
    {
        // Invalid preset format, return an empty array
        return hb_value_array_init();
    }
    hb_value_t *presets = hb_dict_get(imported, "PresetList");
    hb_value_incref(presets);
    hb_value_free(&imported);
    return presets;
}