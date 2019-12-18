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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  avc_chroma_hv_and_aver_dst_2w_msa (int*,int*,int /*<<< orphan*/ ,int,int,int,int,int) ; 
 int /*<<< orphan*/  avc_chroma_hz_and_aver_dst_2w_msa (int*,int*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  avc_chroma_vt_and_aver_dst_2w_msa (int*,int*,int /*<<< orphan*/ ,int,int,int) ; 

void ff_avg_h264_chroma_mc2_msa(uint8_t *dst, uint8_t *src,
                                ptrdiff_t stride, int height, int x, int y)
{
    int32_t cnt;

    av_assert2(x < 8 && y < 8 && x >= 0 && y >= 0);

    if (x && y) {
        avc_chroma_hv_and_aver_dst_2w_msa(src, dst, stride, x, (8 - x), y,
                                          (8 - y), height);
    } else if (x) {
        avc_chroma_hz_and_aver_dst_2w_msa(src, dst, stride, x, (8 - x), height);
    } else if (y) {
        avc_chroma_vt_and_aver_dst_2w_msa(src, dst, stride, y, (8 - y), height);
    } else {
        for (cnt = height; cnt--;) {
            dst[0] = (dst[0] + src[0] + 1) >> 1;
            dst[1] = (dst[1] + src[1] + 1) >> 1;

            src += stride;
            dst += stride;
        }
    }
}