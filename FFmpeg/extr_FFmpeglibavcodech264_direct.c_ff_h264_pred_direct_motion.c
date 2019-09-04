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
struct TYPE_5__ {scalar_t__ direct_spatial_mv_pred; } ;
typedef  TYPE_1__ H264SliceContext ;
typedef  int /*<<< orphan*/  H264Context ;

/* Variables and functions */
 int /*<<< orphan*/  pred_spatial_direct_motion (int /*<<< orphan*/  const* const,TYPE_1__*,int*) ; 
 int /*<<< orphan*/  pred_temp_direct_motion (int /*<<< orphan*/  const* const,TYPE_1__*,int*) ; 

void ff_h264_pred_direct_motion(const H264Context *const h, H264SliceContext *sl,
                                int *mb_type)
{
    if (sl->direct_spatial_mv_pred)
        pred_spatial_direct_motion(h, sl, mb_type);
    else
        pred_temp_direct_motion(h, sl, mb_type);
}