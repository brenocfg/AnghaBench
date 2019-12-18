#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_value_t ;
struct TYPE_3__ {int depth; int* index; } ;
typedef  TYPE_1__ hb_preset_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * hb_dict_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * hb_presets ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int hb_value_get_bool (int /*<<< orphan*/ *) ; 

hb_value_t *
hb_presets_get_folder_children(const hb_preset_index_t *path)
{
    int ii, count, folder;
    hb_value_t *dict;

    if (path == NULL)
        return hb_presets;

    hb_value_t *presets = hb_presets;
    for (ii = 0; ii < path->depth; ii++)
    {
        count = hb_value_array_len(presets);
        if (path->index[ii] >= count) return NULL;
        dict = hb_value_array_get(presets, path->index[ii]);
        folder = hb_value_get_bool(hb_dict_get(dict, "Folder"));
        if (!folder)
            break;
        presets = hb_dict_get(dict, "ChildrenArray");
    }
    if (ii < path->depth)
        return NULL;
    return presets;
}