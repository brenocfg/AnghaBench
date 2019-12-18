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
typedef  int /*<<< orphan*/  v8i16 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_DOT_SH3_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB5 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_D2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SAT_SH4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_D8 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B5_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_aver_s_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_h (int const) ; 

void ff_put_h264_qpel8_mc01_msa(uint8_t *dst, const uint8_t *src,
                                ptrdiff_t stride)
{
    const int16_t filt_const0 = 0xfb01;
    const int16_t filt_const1 = 0x1414;
    const int16_t filt_const2 = 0x1fb;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v16i8 src11, src12, src10_r, src32_r, src54_r, src65_r, src76_r, src98_r;
    v16i8 src21_r, src43_r, src87_r, src109_r, src1211_r, src1110_r;
    v16i8 tmp0, tmp1, tmp2, tmp3, filt0, filt1, filt2, out0, out1, out2, out3;
    v8i16 out0_r, out1_r, out2_r, out3_r, out4_r, out5_r, out6_r, out7_r;

    filt0 = (v16i8) __msa_fill_h(filt_const0);
    filt1 = (v16i8) __msa_fill_h(filt_const1);
    filt2 = (v16i8) __msa_fill_h(filt_const2);

    src -= (stride * 2);

    LD_SB5(src, stride, src0, src1, src2, src3, src4);
    src += (5 * stride);
    LD_SB8(src, stride, src5, src6, src7, src8, src9, src10, src11, src12);
    XORI_B8_128_SB(src5, src6, src7, src8, src9, src10, src11, src12);
    XORI_B5_128_SB(src0, src1, src2, src3, src4);
    ILVR_B4_SB(src1, src0, src2, src1, src3, src2, src4, src3, src10_r, src21_r,
               src32_r, src43_r);
    ILVR_B4_SB(src5, src4, src6, src5, src7, src6, src8, src7, src54_r, src65_r,
               src76_r, src87_r);
    ILVR_B4_SB(src9, src8, src10, src9, src11, src10, src12, src11, src98_r,
               src109_r, src1110_r, src1211_r);
    out0_r = AVC_DOT_SH3_SH(src10_r, src32_r, src54_r, filt0, filt1, filt2);
    out1_r = AVC_DOT_SH3_SH(src21_r, src43_r, src65_r, filt0, filt1, filt2);
    out2_r = AVC_DOT_SH3_SH(src32_r, src54_r, src76_r, filt0, filt1, filt2);
    out3_r = AVC_DOT_SH3_SH(src43_r, src65_r, src87_r, filt0, filt1, filt2);
    out4_r = AVC_DOT_SH3_SH(src54_r, src76_r, src98_r, filt0, filt1, filt2);
    out5_r = AVC_DOT_SH3_SH(src65_r, src87_r, src109_r, filt0, filt1, filt2);
    out6_r = AVC_DOT_SH3_SH(src76_r, src98_r, src1110_r, filt0, filt1, filt2);
    out7_r = AVC_DOT_SH3_SH(src87_r, src109_r, src1211_r, filt0, filt1, filt2);
    PCKEV_D2_SB(src3, src2, src5, src4, tmp0, tmp1);
    PCKEV_D2_SB(src7, src6, src9, src8, tmp2, tmp3);
    SRARI_H4_SH(out0_r, out1_r, out2_r, out3_r, 5);
    SRARI_H4_SH(out4_r, out5_r, out6_r, out7_r, 5);
    SAT_SH4_SH(out0_r, out1_r, out2_r, out3_r, 7);
    SAT_SH4_SH(out4_r, out5_r, out6_r, out7_r, 7);
    PCKEV_B2_SB(out1_r, out0_r, out3_r, out2_r, out0, out1);
    PCKEV_B2_SB(out5_r, out4_r, out7_r, out6_r, out2, out3);
    out0 = __msa_aver_s_b(out0, tmp0);
    out1 = __msa_aver_s_b(out1, tmp1);
    out2 = __msa_aver_s_b(out2, tmp2);
    out3 = __msa_aver_s_b(out3, tmp3);
    XORI_B4_128_SB(out0, out1, out2, out3);
    ST_D8(out0, out1, out2, out3, 0, 1, 0, 1, 0, 1, 0, 1, dst, stride);
}