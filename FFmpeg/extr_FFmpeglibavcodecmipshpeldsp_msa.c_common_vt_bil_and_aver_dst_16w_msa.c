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
 int /*<<< orphan*/  AVER_UB4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB (int const*) ; 
 int /*<<< orphan*/  LD_UB8 (int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_UB8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void common_vt_bil_and_aver_dst_16w_msa(const uint8_t *src,
                                               int32_t src_stride,
                                               uint8_t *dst, int32_t dst_stride,
                                               uint8_t height)
{
    uint8_t loop_cnt;
    v16u8 src0, src1, src2, src3, src4, src5, src6, src7, src8;
    v16u8 res0, res1, res2, res3, res4, res5, res6, res7;
    v16u8 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;

    src0 = LD_UB(src);
    src += src_stride;

    for (loop_cnt = (height >> 3); loop_cnt--;) {
        LD_UB8(src, src_stride, src1, src2, src3, src4, src5, src6, src7, src8);
        src += (8 * src_stride);
        AVER_UB4_UB(src0, src1, src1, src2, src2, src3, src3, src4,
                    res0, res1, res2, res3);
        AVER_UB4_UB(src4, src5, src5, src6, src6, src7, src7, src8,
                    res4, res5, res6, res7);

        LD_UB8(dst, dst_stride, dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7);
        AVER_UB4_UB(dst0, res0, dst1, res1, dst2, res2, dst3, res3,
                    res0, res1, res2, res3);
        AVER_UB4_UB(dst4, res4, dst5, res5, dst6, res6, dst7, res7,
                    res4, res5, res6, res7);
        ST_UB8(res0, res1, res2, res3, res4, res5, res6, res7, dst, dst_stride);
        dst += (8 * dst_stride);

        src0 = src8;
    }
}