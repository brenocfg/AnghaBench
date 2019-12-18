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
typedef  int /*<<< orphan*/  v8u16 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HADD_UB3_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_B2_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB (int const*) ; 
 int /*<<< orphan*/  LD_UB8 (int const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_ST_SB4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  SRARI_H4_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void common_hv_bil_16w_msa(const uint8_t *src, int32_t src_stride,
                                  uint8_t *dst, int32_t dst_stride,
                                  uint8_t height)
{
    uint8_t loop_cnt;
    v16u8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9;
    v16u8 src10, src11, src12, src13, src14, src15, src16, src17;
    v8u16 src0_r, src1_r, src2_r, src3_r, src4_r, src5_r, src6_r, src7_r;
    v8u16 src8_r, src0_l, src1_l, src2_l, src3_l, src4_l, src5_l, src6_l;
    v8u16 src7_l, src8_l;
    v8u16 sum0_r, sum1_r, sum2_r, sum3_r, sum4_r, sum5_r, sum6_r, sum7_r;
    v8u16 sum0_l, sum1_l, sum2_l, sum3_l, sum4_l, sum5_l, sum6_l, sum7_l;

    for (loop_cnt = (height >> 3); loop_cnt--;) {
        LD_UB8(src, src_stride, src0, src1, src2, src3, src4, src5, src6, src7);
        LD_UB8((src + 1), src_stride,
               src9, src10, src11, src12, src13, src14, src15, src16);
        src += (8 * src_stride);

        src8 = LD_UB(src);
        src17 = LD_UB(src + 1);

        ILVRL_B2_UH(src9, src0, src0_r, src0_l);
        ILVRL_B2_UH(src10, src1, src1_r, src1_l);
        ILVRL_B2_UH(src11, src2, src2_r, src2_l);
        ILVRL_B2_UH(src12, src3, src3_r, src3_l);
        ILVRL_B2_UH(src13, src4, src4_r, src4_l);
        ILVRL_B2_UH(src14, src5, src5_r, src5_l);
        ILVRL_B2_UH(src15, src6, src6_r, src6_l);
        ILVRL_B2_UH(src16, src7, src7_r, src7_l);
        ILVRL_B2_UH(src17, src8, src8_r, src8_l);
        HADD_UB3_UH(src0_r, src1_r, src2_r, src0_r, src1_r, src2_r);
        HADD_UB3_UH(src3_r, src4_r, src5_r, src3_r, src4_r, src5_r);
        HADD_UB3_UH(src6_r, src7_r, src8_r, src6_r, src7_r, src8_r);
        HADD_UB3_UH(src0_l, src1_l, src2_l, src0_l, src1_l, src2_l);
        HADD_UB3_UH(src3_l, src4_l, src5_l, src3_l, src4_l, src5_l);
        HADD_UB3_UH(src6_l, src7_l, src8_l, src6_l, src7_l, src8_l);
        ADD4(src0_r, src1_r, src1_r, src2_r, src2_r, src3_r, src3_r, src4_r,
             sum0_r, sum1_r, sum2_r, sum3_r);
        ADD4(src4_r, src5_r, src5_r, src6_r, src6_r, src7_r, src7_r, src8_r,
             sum4_r, sum5_r, sum6_r, sum7_r);
        ADD4(src0_l, src1_l, src1_l, src2_l, src2_l, src3_l, src3_l, src4_l,
             sum0_l, sum1_l, sum2_l, sum3_l);
        ADD4(src4_l, src5_l, src5_l, src6_l, src6_l, src7_l, src7_l, src8_l,
             sum4_l, sum5_l, sum6_l, sum7_l);
        SRARI_H4_UH(sum0_r, sum1_r, sum2_r, sum3_r, 2);
        SRARI_H4_UH(sum4_r, sum5_r, sum6_r, sum7_r, 2);
        SRARI_H4_UH(sum0_l, sum1_l, sum2_l, sum3_l, 2);
        SRARI_H4_UH(sum4_l, sum5_l, sum6_l, sum7_l, 2);
        PCKEV_ST_SB4(sum0_l, sum0_r, sum1_l, sum1_r, sum2_l, sum2_r,
                     sum3_l, sum3_r, dst, dst_stride);
        dst += (4 * dst_stride);
        PCKEV_ST_SB4(sum4_l, sum4_r, sum5_l, sum5_r, sum6_l, sum6_r,
                     sum7_l, sum7_r, dst, dst_stride);
        dst += (4 * dst_stride);
    }
}