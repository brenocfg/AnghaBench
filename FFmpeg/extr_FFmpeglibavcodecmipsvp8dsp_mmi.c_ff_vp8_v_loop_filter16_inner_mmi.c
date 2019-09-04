#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int hev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vp8_filter_common_is4tap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vp8_filter_common_isnot4tap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ vp8_normal_limit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

void ff_vp8_v_loop_filter16_inner_mmi(uint8_t *dst, ptrdiff_t stride,
        int flim_E, int flim_I, int hev_thresh)
{
    int i;

    for (i = 0; i < 16; i++)
        if (vp8_normal_limit(dst + i * 1, stride, flim_E, flim_I)) {
            int hv = hev(dst + i * 1, stride, hev_thresh);
            if (hv)
                vp8_filter_common_is4tap(dst + i * 1, stride);
            else
                vp8_filter_common_isnot4tap(dst + i * 1, stride);
        }
}