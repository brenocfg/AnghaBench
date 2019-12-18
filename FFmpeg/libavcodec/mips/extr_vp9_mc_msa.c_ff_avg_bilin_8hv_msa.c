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
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  common_hv_2ht_2vt_and_aver_dst_8x4_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  common_hv_2ht_2vt_and_aver_dst_8x8mult_msa (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ ** vp9_bilinear_filters_msa ; 

void ff_avg_bilin_8hv_msa(uint8_t *dst, ptrdiff_t dst_stride,
                          const uint8_t *src, ptrdiff_t src_stride,
                          int height, int mx, int my)
{
    const int8_t *filter_horiz = vp9_bilinear_filters_msa[mx - 1];
    const int8_t *filter_vert = vp9_bilinear_filters_msa[my - 1];

    if (4 == height) {
        common_hv_2ht_2vt_and_aver_dst_8x4_msa(src, src_stride, dst, dst_stride,
                                               filter_horiz, filter_vert);
    } else {
        common_hv_2ht_2vt_and_aver_dst_8x8mult_msa(src, src_stride,
                                                   dst, dst_stride,
                                                   filter_horiz, filter_vert,
                                                   height);
    }
}