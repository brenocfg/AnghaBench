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
typedef  int /*<<< orphan*/  hb_preset_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/  hb_preset_template ; 
 int /*<<< orphan*/ * hb_presets_get_folder_children (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  presets_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int hb_preset_append(const hb_preset_index_t *path, const hb_value_t *dict)
{
    hb_value_t *folder = NULL;

    if (dict == NULL)
        return -1;

    folder = hb_presets_get_folder_children(path);
    if (folder)
    {
        int index;
        hb_value_t *dup = hb_value_dup(dict);
        presets_clean(dup, hb_preset_template);
        index = hb_value_array_len(folder);
        hb_value_array_append(folder, dup);
        return index;
    }
    else
    {
        hb_error("hb_preset_append: not found");
        return -1;
    }
    return 0;
}