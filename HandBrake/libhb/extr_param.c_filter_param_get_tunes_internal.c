#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_filter_param_t ;
struct TYPE_2__ {int filter_id; int tune_count; int /*<<< orphan*/ * tunes; } ;

/* Variables and functions */
 int HB_FILTER_INVALID ; 
 TYPE_1__* param_map ; 

__attribute__((used)) static hb_filter_param_t*
filter_param_get_tunes_internal(int filter_id, int *count)
{
    int ii;

    if (count != NULL)
    {
        *count = 0;
    }
    for (ii = 0; param_map[ii].filter_id != HB_FILTER_INVALID; ii++)
    {
        if (param_map[ii].filter_id == filter_id)
        {
            if (count != NULL)
            {
                *count = param_map[ii].tune_count;
            }
            return param_map[ii].tunes;
        }
    }
    return NULL;
}