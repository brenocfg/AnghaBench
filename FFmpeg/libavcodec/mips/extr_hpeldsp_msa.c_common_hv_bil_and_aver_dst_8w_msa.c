#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8u16 ;
typedef  int /*<<< orphan*/  v16u8 ;
struct TYPE_32__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HADD_UB2_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HADD_UB3_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_UB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B3_UB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ LD_SB (int const*) ; 
 int /*<<< orphan*/  LD_SB4 (int const*,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  LD_UB4 (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_AVG_ST8x4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  SLDI_B2_SB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SLDI_B3_SB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SRARI_H4_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void common_hv_bil_and_aver_dst_8w_msa(const uint8_t *src,
                                              int32_t src_stride,
                                              uint8_t *dst, int32_t dst_stride,
                                              uint8_t height)
{
    uint8_t loop_cnt;
    v16i8 src0, src1, src2, src3, src4;
    v16i8 src0_sld1, src1_sld1, src2_sld1, src3_sld1, src4_sld1;
    v16u8 dst0, dst1, dst2, dst3;
    v16u8 src0_r, src1_r, src2_r, src3_r, src4_r;
    v8u16 add0, add1, add2, add3, add4;
    v8u16 sum0, sum1, sum2, sum3;
    v16i8 zeros = { 0 };

    src0 = LD_SB(src);
    src += src_stride;

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_SB4(src, src_stride, src1, src2, src3, src4);
        src += (4 * src_stride);

        LD_UB4(dst, dst_stride, dst0, dst1, dst2, dst3);
        SLDI_B3_SB(zeros, src0, zeros, src1, zeros, src2, 1, src0_sld1,
                   src1_sld1, src2_sld1);
        SLDI_B2_SB(zeros, src3, zeros, src4, 1, src3_sld1, src4_sld1);
        ILVR_B3_UB(src0_sld1, src0, src1_sld1, src1, src2_sld1, src2, src0_r,
                   src1_r, src2_r);
        ILVR_B2_UB(src3_sld1, src3, src4_sld1, src4, src3_r, src4_r);
        HADD_UB3_UH(src0_r, src1_r, src2_r, add0, add1, add2);
        HADD_UB2_UH(src3_r, src4_r, add3, add4);
        ADD4(add0, add1, add1, add2, add2, add3, add3, add4,
             sum0, sum1, sum2, sum3);
        SRARI_H4_UH(sum0, sum1, sum2, sum3, 2);
        PCKEV_AVG_ST8x4_UB(sum0, dst0, sum1, dst1,
                           sum2, dst2, sum3, dst3, dst, dst_stride);
        dst += (4 * dst_stride);
        src0 = src4;
    }
}