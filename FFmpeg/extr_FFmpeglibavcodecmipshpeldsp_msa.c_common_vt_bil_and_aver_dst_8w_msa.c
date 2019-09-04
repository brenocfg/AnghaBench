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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVER_DST_ST8x4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  LD_UB (int const*) ; 
 int /*<<< orphan*/  LD_UB4 (int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void common_vt_bil_and_aver_dst_8w_msa(const uint8_t *src,
                                              int32_t src_stride,
                                              uint8_t *dst, int32_t dst_stride,
                                              uint8_t height)
{
    uint8_t loop_cnt;
    v16u8 src0, src1, src2, src3, src4;

    src0 = LD_UB(src);
    src += src_stride;

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_UB4(src, src_stride, src1, src2, src3, src4);
        src += (4 * src_stride);

        AVER_DST_ST8x4_UB(src0, src1, src1, src2, src2, src3, src3, src4,
                          dst, dst_stride);
        dst += (4 * dst_stride);
        src0 = src4;
    }
}