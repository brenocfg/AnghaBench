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
struct TYPE_4__ {int depth; int* index; } ;
typedef  TYPE_1__ hb_preset_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/  hb_preset_template ; 
 int /*<<< orphan*/ * hb_presets_get_folder_children (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_array_insert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  presets_clean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int hb_preset_insert(const hb_preset_index_t *path, const hb_value_t *dict)
{
    hb_value_t *folder = NULL;

    if (dict == NULL || path == NULL || path->depth < 0)
        return -1;

    int index = path->index[path->depth - 1];
    hb_preset_index_t folder_path = *path;
    folder_path.depth--;
    folder = hb_presets_get_folder_children(&folder_path);
    if (folder)
    {
        hb_value_t *dup = hb_value_dup(dict);
        presets_clean(dup, hb_preset_template);
        if (hb_value_array_len(folder) <= index)
        {
            index = hb_value_array_len(folder);
            hb_value_array_append(folder, dup);
        }
        else
        {
            hb_value_array_insert(folder, index, dup);
        }
    }
    else
    {
        hb_error("hb_preset_insert: not found");
        return -1;
    }
    return index;
}