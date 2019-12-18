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
struct TYPE_3__ {int index; char const* short_name; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ hb_filter_param_t ;

/* Variables and functions */
 TYPE_1__* hb_filter_param_get_presets (int) ; 

__attribute__((used)) static const char* import_indexed_filter(int filter_id, int index)
{
    hb_filter_param_t *filter_presets;
    filter_presets = hb_filter_param_get_presets(filter_id);

    int ii;
    for (ii = 0; filter_presets[ii].name != NULL; ii++)
    {
        if (filter_presets[ii].index == index)
            break;
    }
    return filter_presets[ii].short_name;
}