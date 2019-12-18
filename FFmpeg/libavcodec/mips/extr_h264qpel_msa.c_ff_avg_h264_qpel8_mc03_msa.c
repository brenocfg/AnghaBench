#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8i16 ;
struct TYPE_15__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int ptrdiff_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_DOT_SH3_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  AVER_UB4_UB (scalar_t__,TYPE_1__,scalar_t__,TYPE_1__,scalar_t__,TYPE_1__,scalar_t__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  ILVR_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  INSERT_D2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ; 
 int /*<<< orphan*/  LD4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB5 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_D2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SAT_SH4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_D8 (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B5_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_aver_s_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_h (int const) ; 

void ff_avg_h264_qpel8_mc03_msa(uint8_t *dst, const uint8_t *src,
                                ptrdiff_t stride)
{
    uint64_t tp0, tp1, tp2, tp3;
    const int16_t filt_const0 = 0xfb01;
    const int16_t filt_const1 = 0x1414;
    const int16_t filt_const2 = 0x1fb;
    v16u8 dst0 = { 0 }, dst1 = { 0 }, dst2 = { 0 }, dst3 = { 0 };
    v16i8 src0, src1, src2, src3, src4, src7, src8, src9, src10, src11, src12;
    v16i8 src13, src14, tmp0, tmp1, tmp2, tmp3, src109_r;
    v16i8 src10_r, src32_r, src76_r, src98_r, src21_r, src43_r, src87_r;
    v16i8 filt0, filt1, filt2, out0, out1, out2, out3;
    v8i16 out0_r, out1_r, out2_r, out3_r, out4_r, out5_r, out6_r, out7_r;

    filt0 = (v16i8) __msa_fill_h(filt_const0);
    filt1 = (v16i8) __msa_fill_h(filt_const1);
    filt2 = (v16i8) __msa_fill_h(filt_const2);

    src -= (stride * 2);

    LD_SB5(src, stride, src0, src1, src2, src3, src4);
    src += (5 * stride);

    XORI_B5_128_SB(src0, src1, src2, src3, src4);
    ILVR_B4_SB(src1, src0, src2, src1, src3, src2, src4, src3, src10_r, src21_r,
               src32_r, src43_r);
    LD_SB8(src, stride, src7, src8, src9, src10, src11, src12, src13, src14);
    XORI_B8_128_SB(src7, src8, src9, src10, src11, src12, src13, src14);
    ILVR_B4_SB(src7, src4, src8, src7, src9, src8, src10, src9, src76_r,
               src87_r, src98_r, src109_r);
    out0_r = AVC_DOT_SH3_SH(src10_r, src32_r, src76_r, filt0, filt1, filt2);
    out1_r = AVC_DOT_SH3_SH(src21_r, src43_r, src87_r, filt0, filt1, filt2);
    out2_r = AVC_DOT_SH3_SH(src32_r, src76_r, src98_r, filt0, filt1, filt2);
    out3_r = AVC_DOT_SH3_SH(src43_r, src87_r, src109_r, filt0, filt1, filt2);
    PCKEV_D2_SB(src4, src3, src8, src7, tmp0, tmp1);
    ILVR_B4_SB(src11, src10, src12, src11, src13, src12, src14, src13, src10_r,
               src21_r, src32_r, src43_r);
    out4_r = AVC_DOT_SH3_SH(src76_r, src98_r, src10_r, filt0, filt1, filt2);
    out5_r = AVC_DOT_SH3_SH(src87_r, src109_r, src21_r, filt0, filt1, filt2);
    out6_r = AVC_DOT_SH3_SH(src98_r, src10_r, src32_r, filt0, filt1, filt2);
    out7_r = AVC_DOT_SH3_SH(src109_r, src21_r, src43_r, filt0, filt1, filt2);
    PCKEV_D2_SB(src10, src9, src12, src11, tmp2, tmp3);
    SRARI_H4_SH(out0_r, out1_r, out2_r, out3_r, 5);
    SRARI_H4_SH(out4_r, out5_r, out6_r, out7_r, 5);
    SAT_SH4_SH(out0_r, out1_r, out2_r, out3_r, 7);
    SAT_SH4_SH(out4_r, out5_r, out6_r, out7_r, 7);

    LD4(dst, stride, tp0, tp1, tp2, tp3);
    INSERT_D2_UB(tp0, tp1, dst0);
    INSERT_D2_UB(tp2, tp3, dst1);
    LD4(dst + 4 * stride, stride, tp0, tp1, tp2, tp3);
    INSERT_D2_UB(tp0, tp1, dst2);
    INSERT_D2_UB(tp2, tp3, dst3);

    PCKEV_B2_SB(out1_r, out0_r, out3_r, out2_r, out0, out1);
    PCKEV_B2_SB(out5_r, out4_r, out7_r, out6_r, out2, out3);
    out0 = __msa_aver_s_b(out0, tmp0);
    out1 = __msa_aver_s_b(out1, tmp1);
    out2 = __msa_aver_s_b(out2, tmp2);
    out3 = __msa_aver_s_b(out3, tmp3);
    XORI_B4_128_SB(out0, out1, out2, out3);
    AVER_UB4_UB(out0, dst0, out1, dst1, out2, dst2, out3, dst3, dst0, dst1,
                dst2, dst3);
    ST_D8(dst0, dst1, dst2, dst3, 0, 1, 0, 1, 0, 1, 0, 1, dst, stride);
}