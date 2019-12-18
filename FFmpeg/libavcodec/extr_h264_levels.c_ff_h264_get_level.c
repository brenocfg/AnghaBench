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
struct TYPE_5__ {int level_idc; int constraint_set3_flag; } ;
typedef  TYPE_1__ H264LevelDescriptor ;

/* Variables and functions */
 int FF_ARRAY_ELEMS (TYPE_1__ const*) ; 
 TYPE_1__ const* h264_levels ; 

const H264LevelDescriptor *ff_h264_get_level(int level_idc,
                                             int constraint_set3_flag)
{
    int i;
    for (i = 0; i < FF_ARRAY_ELEMS(h264_levels); i++) {
        if (h264_levels[i].level_idc            == level_idc &&
            h264_levels[i].constraint_set3_flag == constraint_set3_flag)
            return &h264_levels[i];
    }
    return NULL;
}