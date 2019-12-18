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
typedef  scalar_t__ v8i16 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  int /*<<< orphan*/  v2i64 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CLIP_SH4_0_255 (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HEVC_FILT_4TAP (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HEVC_FILT_4TAP_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SB (scalar_t__) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MUL2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_B2_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_W2_SH (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRAR_W4_SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRA_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_D4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_W8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UNPCK_R_SB_SH (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_h (int) ; 
 int /*<<< orphan*/  __msa_fill_w (int) ; 
 scalar_t__ __msa_ilvr_h (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_splati_d (int /*<<< orphan*/ ,int) ; 
 scalar_t__ __msa_srar_h (scalar_t__,scalar_t__) ; 
 scalar_t__ ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hv_uniwgt_4t_12w_msa(uint8_t *src,
                                      int32_t src_stride,
                                      uint8_t *dst,
                                      int32_t dst_stride,
                                      const int8_t *filter_x,
                                      const int8_t *filter_y,
                                      int32_t height,
                                      int32_t weight,
                                      int32_t offset,
                                      int32_t rnd_val)
{
    uint32_t loop_cnt;
    uint8_t *src_tmp, *dst_tmp;
    v16u8 out0, out1;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v16i8 mask0, mask1, mask2, mask3;
    v8i16 filt0, filt1, filt_h0, filt_h1, filter_vec, tmp0, tmp1, tmp2, tmp3;
    v8i16 dsth0, dsth1, dsth2, dsth3, dsth4, dsth5, dsth6;
    v8i16 dst10, dst21, dst22, dst73, dst84, dst95, dst106;
    v8i16 dst76_r, dst98_r, dst87_r, dst109_r;
    v8i16 dst10_r, dst32_r, dst54_r, dst21_r, dst43_r, dst65_r;
    v8i16 dst10_l, dst32_l, dst54_l, dst21_l, dst43_l, dst65_l;
    v8i16 offset_vec, const_128, denom_vec;
    v4i32 dst0_r, dst0_l, dst1_r, dst1_l, dst2_r, dst2_l, dst3_r, dst3_l;
    v4i32 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7, weight_vec, rnd_vec;

    src -= (src_stride + 1);

    filter_vec = LD_SH(filter_x);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    filter_vec = LD_SH(filter_y);
    UNPCK_R_SB_SH(filter_vec, filter_vec);

    SPLATI_W2_SH(filter_vec, 0, filt_h0, filt_h1);

    mask0 = LD_SB(ff_hevc_mask_arr);
    mask1 = mask0 + 2;

    weight_vec = __msa_fill_w(weight);
    rnd_vec = __msa_fill_w(rnd_val);

    offset_vec = __msa_fill_h(offset);
    denom_vec = __msa_fill_h(rnd_val - 6);
    const_128 = __msa_fill_h((128 * weight));
    offset_vec += __msa_srar_h(const_128, denom_vec);

    src_tmp = src;
    dst_tmp = dst;

    LD_SB3(src_tmp, src_stride, src0, src1, src2);
    src_tmp += (3 * src_stride);
    XORI_B3_128_SB(src0, src1, src2);
    VSHF_B2_SB(src0, src0, src0, src0, mask0, mask1, vec0, vec1);
    VSHF_B2_SB(src1, src1, src1, src1, mask0, mask1, vec2, vec3);
    VSHF_B2_SB(src2, src2, src2, src2, mask0, mask1, vec4, vec5);
    dsth0 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
    dsth1 = HEVC_FILT_4TAP_SH(vec2, vec3, filt0, filt1);
    dsth2 = HEVC_FILT_4TAP_SH(vec4, vec5, filt0, filt1);
    ILVRL_H2_SH(dsth1, dsth0, dst10_r, dst10_l);
    ILVRL_H2_SH(dsth2, dsth1, dst21_r, dst21_l);

    for (loop_cnt = 4; loop_cnt--;) {
        LD_SB4(src_tmp, src_stride, src3, src4, src5, src6);
        src_tmp += (4 * src_stride);
        XORI_B4_128_SB(src3, src4, src5, src6);
        VSHF_B2_SB(src3, src3, src3, src3, mask0, mask1, vec0, vec1);
        VSHF_B2_SB(src4, src4, src4, src4, mask0, mask1, vec2, vec3);
        VSHF_B2_SB(src5, src5, src5, src5, mask0, mask1, vec4, vec5);
        VSHF_B2_SB(src6, src6, src6, src6, mask0, mask1, vec6, vec7);
        dsth3 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
        dsth4 = HEVC_FILT_4TAP_SH(vec2, vec3, filt0, filt1);
        dsth5 = HEVC_FILT_4TAP_SH(vec4, vec5, filt0, filt1);
        dsth6 = HEVC_FILT_4TAP_SH(vec6, vec7, filt0, filt1);
        ILVRL_H2_SH(dsth3, dsth2, dst32_r, dst32_l);
        ILVRL_H2_SH(dsth4, dsth3, dst43_r, dst43_l);
        ILVRL_H2_SH(dsth5, dsth4, dst54_r, dst54_l);
        ILVRL_H2_SH(dsth6, dsth5, dst65_r, dst65_l);
        dst0_r = HEVC_FILT_4TAP(dst10_r, dst32_r, filt_h0, filt_h1);
        dst0_l = HEVC_FILT_4TAP(dst10_l, dst32_l, filt_h0, filt_h1);
        dst1_r = HEVC_FILT_4TAP(dst21_r, dst43_r, filt_h0, filt_h1);
        dst1_l = HEVC_FILT_4TAP(dst21_l, dst43_l, filt_h0, filt_h1);
        dst2_r = HEVC_FILT_4TAP(dst32_r, dst54_r, filt_h0, filt_h1);
        dst2_l = HEVC_FILT_4TAP(dst32_l, dst54_l, filt_h0, filt_h1);
        dst3_r = HEVC_FILT_4TAP(dst43_r, dst65_r, filt_h0, filt_h1);
        dst3_l = HEVC_FILT_4TAP(dst43_l, dst65_l, filt_h0, filt_h1);
        SRA_4V(dst0_r, dst0_l, dst1_r, dst1_l, 6);
        SRA_4V(dst2_r, dst2_l, dst3_r, dst3_l, 6);
        MUL2(dst0_r, weight_vec, dst1_r, weight_vec, dst0_r, dst1_r);
        MUL2(dst2_r, weight_vec, dst3_r, weight_vec, dst2_r, dst3_r);
        MUL2(dst0_l, weight_vec, dst1_l, weight_vec, dst0_l, dst1_l);
        MUL2(dst2_l, weight_vec, dst3_l, weight_vec, dst2_l, dst3_l);
        SRAR_W4_SW(dst0_r, dst0_l, dst1_r, dst1_l, rnd_vec);
        SRAR_W4_SW(dst2_r, dst2_l, dst3_r, dst3_l, rnd_vec);
        PCKEV_H4_SH(dst0_l, dst0_r, dst1_l, dst1_r, dst2_l, dst2_r, dst3_l,
                    dst3_r, tmp0, tmp1, tmp2, tmp3);
        ADD2(tmp0, offset_vec, tmp1, offset_vec, tmp0, tmp1);
        ADD2(tmp2, offset_vec, tmp3, offset_vec, tmp2, tmp3);
        CLIP_SH4_0_255(tmp0, tmp1, tmp2, tmp3);
        PCKEV_B2_UB(tmp1, tmp0, tmp3, tmp2, out0, out1);
        ST_D4(out0, out1, 0, 1, 0, 1, dst_tmp, dst_stride);
        dst_tmp += (4 * dst_stride);

        dst10_r = dst54_r;
        dst10_l = dst54_l;
        dst21_r = dst65_r;
        dst21_l = dst65_l;
        dsth2 = dsth6;
    }

    src += 8;
    dst += 8;

    mask2 = LD_SB(ff_hevc_mask_arr + 16);
    mask3 = mask2 + 2;

    LD_SB3(src, src_stride, src0, src1, src2);
    src += (3 * src_stride);
    XORI_B3_128_SB(src0, src1, src2);
    VSHF_B2_SB(src0, src1, src0, src1, mask2, mask3, vec0, vec1);
    VSHF_B2_SB(src1, src2, src1, src2, mask2, mask3, vec2, vec3);
    dst10 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
    dst21 = HEVC_FILT_4TAP_SH(vec2, vec3, filt0, filt1);
    ILVRL_H2_SH(dst21, dst10, dst10_r, dst21_r);
    dst22 = (v8i16) __msa_splati_d((v2i64) dst21, 1);

    for (loop_cnt = 2; loop_cnt--;) {
        LD_SB8(src, src_stride, src3, src4, src5, src6, src7, src8, src9,
               src10);
        src += (8 * src_stride);
        XORI_B8_128_SB(src3, src4, src5, src6, src7, src8, src9, src10);
        VSHF_B2_SB(src3, src7, src3, src7, mask2, mask3, vec0, vec1);
        VSHF_B2_SB(src4, src8, src4, src8, mask2, mask3, vec2, vec3);
        VSHF_B2_SB(src5, src9, src5, src9, mask2, mask3, vec4, vec5);
        VSHF_B2_SB(src6, src10, src6, src10, mask2, mask3, vec6, vec7);
        dst73 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
        dst84 = HEVC_FILT_4TAP_SH(vec2, vec3, filt0, filt1);
        dst95 = HEVC_FILT_4TAP_SH(vec4, vec5, filt0, filt1);
        dst106 = HEVC_FILT_4TAP_SH(vec6, vec7, filt0, filt1);
        dst32_r = __msa_ilvr_h(dst73, dst22);
        ILVRL_H2_SH(dst84, dst73, dst43_r, dst87_r);
        ILVRL_H2_SH(dst95, dst84, dst54_r, dst98_r);
        ILVRL_H2_SH(dst106, dst95, dst65_r, dst109_r);
        dst22 = (v8i16) __msa_splati_d((v2i64) dst73, 1);
        dst76_r = __msa_ilvr_h(dst22, dst106);
        dst0 = HEVC_FILT_4TAP(dst10_r, dst32_r, filt_h0, filt_h1);
        dst1 = HEVC_FILT_4TAP(dst21_r, dst43_r, filt_h0, filt_h1);
        dst2 = HEVC_FILT_4TAP(dst32_r, dst54_r, filt_h0, filt_h1);
        dst3 = HEVC_FILT_4TAP(dst43_r, dst65_r, filt_h0, filt_h1);
        dst4 = HEVC_FILT_4TAP(dst54_r, dst76_r, filt_h0, filt_h1);
        dst5 = HEVC_FILT_4TAP(dst65_r, dst87_r, filt_h0, filt_h1);
        dst6 = HEVC_FILT_4TAP(dst76_r, dst98_r, filt_h0, filt_h1);
        dst7 = HEVC_FILT_4TAP(dst87_r, dst109_r, filt_h0, filt_h1);
        SRA_4V(dst0, dst1, dst2, dst3, 6);
        SRA_4V(dst4, dst5, dst6, dst7, 6);
        MUL2(dst0, weight_vec, dst1, weight_vec, dst0, dst1);
        MUL2(dst2, weight_vec, dst3, weight_vec, dst2, dst3);
        MUL2(dst4, weight_vec, dst5, weight_vec, dst4, dst5);
        MUL2(dst6, weight_vec, dst7, weight_vec, dst6, dst7);
        SRAR_W4_SW(dst0, dst1, dst2, dst3, rnd_vec);
        SRAR_W4_SW(dst4, dst5, dst6, dst7, rnd_vec);
        PCKEV_H4_SH(dst1, dst0, dst3, dst2, dst5, dst4, dst7, dst6, tmp0, tmp1,
                    tmp2, tmp3);
        ADD2(tmp0, offset_vec, tmp1, offset_vec, tmp0, tmp1);
        ADD2(tmp2, offset_vec, tmp3, offset_vec, tmp2, tmp3);
        CLIP_SH4_0_255(tmp0, tmp1, tmp2, tmp3);
        PCKEV_B2_UB(tmp1, tmp0, tmp3, tmp2, out0, out1);
        ST_W8(out0, out1, 0, 1, 2, 3, 0, 1, 2, 3, dst, dst_stride);
        dst += (8 * dst_stride);

        dst10_r = dst98_r;
        dst21_r = dst109_r;
        dst22 = (v8i16) __msa_splati_d((v2i64) dst106, 1);
    }
}