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
struct TYPE_3__ {int*** mv_cache; } ;
typedef  TYPE_1__ H264SliceContext ;

/* Variables and functions */
 int FFMAX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  av_assert2 (int) ; 
 size_t* scan8 ; 

__attribute__((used)) static inline int get_lowest_part_list_y(H264SliceContext *sl,
                                         int n, int height, int y_offset, int list)
{
    int raw_my             = sl->mv_cache[list][scan8[n]][1];
    int filter_height_down = (raw_my & 3) ? 3 : 0;
    int full_my            = (raw_my >> 2) + y_offset;
    int bottom             = full_my + filter_height_down + height;

    av_assert2(height >= 0);

    return FFMAX(0, bottom);
}