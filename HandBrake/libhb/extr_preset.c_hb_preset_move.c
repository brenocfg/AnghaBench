#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_value_t ;
struct TYPE_5__ {int depth; int* index; } ;
typedef  TYPE_1__ hb_preset_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/ * hb_presets_get_folder_children (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_value_array_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hb_value_array_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_value_array_insert (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_array_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hb_value_incref (int /*<<< orphan*/ *) ; 

int hb_preset_move(const hb_preset_index_t *src_path,
                   const hb_preset_index_t *dst_path)
{
    hb_value_t *src_folder = NULL;
    hb_value_t *dst_folder = NULL;

    hb_preset_index_t src_folder_path = *src_path;
    hb_preset_index_t dst_folder_path = *dst_path;
    src_folder_path.depth--;
    dst_folder_path.depth--;
    src_folder = hb_presets_get_folder_children(&src_folder_path);
    dst_folder = hb_presets_get_folder_children(&dst_folder_path);
    if (src_folder == NULL || dst_folder == NULL)
    {
        hb_error("hb_preset_move: not found");
        return -1;
    }

    hb_value_t *dict;
    int         src_index, dst_index;

    src_index = src_path->index[src_path->depth-1];
    dst_index = dst_path->index[dst_path->depth-1];
    dict      = hb_value_array_get(src_folder, src_index);
    hb_value_incref(dict);
    hb_value_array_remove(src_folder, src_index);

    // Be careful about indexes in the case that they are in the same folder
    if (src_folder == dst_folder && src_index < dst_index)
        dst_index--;
    if (hb_value_array_len(dst_folder) <= dst_index)
        hb_value_array_append(dst_folder, dict);
    else
        hb_value_array_insert(dst_folder, dst_index, dict);

    return 0;
}