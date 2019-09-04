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
 int /*<<< orphan*/  vp8_v_loop_filter8_mmi (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 

void ff_vp8_v_loop_filter16_mmi(uint8_t *dst, ptrdiff_t stride, int flim_E,
        int flim_I, int hev_thresh)
{
    vp8_v_loop_filter8_mmi(dst, stride, flim_E, flim_I, hev_thresh);
    vp8_v_loop_filter8_mmi(dst + 8, stride, flim_E, flim_I, hev_thresh);
}