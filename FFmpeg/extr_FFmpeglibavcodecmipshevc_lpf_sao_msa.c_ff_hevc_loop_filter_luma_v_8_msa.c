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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  hevc_loopfilter_luma_ver_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ff_hevc_loop_filter_luma_v_8_msa(uint8_t *src,
                                      ptrdiff_t src_stride,
                                      int32_t beta, int32_t *tc,
                                      uint8_t *no_p, uint8_t *no_q)
{
    hevc_loopfilter_luma_ver_msa(src, src_stride, beta, tc, no_p, no_q);
}