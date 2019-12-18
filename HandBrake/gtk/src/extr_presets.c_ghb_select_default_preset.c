#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  signal_user_data_t ;
struct TYPE_7__ {scalar_t__ depth; } ;
typedef  TYPE_1__ hb_preset_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_PRESET_TYPE_ALL ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 TYPE_1__* hb_preset_index_init (int*,int) ; 
 TYPE_1__* hb_preset_search_index (char*,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* hb_presets_get_default_index () ; 
 int /*<<< orphan*/  select_preset2 (int /*<<< orphan*/ *,TYPE_1__*) ; 

void
ghb_select_default_preset(signal_user_data_t *ud)
{
    hb_preset_index_t *path;

    path = hb_presets_get_default_index();
    if (path == NULL || path->depth == 0)
    {
        // No default set, find original "default" preset
        g_free(path);
        path = hb_preset_search_index("Fast 1080p30", 1, HB_PRESET_TYPE_ALL);
    }
    if (path == NULL || path->depth == 0)
    {
        int index[2] = {0, 0};

        // Could not find original default, try first available preset
        g_free(path);
        path = hb_preset_index_init(index, 2);
    }
    if (path != NULL)
    {
        select_preset2(ud, path);
        g_free(path);
    }
}