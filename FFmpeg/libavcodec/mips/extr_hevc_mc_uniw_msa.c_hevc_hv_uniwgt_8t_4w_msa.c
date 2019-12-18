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
typedef  scalar_t__ v4i32 ;
typedef  int /*<<< orphan*/  v2i64 ;
typedef  scalar_t__ v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  CLIP_SW4_0_255 (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HEVC_FILT_8TAP (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HEVC_FILT_8TAP_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SB (scalar_t__) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB7 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  MUL2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_H2_SW (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_H4_SH (scalar_t__,int /*<<< orphan*/ ,int,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_W4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRAR_W4_SW (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRA_4V (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ST_W4 (scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UNPCK_R_SB_SH (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VSHF_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B7_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_w (int) ; 
 scalar_t__ __msa_ilvr_h (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_ldi_w (int) ; 
 scalar_t__ __msa_pckev_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_splati_d (int /*<<< orphan*/ ,int) ; 
 scalar_t__ __msa_srar_w (scalar_t__,scalar_t__) ; 
 scalar_t__ ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hv_uniwgt_8t_4w_msa(uint8_t *src,
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
    v16u8 out;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v8i16 filt0, filt1, filt2, filt3;
    v8i16 filt_h0, filt_h1, filt_h2, filt_h3;
    v16i8 mask1, mask2, mask3;
    v8i16 filter_vec;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v16i8 vec8, vec9, vec10, vec11, vec12, vec13, vec14, vec15;
    v8i16 dst30, dst41, dst52, dst63, dst66, dst97, dst108;
    v8i16 dst10_r, dst32_r, dst54_r, dst76_r, dst98_r;
    v8i16 dst21_r, dst43_r, dst65_r, dst87_r, dst109_r;
    v4i32 dst0_r, dst1_r, dst2_r, dst3_r;
    v4i32 weight_vec, offset_vec, rnd_vec, const_128, denom_vec;
    v16i8 mask0 = LD_SB(ff_hevc_mask_arr + 16);

    src -= ((3 * src_stride) + 3);
    filter_vec = LD_SH(filter_x);
    SPLATI_H4_SH(filter_vec, 0, 1, 2, 3, filt0, filt1, filt2, filt3);

    filter_vec = LD_SH(filter_y);
    UNPCK_R_SB_SH(filter_vec, filter_vec);

    SPLATI_W4_SH(filter_vec, filt_h0, filt_h1, filt_h2, filt_h3);

    mask1 = mask0 + 2;
    mask2 = mask0 + 4;
    mask3 = mask0 + 6;

    weight_vec = __msa_fill_w(weight);
    offset_vec = __msa_fill_w(offset);
    rnd_vec = __msa_fill_w(rnd_val);
    denom_vec = rnd_vec - 6;

    const_128 = __msa_ldi_w(128);
    const_128 *= weight_vec;
    offset_vec += __msa_srar_w(const_128, denom_vec);

    LD_SB7(src, src_stride, src0, src1, src2, src3, src4, src5, src6);
    src += (7 * src_stride);
    XORI_B7_128_SB(src0, src1, src2, src3, src4, src5, src6);

    /* row 0 row 1 row 2 row 3 */
    VSHF_B4_SB(src0, src3, mask0, mask1, mask2, mask3, vec0, vec1, vec2, vec3);
    VSHF_B4_SB(src1, src4, mask0, mask1, mask2, mask3, vec4, vec5, vec6, vec7);
    VSHF_B4_SB(src2, src5, mask0, mask1, mask2, mask3,
               vec8, vec9, vec10, vec11);
    VSHF_B4_SB(src3, src6, mask0, mask1, mask2, mask3,
               vec12, vec13, vec14, vec15);
    dst30 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                              filt3);
    dst41 = HEVC_FILT_8TAP_SH(vec4, vec5, vec6, vec7, filt0, filt1, filt2,
                              filt3);
    dst52 = HEVC_FILT_8TAP_SH(vec8, vec9, vec10, vec11, filt0, filt1, filt2,
                              filt3);
    dst63 = HEVC_FILT_8TAP_SH(vec12, vec13, vec14, vec15, filt0, filt1, filt2,
                              filt3);

    ILVRL_H2_SH(dst41, dst30, dst10_r, dst43_r);
    ILVRL_H2_SH(dst52, dst41, dst21_r, dst54_r);
    ILVRL_H2_SH(dst63, dst52, dst32_r, dst65_r);

    dst66 = (v8i16) __msa_splati_d((v2i64) dst63, 1);

    for (loop_cnt = height >> 2; loop_cnt--;) {
        LD_SB4(src, src_stride, src7, src8, src9, src10);
        src += (4 * src_stride);
        XORI_B4_128_SB(src7, src8, src9, src10);

        VSHF_B4_SB(src7, src9, mask0, mask1, mask2, mask3,
                   vec0, vec1, vec2, vec3);
        VSHF_B4_SB(src8, src10, mask0, mask1, mask2, mask3,
                   vec4, vec5, vec6, vec7);
        dst97 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                  filt3);
        dst108 = HEVC_FILT_8TAP_SH(vec4, vec5, vec6, vec7, filt0, filt1, filt2,
                                   filt3);

        dst76_r = __msa_ilvr_h(dst97, dst66);
        ILVRL_H2_SH(dst108, dst97, dst87_r, dst109_r);
        dst66 = (v8i16) __msa_splati_d((v2i64) dst97, 1);
        dst98_r = __msa_ilvr_h(dst66, dst108);

        dst0_r = HEVC_FILT_8TAP(dst10_r, dst32_r, dst54_r, dst76_r, filt_h0,
                                filt_h1, filt_h2, filt_h3);
        dst1_r = HEVC_FILT_8TAP(dst21_r, dst43_r, dst65_r, dst87_r, filt_h0,
                                filt_h1, filt_h2, filt_h3);
        dst2_r = HEVC_FILT_8TAP(dst32_r, dst54_r, dst76_r, dst98_r, filt_h0,
                                filt_h1, filt_h2, filt_h3);
        dst3_r = HEVC_FILT_8TAP(dst43_r, dst65_r, dst87_r, dst109_r, filt_h0,
                                filt_h1, filt_h2, filt_h3);

        SRA_4V(dst0_r, dst1_r, dst2_r, dst3_r, 6);
        MUL2(dst0_r, weight_vec, dst1_r, weight_vec, dst0_r, dst1_r);
        MUL2(dst2_r, weight_vec, dst3_r, weight_vec, dst2_r, dst3_r);
        SRAR_W4_SW(dst0_r, dst1_r, dst2_r, dst3_r, rnd_vec);
        ADD2(dst0_r, offset_vec, dst1_r, offset_vec, dst0_r, dst1_r);
        ADD2(dst2_r, offset_vec, dst3_r, offset_vec, dst2_r, dst3_r);
        CLIP_SW4_0_255(dst0_r, dst1_r, dst2_r, dst3_r);
        PCKEV_H2_SW(dst1_r, dst0_r, dst3_r, dst2_r, dst0_r, dst1_r);
        out = (v16u8) __msa_pckev_b((v16i8) dst1_r, (v16i8) dst0_r);
        ST_W4(out, 0, 1, 2, 3, dst, dst_stride);
        dst += (4 * dst_stride);

        dst10_r = dst54_r;
        dst32_r = dst76_r;
        dst54_r = dst98_r;
        dst21_r = dst65_r;
        dst43_r = dst87_r;
        dst65_r = dst109_r;
        dst66 = (v8i16) __msa_splati_d((v2i64) dst108, 1);
    }
}