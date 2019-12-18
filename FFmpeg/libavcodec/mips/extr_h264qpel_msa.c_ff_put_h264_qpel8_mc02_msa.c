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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_DOT_SH3_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB5 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_XORI128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_SH4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_D8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_h (int const) ; 

void ff_put_h264_qpel8_mc02_msa(uint8_t *dst, const uint8_t *src,
                                ptrdiff_t stride)
{
    const int16_t filt_const0 = 0xfb01;
    const int16_t filt_const1 = 0x1414;
    const int16_t filt_const2 = 0x1fb;
    v16u8 out0, out1, out2, out3;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v16i8 src11, src12, src10_r, src21_r, src32_r, src43_r, src76_r, src87_r;
    v16i8 src98_r, src109_r, src89_r, src910_r, src1110_r, src1211_r;
    v16i8 filt0, filt1, filt2;
    v8i16 out0_r, out1_r, out2_r, out3_r, out4_r, out5_r, out6_r, out7_r;

    filt0 = (v16i8) __msa_fill_h(filt_const0);
    filt1 = (v16i8) __msa_fill_h(filt_const1);
    filt2 = (v16i8) __msa_fill_h(filt_const2);

    src -= (stride * 2);

    LD_SB8(src, stride, src0, src1, src2, src3, src4, src5, src6, src7);
    src += (8 * stride);
    LD_SB5(src, stride, src8, src9, src10, src11, src12);
    ILVR_B4_SB(src1, src0, src2, src1, src3, src2, src4, src3, src10_r, src21_r,
               src32_r, src43_r);
    ILVR_B4_SB(src5, src4, src6, src5, src7, src6, src8, src7, src76_r, src87_r,
               src98_r, src109_r);
    ILVR_B4_SB(src9, src8, src10, src9, src11, src10, src12, src11, src89_r,
               src910_r, src1110_r, src1211_r);
    XORI_B4_128_SB(src10_r, src21_r, src32_r, src43_r);
    XORI_B4_128_SB(src76_r, src87_r, src98_r, src109_r);
    XORI_B4_128_SB(src89_r, src910_r, src1110_r, src1211_r);
    out0_r = AVC_DOT_SH3_SH(src10_r, src32_r, src76_r, filt0, filt1, filt2);
    out1_r = AVC_DOT_SH3_SH(src21_r, src43_r, src87_r, filt0, filt1, filt2);
    out2_r = AVC_DOT_SH3_SH(src32_r, src76_r, src98_r, filt0, filt1, filt2);
    out3_r = AVC_DOT_SH3_SH(src43_r, src87_r, src109_r, filt0, filt1, filt2);
    out4_r = AVC_DOT_SH3_SH(src76_r, src98_r, src89_r, filt0, filt1, filt2);
    out5_r = AVC_DOT_SH3_SH(src87_r, src109_r, src910_r, filt0, filt1, filt2);
    out6_r = AVC_DOT_SH3_SH(src98_r, src89_r, src1110_r, filt0, filt1, filt2);
    out7_r = AVC_DOT_SH3_SH(src109_r, src910_r, src1211_r, filt0, filt1, filt2);
    SRARI_H4_SH(out0_r, out1_r, out2_r, out3_r, 5);
    SRARI_H4_SH(out4_r, out5_r, out6_r, out7_r, 5);
    SAT_SH4_SH(out0_r, out1_r, out2_r, out3_r, 7);
    SAT_SH4_SH(out4_r, out5_r, out6_r, out7_r, 7);
    out0 = PCKEV_XORI128_UB(out0_r, out1_r);
    out1 = PCKEV_XORI128_UB(out2_r, out3_r);
    out2 = PCKEV_XORI128_UB(out4_r, out5_r);
    out3 = PCKEV_XORI128_UB(out6_r, out7_r);
    ST_D8(out0, out1, out2, out3, 0, 1, 0, 1, 0, 1, 0, 1, dst, stride);
}