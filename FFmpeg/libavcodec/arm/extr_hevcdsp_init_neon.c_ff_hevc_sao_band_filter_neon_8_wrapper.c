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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ff_hevc_sao_band_filter_neon_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

void ff_hevc_sao_band_filter_neon_8_wrapper(uint8_t *_dst, uint8_t *_src,
                                  ptrdiff_t stride_dst, ptrdiff_t stride_src,
                                  int16_t *sao_offset_val, int sao_left_class,
                                  int width, int height) {
    uint8_t *dst = _dst;
    uint8_t *src = _src;
    int16_t offset_table[32] = {0};
    int k;

    for (k = 0; k < 4; k++) {
        offset_table[(k + sao_left_class) & 31] = sao_offset_val[k + 1];
    }

    ff_hevc_sao_band_filter_neon_8(dst, src, stride_dst, stride_src, width, height, offset_table);
}