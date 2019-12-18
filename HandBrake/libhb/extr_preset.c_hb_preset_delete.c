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
struct TYPE_4__ {int depth; int /*<<< orphan*/ * index; } ;
typedef  TYPE_1__ hb_preset_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  hb_error (char*) ; 
 int /*<<< orphan*/ * hb_presets_get_folder_children (TYPE_1__*) ; 
 int /*<<< orphan*/  hb_value_array_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hb_value_array_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
hb_preset_delete(const hb_preset_index_t *path)
{
    hb_value_t *folder = NULL;

    if (path == NULL)
        return -1;

    hb_preset_index_t folder_path = *path;
    folder_path.depth--;
    folder = hb_presets_get_folder_children(&folder_path);
    if (folder)
    {
        if (hb_value_array_len(folder) <= path->index[path->depth-1])
        {
            hb_error("hb_preset_delete: not found");
            return -1;
        }
        else
        {
            hb_value_array_remove(folder, path->index[path->depth-1]);
        }
    }
    else
    {
        hb_error("hb_preset_delete: not found");
        return -1;
    }
    return 0;
}