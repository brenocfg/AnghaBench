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
 int /*<<< orphan*/  HEVC_FILT_8TAP (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HEVC_FILT_8TAP_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SB (scalar_t__) ; 
 int /*<<< orphan*/  LD_SB7 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_H2_SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_XORI128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_SW4_SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPLATI_H4_SH (scalar_t__,int /*<<< orphan*/ ,int,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_W4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRARI_W4_SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRA_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST4x4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UNPCK_R_SB_SH (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VSHF_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B7_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_ilvr_h (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_splati_d (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hv_uni_8t_4w_msa(uint8_t *src,
                                  int32_t src_stride,
                                  uint8_t *dst,
                                  int32_t dst_stride,
                                  const int8_t *filter_x,
                                  const int8_t *filter_y,
                                  int32_t height)
{
    uint32_t loop_cnt;
    v16u8 out0, out1;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8;
    v16i8 src9, src10, src11, src12, src13, src14;
    v8i16 filt0, filt1, filt2, filt3;
    v8i16 filt_h0, filt_h1, filt_h2, filt_h3;
    v16i8 mask1, mask2, mask3;
    v8i16 filter_vec;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v16i8 vec8, vec9, vec10, vec11, vec12, vec13, vec14, vec15;
    v8i16 dst30, dst41, dst52, dst63, dst66, dst117, dst128, dst139, dst1410;
    v8i16 dst10_r, dst32_r, dst54_r, dst76_r, dst98_r, dst1110_r, dst1312_r;
    v8i16 dst21_r, dst43_r, dst65_r, dst87_r, dst109_r, dst1211_r, dst1413_r;
    v4i32 dst0_r, dst1_r, dst2_r, dst3_r, dst4_r, dst5_r, dst6_r, dst7_r;
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

    LD_SB7(src, src_stride, src0, src1, src2, src3, src4, src5, src6);
    src += (7 * src_stride);
    XORI_B7_128_SB(src0, src1, src2, src3, src4, src5, src6);

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

    for (loop_cnt = height >> 3; loop_cnt--;) {
        LD_SB8(src, src_stride, src7, src8, src9, src10, src11, src12, src13,
               src14);
        src += (8 * src_stride);
        XORI_B8_128_SB(src7, src8, src9, src10, src11, src12, src13, src14);

        VSHF_B4_SB(src7, src11, mask0, mask1, mask2, mask3,
                   vec0, vec1, vec2, vec3);
        VSHF_B4_SB(src8, src12, mask0, mask1, mask2, mask3,
                   vec4, vec5, vec6, vec7);
        VSHF_B4_SB(src9, src13, mask0, mask1, mask2, mask3,
                   vec8, vec9, vec10, vec11);
        VSHF_B4_SB(src10, src14, mask0, mask1, mask2, mask3,
                   vec12, vec13, vec14, vec15);

        dst117 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                   filt3);
        dst128 = HEVC_FILT_8TAP_SH(vec4, vec5, vec6, vec7, filt0, filt1, filt2,
                                   filt3);
        dst139 = HEVC_FILT_8TAP_SH(vec8, vec9, vec10, vec11, filt0, filt1,
                                   filt2, filt3);
        dst1410 = HEVC_FILT_8TAP_SH(vec12, vec13, vec14, vec15, filt0, filt1,
                                   filt2, filt3);

        dst76_r = __msa_ilvr_h(dst117, dst66);
        ILVRL_H2_SH(dst128, dst117, dst87_r, dst1211_r);
        ILVRL_H2_SH(dst139, dst128, dst98_r, dst1312_r);
        ILVRL_H2_SH(dst1410, dst139, dst109_r, dst1413_r);
        dst117 = (v8i16) __msa_splati_d((v2i64) dst117, 1);
        dst1110_r = __msa_ilvr_h(dst117, dst1410);

        dst0_r = HEVC_FILT_8TAP(dst10_r, dst32_r, dst54_r, dst76_r, filt_h0,
                                filt_h1, filt_h2, filt_h3);
        dst1_r = HEVC_FILT_8TAP(dst21_r, dst43_r, dst65_r, dst87_r, filt_h0,
                                filt_h1, filt_h2, filt_h3);
        dst2_r = HEVC_FILT_8TAP(dst32_r, dst54_r, dst76_r, dst98_r, filt_h0,
                                filt_h1, filt_h2, filt_h3);
        dst3_r = HEVC_FILT_8TAP(dst43_r, dst65_r, dst87_r, dst109_r, filt_h0,
                                filt_h1, filt_h2, filt_h3);
        dst4_r = HEVC_FILT_8TAP(dst54_r, dst76_r, dst98_r, dst1110_r, filt_h0,
                                filt_h1, filt_h2, filt_h3);
        dst5_r = HEVC_FILT_8TAP(dst65_r, dst87_r, dst109_r, dst1211_r, filt_h0,
                                filt_h1, filt_h2, filt_h3);
        dst6_r = HEVC_FILT_8TAP(dst76_r, dst98_r, dst1110_r, dst1312_r, filt_h0,
                                filt_h1, filt_h2, filt_h3);
        dst7_r = HEVC_FILT_8TAP(dst87_r, dst109_r, dst1211_r, dst1413_r,
                                filt_h0, filt_h1, filt_h2, filt_h3);

        SRA_4V(dst0_r, dst1_r, dst2_r, dst3_r, 6);
        SRA_4V(dst4_r, dst5_r, dst6_r, dst7_r, 6);
        SRARI_W4_SW(dst0_r, dst1_r, dst2_r, dst3_r, 6);
        SRARI_W4_SW(dst4_r, dst5_r, dst6_r, dst7_r, 6);
        SAT_SW4_SW(dst0_r, dst1_r, dst2_r, dst3_r, 7);
        SAT_SW4_SW(dst4_r, dst5_r, dst6_r, dst7_r, 7);
        PCKEV_H2_SW(dst1_r, dst0_r, dst3_r, dst2_r, dst0_r, dst1_r);
        PCKEV_H2_SW(dst5_r, dst4_r, dst7_r, dst6_r, dst4_r, dst5_r);
        out0 = PCKEV_XORI128_UB(dst0_r, dst1_r);
        out1 = PCKEV_XORI128_UB(dst4_r, dst5_r);
        ST4x4_UB(out0, out0, 0, 1, 2, 3, dst, dst_stride);
        dst += (4 * dst_stride);
        ST4x4_UB(out1, out1, 0, 1, 2, 3, dst, dst_stride);
        dst += (4 * dst_stride);

        dst10_r = dst98_r;
        dst32_r = dst1110_r;
        dst54_r = dst1312_r;
        dst21_r = dst109_r;
        dst43_r = dst1211_r;
        dst65_r = dst1413_r;
        dst66 = (v8i16) __msa_splati_d((v2i64) dst1410, 1);
    }
}