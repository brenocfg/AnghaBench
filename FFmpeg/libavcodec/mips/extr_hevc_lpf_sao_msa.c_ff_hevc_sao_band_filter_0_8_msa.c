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
 int /*<<< orphan*/  hevc_sao_band_filter_16multiple_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  hevc_sao_band_filter_4width_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hevc_sao_band_filter_8width_msa (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 

void ff_hevc_sao_band_filter_0_8_msa(uint8_t *dst, uint8_t *src,
                                     ptrdiff_t stride_dst, ptrdiff_t stride_src,
                                     int16_t *sao_offset_val, int sao_left_class,
                                     int width, int height)
{
    if (width >> 4) {
        hevc_sao_band_filter_16multiple_msa(dst, stride_dst, src, stride_src,
                                            sao_left_class, sao_offset_val,
                                            width - (width % 16), height);
        dst += width - (width % 16);
        src += width - (width % 16);
        width %= 16;
    }

    if (width >> 3) {
        hevc_sao_band_filter_8width_msa(dst, stride_dst, src, stride_src,
                                        sao_left_class, sao_offset_val, height);
        dst += 8;
        src += 8;
        width %= 8;
    }

    if (width) {
        hevc_sao_band_filter_4width_msa(dst, stride_dst, src, stride_src,
                                        sao_left_class, sao_offset_val, height);
    }
}