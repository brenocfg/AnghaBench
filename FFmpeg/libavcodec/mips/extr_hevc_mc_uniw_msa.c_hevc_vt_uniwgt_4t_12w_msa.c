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
typedef  int /*<<< orphan*/  v4i32 ;
typedef  int /*<<< orphan*/  v2i64 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_FILT_4TAP_SH (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEVC_UNIW_RND_CLIP2_MAX_SATU_H (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEVC_UNIW_RND_CLIP4_MAX_SATU_H (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVL_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVRL_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_B3_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_D4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_W4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __msa_adds_s_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_fill_h (int) ; 
 int /*<<< orphan*/  __msa_fill_w (int) ; 
 scalar_t__ __msa_ilvr_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_srar_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hevc_vt_uniwgt_4t_12w_msa(uint8_t *src,
                                      int32_t src_stride,
                                      uint8_t *dst,
                                      int32_t dst_stride,
                                      const int8_t *filter,
                                      int32_t height,
                                      int32_t weight,
                                      int32_t offset,
                                      int32_t rnd_val)
{
    int32_t loop_cnt;
    v16u8 out0, out1, out2, out3, out4, out5;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v16i8 src10_r, src32_r, src21_r, src43_r;
    v16i8 src10_l, src32_l, src54_l, src21_l, src43_l, src65_l;
    v16i8 src2110, src4332;
    v16i8 src54_r, src76_r, src98_r, src65_r, src87_r, src109_r;
    v16i8 src76_l, src98_l, src87_l, src109_l, src6554, src8776, src10998;
    v8i16 filt0, filt1;
    v8i16 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7, dst8;
    v8i16 dst9, dst10, dst11, filter_vec, weight_vec_h, offset_vec, denom_vec;
    v4i32 weight_vec, rnd_vec;

    src -= (1 * src_stride);

    weight = weight & 0x0000FFFF;

    weight_vec = __msa_fill_w(weight);
    rnd_vec = __msa_fill_w(rnd_val);

    weight *= 128;
    rnd_val -= 6;

    weight_vec_h = __msa_fill_h(weight);
    offset_vec = __msa_fill_h(offset);
    denom_vec = __msa_fill_h(rnd_val);

    weight_vec_h = __msa_srar_h(weight_vec_h, denom_vec);
    offset_vec = __msa_adds_s_h(offset_vec, weight_vec_h);

    filter_vec = LD_SH(filter);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    LD_SB3(src, src_stride, src0, src1, src2);
    src += (3 * src_stride);
    XORI_B3_128_SB(src0, src1, src2);
    ILVR_B2_SB(src1, src0, src2, src1, src10_r, src21_r);
    ILVL_B2_SB(src1, src0, src2, src1, src10_l, src21_l);
    src2110 = (v16i8) __msa_ilvr_d((v2i64) src21_l, (v2i64) src10_l);

    for (loop_cnt = 2; loop_cnt--;) {
        LD_SB8(src, src_stride, src3, src4, src5, src6, src7, src8, src9, src10);
        src += (8 * src_stride);
        XORI_B8_128_SB(src3, src4, src5, src6, src7, src8, src9, src10);
        ILVRL_B2_SB(src3, src2, src32_r, src32_l);
        ILVRL_B2_SB(src4, src3, src43_r, src43_l);
        ILVRL_B2_SB(src5, src4, src54_r, src54_l);
        ILVRL_B2_SB(src6, src5, src65_r, src65_l);
        src4332 = (v16i8) __msa_ilvr_d((v2i64) src43_l, (v2i64) src32_l);
        src6554 = (v16i8) __msa_ilvr_d((v2i64) src65_l, (v2i64) src54_l);
        dst0 = HEVC_FILT_4TAP_SH(src10_r, src32_r, filt0, filt1);
        dst1 = HEVC_FILT_4TAP_SH(src21_r, src43_r, filt0, filt1);
        dst2 = HEVC_FILT_4TAP_SH(src32_r, src54_r, filt0, filt1);
        dst3 = HEVC_FILT_4TAP_SH(src43_r, src65_r, filt0, filt1);
        dst4 = HEVC_FILT_4TAP_SH(src2110, src4332, filt0, filt1);
        dst5 = HEVC_FILT_4TAP_SH(src4332, src6554, filt0, filt1);
        HEVC_UNIW_RND_CLIP4_MAX_SATU_H(dst0, dst1, dst2, dst3, weight_vec,
                                       offset_vec, rnd_vec, dst0, dst1, dst2,
                                       dst3);
        HEVC_UNIW_RND_CLIP2_MAX_SATU_H(dst4, dst5, weight_vec, offset_vec,
                                       rnd_vec, dst4, dst5);
        PCKEV_B3_UB(dst1, dst0, dst3, dst2, dst5, dst4, out0, out1, out2);
        ST_D4(out0, out1, 0, 1, 0, 1, dst, dst_stride);
        ST_W4(out2, 0, 1, 2, 3, dst + 8, dst_stride);
        dst += (4 * dst_stride);

        ILVRL_B2_SB(src7, src6, src76_r, src76_l);
        ILVRL_B2_SB(src8, src7, src87_r, src87_l);
        ILVRL_B2_SB(src9, src8, src98_r, src98_l);
        ILVRL_B2_SB(src10, src9, src109_r, src109_l);
        src8776 = (v16i8) __msa_ilvr_d((v2i64) src87_l, (v2i64) src76_l);
        src10998 = (v16i8) __msa_ilvr_d((v2i64) src109_l, (v2i64) src98_l);
        dst6 = HEVC_FILT_4TAP_SH(src54_r, src76_r, filt0, filt1);
        dst7 = HEVC_FILT_4TAP_SH(src65_r, src87_r, filt0, filt1);
        dst8 = HEVC_FILT_4TAP_SH(src76_r, src98_r, filt0, filt1);
        dst9 = HEVC_FILT_4TAP_SH(src87_r, src109_r, filt0, filt1);
        dst10 = HEVC_FILT_4TAP_SH(src6554, src8776, filt0, filt1);
        dst11 = HEVC_FILT_4TAP_SH(src8776, src10998, filt0, filt1);
        HEVC_UNIW_RND_CLIP4_MAX_SATU_H(dst6, dst7, dst8, dst9, weight_vec,
                                       offset_vec, rnd_vec, dst6, dst7, dst8,
                                       dst9);
        HEVC_UNIW_RND_CLIP2_MAX_SATU_H(dst10, dst11, weight_vec, offset_vec,
                                       rnd_vec, dst10, dst11);
        PCKEV_B3_UB(dst7, dst6, dst9, dst8, dst11, dst10, out3, out4, out5);
        ST_D4(out3, out4, 0, 1, 0, 1, dst, dst_stride);
        ST_W4(out5, 0, 1, 2, 3, dst + 8, dst_stride);
        dst += (4 * dst_stride);

        src2 = src10;
        src10_r = src98_r;
        src21_r = src109_r;
        src2110 = src10998;
    }
}