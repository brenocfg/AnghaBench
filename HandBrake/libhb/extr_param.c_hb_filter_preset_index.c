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
struct TYPE_5__ {int index; } ;
typedef  TYPE_1__ hb_filter_param_t ;

/* Variables and functions */
 TYPE_1__* filter_param_get_entry (TYPE_1__*,char const*,int) ; 
 TYPE_1__* filter_param_get_presets_internal (int,int*) ; 

int
hb_filter_preset_index(int filter_id, const char *preset)
{
    if (preset == NULL)
        return -1;

    int preset_count;
    hb_filter_param_t *preset_table;
    hb_filter_param_t *preset_entry;

    preset_table = filter_param_get_presets_internal(filter_id, &preset_count);
    preset_entry = filter_param_get_entry(preset_table, preset, preset_count);
    if (preset_entry == NULL)
        return -1;
    return preset_entry->index;
}