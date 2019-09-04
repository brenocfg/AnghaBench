#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8i16 ;
typedef  int /*<<< orphan*/  v16u8 ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUTTERFLY_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLIP_SH2_0_255 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SH (TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_UB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRARI_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST8x1_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VP9_MADD_BF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP9_MADD_SHORT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VP9_SET_COSPI_PAIR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cospi_11_64 ; 
 int /*<<< orphan*/  cospi_12_64 ; 
 int /*<<< orphan*/  cospi_13_64 ; 
 int /*<<< orphan*/  cospi_15_64 ; 
 int /*<<< orphan*/  cospi_16_64 ; 
 int /*<<< orphan*/  cospi_17_64 ; 
 int /*<<< orphan*/  cospi_19_64 ; 
 int /*<<< orphan*/  cospi_1_64 ; 
 int /*<<< orphan*/  cospi_20_64 ; 
 int /*<<< orphan*/  cospi_21_64 ; 
 int /*<<< orphan*/  cospi_23_64 ; 
 int /*<<< orphan*/  cospi_24_64 ; 
 int /*<<< orphan*/  cospi_25_64 ; 
 int /*<<< orphan*/  cospi_27_64 ; 
 int /*<<< orphan*/  cospi_28_64 ; 
 int /*<<< orphan*/  cospi_29_64 ; 
 int /*<<< orphan*/  cospi_31_64 ; 
 int /*<<< orphan*/  cospi_3_64 ; 
 int /*<<< orphan*/  cospi_4_64 ; 
 int /*<<< orphan*/  cospi_5_64 ; 
 int /*<<< orphan*/  cospi_7_64 ; 
 int /*<<< orphan*/  cospi_8_64 ; 
 int /*<<< orphan*/  cospi_9_64 ; 

__attribute__((used)) static void vp9_iadst16_1d_columns_addblk_msa(int16_t *input, uint8_t *dst,
                                              int32_t dst_stride)
{
    v8i16 v0, v2, v4, v6, k0, k1, k2, k3;
    v8i16 r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15;
    v8i16 out0, out1, out2, out3, out4, out5, out6, out7;
    v8i16 out8, out9, out10, out11, out12, out13, out14, out15;
    v8i16 g0, g1, g2, g3, g4, g5, g6, g7, g8, g9, g10, g11, g12, g13, g14, g15;
    v8i16 h0, h1, h2, h3, h4, h5, h6, h7, h8, h9, h10, h11;
    v8i16 res0, res1, res2, res3, res4, res5, res6, res7;
    v8i16 res8, res9, res10, res11, res12, res13, res14, res15;
    v16u8 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;
    v16u8 dst8, dst9, dst10, dst11, dst12, dst13, dst14, dst15;
    v16i8 zero = { 0 };

    r0 = LD_SH(input + 0 * 16);
    r3 = LD_SH(input + 3 * 16);
    r4 = LD_SH(input + 4 * 16);
    r7 = LD_SH(input + 7 * 16);
    r8 = LD_SH(input + 8 * 16);
    r11 = LD_SH(input + 11 * 16);
    r12 = LD_SH(input + 12 * 16);
    r15 = LD_SH(input + 15 * 16);

    /* stage 1 */
    k0 = VP9_SET_COSPI_PAIR(cospi_1_64, cospi_31_64);
    k1 = VP9_SET_COSPI_PAIR(cospi_31_64, -cospi_1_64);
    k2 = VP9_SET_COSPI_PAIR(cospi_17_64, cospi_15_64);
    k3 = VP9_SET_COSPI_PAIR(cospi_15_64, -cospi_17_64);
    VP9_MADD_BF(r15, r0, r7, r8, k0, k1, k2, k3, g0, g1, g2, g3);
    k0 = VP9_SET_COSPI_PAIR(cospi_9_64, cospi_23_64);
    k1 = VP9_SET_COSPI_PAIR(cospi_23_64, -cospi_9_64);
    k2 = VP9_SET_COSPI_PAIR(cospi_25_64, cospi_7_64);
    k3 = VP9_SET_COSPI_PAIR(cospi_7_64, -cospi_25_64);
    VP9_MADD_BF(r11, r4, r3, r12, k0, k1, k2, k3, g8, g9, g10, g11);
    BUTTERFLY_4(g0, g2, g10, g8, h8, h9, v2, v0);
    k0 = VP9_SET_COSPI_PAIR(cospi_4_64, cospi_28_64);
    k1 = VP9_SET_COSPI_PAIR(cospi_28_64, -cospi_4_64);
    k2 = VP9_SET_COSPI_PAIR(-cospi_28_64, cospi_4_64);
    VP9_MADD_BF(g1, g3, g9, g11, k0, k1, k2, k0, h0, h1, h2, h3);

    r1 = LD_SH(input + 1 * 16);
    r2 = LD_SH(input + 2 * 16);
    r5 = LD_SH(input + 5 * 16);
    r6 = LD_SH(input + 6 * 16);
    r9 = LD_SH(input + 9 * 16);
    r10 = LD_SH(input + 10 * 16);
    r13 = LD_SH(input + 13 * 16);
    r14 = LD_SH(input + 14 * 16);

    k0 = VP9_SET_COSPI_PAIR(cospi_5_64, cospi_27_64);
    k1 = VP9_SET_COSPI_PAIR(cospi_27_64, -cospi_5_64);
    k2 = VP9_SET_COSPI_PAIR(cospi_21_64, cospi_11_64);
    k3 = VP9_SET_COSPI_PAIR(cospi_11_64, -cospi_21_64);
    VP9_MADD_BF(r13, r2, r5, r10, k0, k1, k2, k3, g4, g5, g6, g7);
    k0 = VP9_SET_COSPI_PAIR(cospi_13_64, cospi_19_64);
    k1 = VP9_SET_COSPI_PAIR(cospi_19_64, -cospi_13_64);
    k2 = VP9_SET_COSPI_PAIR(cospi_29_64, cospi_3_64);
    k3 = VP9_SET_COSPI_PAIR(cospi_3_64, -cospi_29_64);
    VP9_MADD_BF(r9, r6, r1, r14, k0, k1, k2, k3, g12, g13, g14, g15);
    BUTTERFLY_4(g4, g6, g14, g12, h10, h11, v6, v4);
    BUTTERFLY_4(h8, h9, h11, h10, out0, out1, h11, h10);
    out1 = -out1;
    SRARI_H2_SH(out0, out1, 6);
    dst0 = LD_UB(dst + 0 * dst_stride);
    dst1 = LD_UB(dst + 15 * dst_stride);
    ILVR_B2_SH(zero, dst0, zero, dst1, res0, res1);
    ADD2(res0, out0, res1, out1, res0, res1);
    CLIP_SH2_0_255(res0, res1);
    PCKEV_B2_SH(res0, res0, res1, res1, res0, res1);
    ST8x1_UB(res0, dst);
    ST8x1_UB(res1, dst + 15 * dst_stride);

    k0 = VP9_SET_COSPI_PAIR(cospi_12_64, cospi_20_64);
    k1 = VP9_SET_COSPI_PAIR(-cospi_20_64, cospi_12_64);
    k2 = VP9_SET_COSPI_PAIR(cospi_20_64, -cospi_12_64);
    VP9_MADD_BF(g7, g5, g15, g13, k0, k1, k2, k0, h4, h5, h6, h7);
    BUTTERFLY_4(h0, h2, h6, h4, out8, out9, out11, out10);
    out8 = -out8;

    SRARI_H2_SH(out8, out9, 6);
    dst8 = LD_UB(dst + 1 * dst_stride);
    dst9 = LD_UB(dst + 14 * dst_stride);
    ILVR_B2_SH(zero, dst8, zero, dst9, res8, res9);
    ADD2(res8, out8, res9, out9, res8, res9);
    CLIP_SH2_0_255(res8, res9);
    PCKEV_B2_SH(res8, res8, res9, res9, res8, res9);
    ST8x1_UB(res8, dst + dst_stride);
    ST8x1_UB(res9, dst + 14 * dst_stride);

    k0 = VP9_SET_COSPI_PAIR(cospi_8_64, cospi_24_64);
    k1 = VP9_SET_COSPI_PAIR(cospi_24_64, -cospi_8_64);
    k2 = VP9_SET_COSPI_PAIR(-cospi_24_64, cospi_8_64);
    VP9_MADD_BF(v0, v2, v4, v6, k0, k1, k2, k0, out4, out6, out5, out7);
    out4 = -out4;
    SRARI_H2_SH(out4, out5, 6);
    dst4 = LD_UB(dst + 3 * dst_stride);
    dst5 = LD_UB(dst + 12 * dst_stride);
    ILVR_B2_SH(zero, dst4, zero, dst5, res4, res5);
    ADD2(res4, out4, res5, out5, res4, res5);
    CLIP_SH2_0_255(res4, res5);
    PCKEV_B2_SH(res4, res4, res5, res5, res4, res5);
    ST8x1_UB(res4, dst + 3 * dst_stride);
    ST8x1_UB(res5, dst + 12 * dst_stride);

    VP9_MADD_BF(h1, h3, h5, h7, k0, k1, k2, k0, out12, out14, out13, out15);
    out13 = -out13;
    SRARI_H2_SH(out12, out13, 6);
    dst12 = LD_UB(dst + 2 * dst_stride);
    dst13 = LD_UB(dst + 13 * dst_stride);
    ILVR_B2_SH(zero, dst12, zero, dst13, res12, res13);
    ADD2(res12, out12, res13, out13, res12, res13);
    CLIP_SH2_0_255(res12, res13);
    PCKEV_B2_SH(res12, res12, res13, res13, res12, res13);
    ST8x1_UB(res12, dst + 2 * dst_stride);
    ST8x1_UB(res13, dst + 13 * dst_stride);

    k0 = VP9_SET_COSPI_PAIR(cospi_16_64, cospi_16_64);
    k3 = VP9_SET_COSPI_PAIR(-cospi_16_64, cospi_16_64);
    VP9_MADD_SHORT(out6, out7, k0, k3, out6, out7);
    SRARI_H2_SH(out6, out7, 6);
    dst6 = LD_UB(dst + 4 * dst_stride);
    dst7 = LD_UB(dst + 11 * dst_stride);
    ILVR_B2_SH(zero, dst6, zero, dst7, res6, res7);
    ADD2(res6, out6, res7, out7, res6, res7);
    CLIP_SH2_0_255(res6, res7);
    PCKEV_B2_SH(res6, res6, res7, res7, res6, res7);
    ST8x1_UB(res6, dst + 4 * dst_stride);
    ST8x1_UB(res7, dst + 11 * dst_stride);

    VP9_MADD_SHORT(out10, out11, k0, k3, out10, out11);
    SRARI_H2_SH(out10, out11, 6);
    dst10 = LD_UB(dst + 6 * dst_stride);
    dst11 = LD_UB(dst + 9 * dst_stride);
    ILVR_B2_SH(zero, dst10, zero, dst11, res10, res11);
    ADD2(res10, out10, res11, out11, res10, res11);
    CLIP_SH2_0_255(res10, res11);
    PCKEV_B2_SH(res10, res10, res11, res11, res10, res11);
    ST8x1_UB(res10, dst + 6 * dst_stride);
    ST8x1_UB(res11, dst + 9 * dst_stride);

    k1 = VP9_SET_COSPI_PAIR(-cospi_16_64, -cospi_16_64);
    k2 = VP9_SET_COSPI_PAIR(cospi_16_64, -cospi_16_64);
    VP9_MADD_SHORT(h10, h11, k1, k2, out2, out3);
    SRARI_H2_SH(out2, out3, 6);
    dst2 = LD_UB(dst + 7 * dst_stride);
    dst3 = LD_UB(dst + 8 * dst_stride);
    ILVR_B2_SH(zero, dst2, zero, dst3, res2, res3);
    ADD2(res2, out2, res3, out3, res2, res3);
    CLIP_SH2_0_255(res2, res3);
    PCKEV_B2_SH(res2, res2, res3, res3, res2, res3);
    ST8x1_UB(res2, dst + 7 * dst_stride);
    ST8x1_UB(res3, dst + 8 * dst_stride);

    VP9_MADD_SHORT(out14, out15, k1, k2, out14, out15);
    SRARI_H2_SH(out14, out15, 6);
    dst14 = LD_UB(dst + 5 * dst_stride);
    dst15 = LD_UB(dst + 10 * dst_stride);
    ILVR_B2_SH(zero, dst14, zero, dst15, res14, res15);
    ADD2(res14, out14, res15, out15, res14, res15);
    CLIP_SH2_0_255(res14, res15);
    PCKEV_B2_SH(res14, res14, res15, res15, res14, res15);
    ST8x1_UB(res14, dst + 5 * dst_stride);
    ST8x1_UB(res15, dst + 10 * dst_stride);
}