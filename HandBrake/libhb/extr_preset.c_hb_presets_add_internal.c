#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_value_t ;
struct TYPE_4__ {scalar_t__ depth; } ;
typedef  TYPE_1__ hb_preset_index_t ;

/* Variables and functions */
 scalar_t__ HB_VALUE_TYPE_ARRAY ; 
 scalar_t__ HB_VALUE_TYPE_DICT ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * hb_presets ; 
 int /*<<< orphan*/  hb_presets_clear_default () ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_free (int /*<<< orphan*/ **) ; 
 scalar_t__ hb_value_type (int /*<<< orphan*/ *) ; 
 TYPE_1__* lookup_default_index (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hb_presets_add_internal(hb_value_t *preset)
{
    hb_preset_index_t *path;
    int                added = 0;

    if (preset == NULL)
        return -1;

    path = lookup_default_index(preset);
    if (path != NULL && path->depth != 0)
    {
        // There is a "Default" preset in the preset(s) being added.
        // Clear any existing default preset.
        hb_presets_clear_default();
    }
    free(path);

    int index = hb_value_array_len(hb_presets);
    if (hb_value_type(preset) == HB_VALUE_TYPE_DICT)
    {
        // A standalone preset or folder of presets. Add to preset array.
        hb_value_array_append(hb_presets, hb_value_dup(preset));
        added++;
    }
    else if (hb_value_type(preset) == HB_VALUE_TYPE_ARRAY)
    {
        // An array of presets. Add each element.
        int count = hb_value_array_len(preset);
        int ii;
        for (ii = 0; ii < count; ii++)
        {
            hb_value_t *value = hb_value_array_get(preset, ii);
            hb_value_array_append(hb_presets, hb_value_dup(value));
            added++;
        }
    }

    hb_value_free(&preset);
    if (added == 0)
    {
        return -1;
    }

    return index;
}