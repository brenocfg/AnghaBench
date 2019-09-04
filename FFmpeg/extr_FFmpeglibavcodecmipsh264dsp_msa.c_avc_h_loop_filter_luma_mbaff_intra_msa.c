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
typedef  int v8u16 ;
typedef  scalar_t__ v8i16 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  int /*<<< orphan*/  v2i64 ;
typedef  scalar_t__ v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ILVL_H2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVL_W2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B2_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B4_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  ILVR_H2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_W2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_W2_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PCKEV_B2_UB (int,int,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SH (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SLDI_B2_0_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SLDI_B4_0_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ __msa_asub_u_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_bmnz_v (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __msa_copy_u_h (scalar_t__,int) ; 
 int /*<<< orphan*/  __msa_copy_u_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_fill_b (int) ; 
 scalar_t__ __msa_ilvl_w (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_ilvr_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_insert_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_pckev_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_srari_h (scalar_t__,int) ; 

__attribute__((used)) static void avc_h_loop_filter_luma_mbaff_intra_msa(uint8_t *src, int32_t stride,
                                                   int32_t alpha_in,
                                                   int32_t beta_in)
{
    uint64_t load0, load1;
    uint32_t out0, out2;
    uint16_t out1, out3;
    v8u16 src0_r, src1_r, src2_r, src3_r, src4_r, src5_r, src6_r, src7_r;
    v8u16 dst0_r, dst1_r, dst4_r, dst5_r;
    v8u16 dst2_x_r, dst2_y_r, dst3_x_r, dst3_y_r;
    v16u8 dst0, dst1, dst4, dst5, dst2_x, dst2_y, dst3_x, dst3_y;
    v8i16 tmp0, tmp1, tmp2, tmp3;
    v16u8 alpha, beta;
    v16u8 p0_asub_q0, p1_asub_p0, q1_asub_q0, p2_asub_p0, q2_asub_q0;
    v16u8 is_less_than, is_less_than_alpha, is_less_than_beta;
    v16u8 is_less_than_beta1, is_less_than_beta2;
    v16i8 src0 = { 0 };
    v16i8 src1 = { 0 };
    v16i8 src2 = { 0 };
    v16i8 src3 = { 0 };
    v16i8 src4 = { 0 };
    v16i8 src5 = { 0 };
    v16i8 src6 = { 0 };
    v16i8 src7 = { 0 };
    v16i8 zeros = { 0 };

    load0 = LD(src - 4);
    load1 = LD(src + stride - 4);
    src0 = (v16i8) __msa_insert_d((v2i64) src0, 0, load0);
    src1 = (v16i8) __msa_insert_d((v2i64) src1, 0, load1);

    load0 = LD(src + (2 * stride) - 4);
    load1 = LD(src + (3 * stride) - 4);
    src2 = (v16i8) __msa_insert_d((v2i64) src2, 0, load0);
    src3 = (v16i8) __msa_insert_d((v2i64) src3, 0, load1);

    load0 = LD(src + (4 * stride) - 4);
    load1 = LD(src + (5 * stride) - 4);
    src4 = (v16i8) __msa_insert_d((v2i64) src4, 0, load0);
    src5 = (v16i8) __msa_insert_d((v2i64) src5, 0, load1);

    load0 = LD(src + (6 * stride) - 4);
    load1 = LD(src + (7 * stride) - 4);
    src6 = (v16i8) __msa_insert_d((v2i64) src6, 0, load0);
    src7 = (v16i8) __msa_insert_d((v2i64) src7, 0, load1);

    ILVR_B4_SB(src1, src0, src3, src2, src5, src4, src7, src6,
               src0, src1, src2, src3);

    ILVR_H2_SH(src1, src0, src3, src2, tmp0, tmp2);
    ILVL_H2_SH(src1, src0, src3, src2, tmp1, tmp3);

    ILVR_W2_SB(tmp2, tmp0, tmp3, tmp1, src6, src3);
    ILVL_W2_SB(tmp2, tmp0, tmp3, tmp1, src1, src5);
    SLDI_B4_0_SB(src6, src1, src3, src5, src0, src2, src4, src7, 8);

    p0_asub_q0 = __msa_asub_u_b((v16u8) src2, (v16u8) src3);
    p1_asub_p0 = __msa_asub_u_b((v16u8) src1, (v16u8) src2);
    q1_asub_q0 = __msa_asub_u_b((v16u8) src4, (v16u8) src3);

    alpha = (v16u8) __msa_fill_b(alpha_in);
    beta = (v16u8) __msa_fill_b(beta_in);

    is_less_than_alpha = (p0_asub_q0 < alpha);
    is_less_than_beta = (p1_asub_p0 < beta);
    is_less_than = is_less_than_alpha & is_less_than_beta;
    is_less_than_beta = (q1_asub_q0 < beta);
    is_less_than = is_less_than & is_less_than_beta;

    alpha >>= 2;
    alpha += 2;

    is_less_than_alpha = (p0_asub_q0 < alpha);

    p2_asub_p0 = __msa_asub_u_b((v16u8) src0, (v16u8) src2);
    is_less_than_beta1 = (p2_asub_p0 < beta);
    q2_asub_q0 = __msa_asub_u_b((v16u8) src5, (v16u8) src3);
    is_less_than_beta2 = (q2_asub_q0 < beta);

    ILVR_B4_UH(zeros, src0, zeros, src1, zeros, src2, zeros, src3,
               src0_r, src1_r, src2_r, src3_r);
    ILVR_B4_UH(zeros, src4, zeros, src5, zeros, src6, zeros, src7,
               src4_r, src5_r, src6_r, src7_r);

    dst2_x_r = src1_r + src2_r + src3_r;
    dst2_x_r = src0_r + (2 * (dst2_x_r)) + src4_r;
    dst2_x_r = (v8u16) __msa_srari_h((v8i16) dst2_x_r, 3);
    dst1_r = src0_r + src1_r + src2_r + src3_r;
    dst1_r = (v8u16) __msa_srari_h((v8i16) dst1_r, 2);

    dst0_r = (2 * src6_r) + (3 * src0_r);
    dst0_r += src1_r + src2_r + src3_r;
    dst0_r = (v8u16) __msa_srari_h((v8i16) dst0_r, 3);
    dst2_y_r = (2 * src1_r) + src2_r + src4_r;
    dst2_y_r = (v8u16) __msa_srari_h((v8i16) dst2_y_r, 2);

    PCKEV_B2_UB(dst2_x_r, dst2_x_r, dst2_y_r, dst2_y_r, dst2_x, dst2_y);
    dst2_x = __msa_bmnz_v(dst2_y, dst2_x, is_less_than_beta1);

    dst3_x_r = src2_r + src3_r + src4_r;
    dst3_x_r = src1_r + (2 * dst3_x_r) + src5_r;
    dst3_x_r = (v8u16) __msa_srari_h((v8i16) dst3_x_r, 3);
    dst4_r = src2_r + src3_r + src4_r + src5_r;
    dst4_r = (v8u16) __msa_srari_h((v8i16) dst4_r, 2);

    dst5_r = (2 * src7_r) + (3 * src5_r);
    dst5_r += src4_r + src3_r + src2_r;
    dst5_r = (v8u16) __msa_srari_h((v8i16) dst5_r, 3);
    dst3_y_r = (2 * src4_r) + src3_r + src1_r;
    dst3_y_r = (v8u16) __msa_srari_h((v8i16) dst3_y_r, 2);

    PCKEV_B2_UB(dst3_x_r, dst3_x_r, dst3_y_r, dst3_y_r, dst3_x, dst3_y);
    dst3_x = __msa_bmnz_v(dst3_y, dst3_x, is_less_than_beta2);

    dst2_y_r = (2 * src1_r) + src2_r + src4_r;
    dst2_y_r = (v8u16) __msa_srari_h((v8i16) dst2_y_r, 2);
    dst3_y_r = (2 * src4_r) + src3_r + src1_r;
    dst3_y_r = (v8u16) __msa_srari_h((v8i16) dst3_y_r, 2);

    PCKEV_B2_UB(dst2_y_r, dst2_y_r, dst3_y_r, dst3_y_r, dst2_y, dst3_y);

    dst2_x = __msa_bmnz_v(dst2_y, dst2_x, is_less_than_alpha);
    dst3_x = __msa_bmnz_v(dst3_y, dst3_x, is_less_than_alpha);
    dst2_x = __msa_bmnz_v((v16u8) src2, dst2_x, is_less_than);
    dst3_x = __msa_bmnz_v((v16u8) src3, dst3_x, is_less_than);

    is_less_than = is_less_than_alpha & is_less_than;
    dst1 = (v16u8) __msa_pckev_b((v16i8) dst1_r, (v16i8) dst1_r);
    is_less_than_beta1 = is_less_than_beta1 & is_less_than;
    dst1 = __msa_bmnz_v((v16u8) src1, dst1, is_less_than_beta1);

    dst0 = (v16u8) __msa_pckev_b((v16i8) dst0_r, (v16i8) dst0_r);
    dst0 = __msa_bmnz_v((v16u8) src0, dst0, is_less_than_beta1);
    dst4 = (v16u8) __msa_pckev_b((v16i8) dst4_r, (v16i8) dst4_r);
    is_less_than_beta2 = is_less_than_beta2 & is_less_than;
    dst4 = __msa_bmnz_v((v16u8) src4, dst4, is_less_than_beta2);
    dst5 = (v16u8) __msa_pckev_b((v16i8) dst5_r, (v16i8) dst5_r);
    dst5 = __msa_bmnz_v((v16u8) src5, dst5, is_less_than_beta2);

    ILVR_B2_UB(dst1, dst0, dst3_x, dst2_x, dst0, dst1);
    dst2_x = (v16u8) __msa_ilvr_b((v16i8) dst5, (v16i8) dst4);
    ILVRL_H2_SH(dst1, dst0, tmp0, tmp1);
    ILVRL_H2_SH(zeros, dst2_x, tmp2, tmp3);

    ILVR_W2_UB(tmp2, tmp0, tmp3, tmp1, dst0, dst4);
    SLDI_B2_0_UB(dst0, dst4, dst1, dst5, 8);
    dst2_x = (v16u8) __msa_ilvl_w((v4i32) tmp2, (v4i32) tmp0);
    dst2_y = (v16u8) __msa_ilvl_w((v4i32) tmp3, (v4i32) tmp1);
    SLDI_B2_0_UB(dst2_x, dst2_y, dst3_x, dst3_y, 8);

    out0 = __msa_copy_u_w((v4i32) dst0, 0);
    out1 = __msa_copy_u_h((v8i16) dst0, 2);
    out2 = __msa_copy_u_w((v4i32) dst1, 0);
    out3 = __msa_copy_u_h((v8i16) dst1, 2);

    SW(out0, (src - 3));
    SH(out1, (src + 1));
    src += stride;
    SW(out2, (src - 3));
    SH(out3, (src + 1));
    src += stride;

    out0 = __msa_copy_u_w((v4i32) dst2_x, 0);
    out1 = __msa_copy_u_h((v8i16) dst2_x, 2);
    out2 = __msa_copy_u_w((v4i32) dst3_x, 0);
    out3 = __msa_copy_u_h((v8i16) dst3_x, 2);

    SW(out0, (src - 3));
    SH(out1, (src + 1));
    src += stride;
    SW(out2, (src - 3));
    SH(out3, (src + 1));
    src += stride;

    out0 = __msa_copy_u_w((v4i32) dst4, 0);
    out1 = __msa_copy_u_h((v8i16) dst4, 2);
    out2 = __msa_copy_u_w((v4i32) dst5, 0);
    out3 = __msa_copy_u_h((v8i16) dst5, 2);

    SW(out0, (src - 3));
    SH(out1, (src + 1));
    src += stride;
    SW(out2, (src - 3));
    SH(out3, (src + 1));
    src += stride;

    out0 = __msa_copy_u_w((v4i32) dst2_y, 0);
    out1 = __msa_copy_u_h((v8i16) dst2_y, 2);
    out2 = __msa_copy_u_w((v4i32) dst3_y, 0);
    out3 = __msa_copy_u_h((v8i16) dst3_y, 2);

    SW(out0, (src - 3));
    SH(out1, (src + 1));
    src += stride;
    SW(out2, (src - 3));
    SH(out3, (src + 1));
}