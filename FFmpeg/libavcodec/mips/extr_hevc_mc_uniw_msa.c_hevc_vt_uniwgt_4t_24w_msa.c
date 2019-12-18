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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_FILT_4TAP_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEVC_UNIW_RND_CLIP4_MAX_SATU_H (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVL_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_B2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_B4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_D4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_UB4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_adds_s_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_fill_h (int) ; 
 int /*<<< orphan*/  __msa_fill_w (int) ; 
 int /*<<< orphan*/  __msa_srar_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hevc_vt_uniwgt_4t_24w_msa(uint8_t *src,
                                      int32_t src_stride,
                                      uint8_t *dst,
                                      int32_t dst_stride,
                                      const int8_t *filter,
                                      int32_t height,
                                      int32_t weight,
                                      int32_t offset,
                                      int32_t rnd_val)
{
    uint32_t loop_cnt;
    v16u8 out0, out1, out2, out3, out4, out5;
    v16i8 src0, src1, src2, src3, src4, src5;
    v16i8 src6, src7, src8, src9, src10, src11, src12, src13;
    v16i8 src10_r, src32_r, src54_r, src21_r, src43_r, src65_r;
    v16i8 src10_l, src32_l, src54_l, src21_l, src43_l, src65_l;
    v16i8 src87_r, src98_r, src109_r, src1110_r, src1211_r, src1312_r;
    v8i16 filt0, filt1;
    v8i16 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7, dst8, dst9, dst10;
    v8i16 filter_vec, weight_vec_h, offset_vec, denom_vec, dst11;
    v4i32 weight_vec, rnd_vec;

    src -= src_stride;

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
    LD_SB3(src + 16, src_stride, src7, src8, src9);
    src += (3 * src_stride);
    XORI_B3_128_SB(src0, src1, src2);
    XORI_B3_128_SB(src7, src8, src9);
    ILVR_B2_SB(src1, src0, src2, src1, src10_r, src21_r);
    ILVL_B2_SB(src1, src0, src2, src1, src10_l, src21_l);
    ILVR_B2_SB(src8, src7, src9, src8, src87_r, src98_r);

    for (loop_cnt = 8; loop_cnt--;) {
        LD_SB4(src, src_stride, src3, src4, src5, src6);
        LD_SB4(src + 16, src_stride, src10, src11, src12, src13);
        src += (4 * src_stride);
        XORI_B4_128_SB(src3, src4, src5, src6);
        XORI_B4_128_SB(src10, src11, src12, src13);
        ILVR_B2_SB(src3, src2, src4, src3, src32_r, src43_r);
        ILVL_B2_SB(src3, src2, src4, src3, src32_l, src43_l);
        ILVRL_B2_SB(src5, src4, src54_r, src54_l);
        ILVRL_B2_SB(src6, src5, src65_r, src65_l);
        ILVR_B2_SB(src10, src9, src11, src10, src109_r, src1110_r);
        ILVR_B2_SB(src12, src11, src13, src12, src1211_r, src1312_r);
        dst0 = HEVC_FILT_4TAP_SH(src10_r, src32_r, filt0, filt1);
        dst1 = HEVC_FILT_4TAP_SH(src21_r, src43_r, filt0, filt1);
        dst2 = HEVC_FILT_4TAP_SH(src32_r, src54_r, filt0, filt1);
        dst3 = HEVC_FILT_4TAP_SH(src43_r, src65_r, filt0, filt1);
        dst4 = HEVC_FILT_4TAP_SH(src10_l, src32_l, filt0, filt1);
        dst5 = HEVC_FILT_4TAP_SH(src21_l, src43_l, filt0, filt1);
        dst6 = HEVC_FILT_4TAP_SH(src32_l, src54_l, filt0, filt1);
        dst7 = HEVC_FILT_4TAP_SH(src43_l, src65_l, filt0, filt1);
        dst8 = HEVC_FILT_4TAP_SH(src87_r, src109_r, filt0, filt1);
        dst9 = HEVC_FILT_4TAP_SH(src98_r, src1110_r, filt0, filt1);
        dst10 = HEVC_FILT_4TAP_SH(src109_r, src1211_r, filt0, filt1);
        dst11 = HEVC_FILT_4TAP_SH(src1110_r, src1312_r, filt0, filt1);
        HEVC_UNIW_RND_CLIP4_MAX_SATU_H(dst0, dst1, dst2, dst3, weight_vec,
                                       offset_vec, rnd_vec, dst0, dst1, dst2,
                                       dst3);
        HEVC_UNIW_RND_CLIP4_MAX_SATU_H(dst4, dst5, dst6, dst7, weight_vec,
                                       offset_vec, rnd_vec, dst4, dst5, dst6,
                                       dst7);
        HEVC_UNIW_RND_CLIP4_MAX_SATU_H(dst8, dst9, dst10, dst11, weight_vec,
                                       offset_vec, rnd_vec, dst8, dst9, dst10,
                                       dst11);
        PCKEV_B4_UB(dst4, dst0, dst5, dst1, dst6, dst2, dst7, dst3, out0, out1,
                    out2, out3);
        PCKEV_B2_UB(dst9, dst8, dst11, dst10, out4, out5);
        ST_UB4(out0, out1, out2, out3, dst, dst_stride);
        ST_D4(out4, out5, 0, 1, 0, 1, dst + 16, dst_stride);
        dst += (4 * dst_stride);

        src2 = src6;
        src9 = src13;
        src10_r = src54_r;
        src21_r = src65_r;
        src10_l = src54_l;
        src21_l = src65_l;
        src87_r = src1211_r;
        src98_r = src1312_r;
    }
}