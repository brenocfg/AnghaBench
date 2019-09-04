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
typedef  int v8i16 ;
typedef  int v4i32 ;
typedef  int /*<<< orphan*/  v2i64 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int HEVC_FILT_8TAP (int,int,int,int,int,int,int,int) ; 
 int HEVC_FILT_8TAP_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  ILVL_H2_SH (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ILVL_H4_SH (int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (int,int,int,int) ; 
 int /*<<< orphan*/  ILVR_H2_SH (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ILVR_H4_SH (int,int,int,int,int,int,int,int,int,int,int,int) ; 
 scalar_t__ LD_SB (scalar_t__) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB7 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_H2_SH (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_H2_SW (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_XORI128_UB (int,int) ; 
 int /*<<< orphan*/  SAT_SW4_SW (int,int,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_H4_SH (int,int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_W4_SH (int,int,int,int,int) ; 
 int /*<<< orphan*/  SRARI_W4_SW (int,int,int,int,int) ; 
 int /*<<< orphan*/  SRA_4V (int,int,int,int,int) ; 
 int /*<<< orphan*/  ST4x4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST8x2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UNPCK_R_SB_SH (int,int) ; 
 int /*<<< orphan*/  VSHF_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B2_128_SB (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B7_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int __msa_ilvr_h (int,int) ; 
 scalar_t__ __msa_splati_d (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hv_uni_8t_12w_msa(uint8_t *src,
                                   int32_t src_stride,
                                   uint8_t *dst,
                                   int32_t dst_stride,
                                   const int8_t *filter_x,
                                   const int8_t *filter_y,
                                   int32_t height)
{
    uint32_t loop_cnt;
    uint8_t *src_tmp, *dst_tmp;
    v16u8 out0, out1;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v16i8 src11, src12, src13, src14;
    v16i8 mask0, mask1, mask2, mask3, mask4, mask5, mask6, mask7;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v16i8 vec8, vec9, vec10, vec11, vec12, vec13, vec14, vec15;
    v8i16 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7, dst8;
    v8i16 dst30, dst41, dst52, dst63, dst66, dst117, dst128, dst139, dst1410;
    v8i16 filt0, filt1, filt2, filt3, filt_h0, filt_h1, filt_h2, filt_h3;
    v8i16 dst10_r, dst32_r, dst54_r, dst76_r, dst21_r, dst43_r, dst65_r;
    v8i16 dst10_l, dst32_l, dst54_l, dst76_l, dst21_l, dst43_l, dst65_l;
    v8i16 dst87_r, dst98_r, dst1110_r, dst1312_r, dst109_r, dst1211_r;
    v8i16 dst1413_r, dst87_l, filter_vec;
    v4i32 dst0_r, dst1_r, dst2_r, dst3_r, dst4_r, dst5_r, dst6_r, dst7_r;
    v4i32 dst0_l, dst1_l;

    src -= ((3 * src_stride) + 3);

    filter_vec = LD_SH(filter_x);
    SPLATI_H4_SH(filter_vec, 0, 1, 2, 3, filt0, filt1, filt2, filt3);

    filter_vec = LD_SH(filter_y);
    UNPCK_R_SB_SH(filter_vec, filter_vec);

    SPLATI_W4_SH(filter_vec, filt_h0, filt_h1, filt_h2, filt_h3);

    mask0 = LD_SB(ff_hevc_mask_arr);
    mask1 = mask0 + 2;
    mask2 = mask0 + 4;
    mask3 = mask0 + 6;

    src_tmp = src;
    dst_tmp = dst;

    LD_SB7(src_tmp, src_stride, src0, src1, src2, src3, src4, src5, src6);
    src_tmp += (7 * src_stride);
    XORI_B7_128_SB(src0, src1, src2, src3, src4, src5, src6);

    /* row 0 row 1 row 2 row 3 */
    VSHF_B4_SB(src0, src0, mask0, mask1, mask2, mask3, vec0, vec1, vec2, vec3);
    VSHF_B4_SB(src1, src1, mask0, mask1, mask2, mask3, vec4, vec5, vec6, vec7);
    VSHF_B4_SB(src2, src2, mask0, mask1, mask2, mask3, vec8, vec9, vec10,
               vec11);
    VSHF_B4_SB(src3, src3, mask0, mask1, mask2, mask3, vec12, vec13, vec14,
               vec15);
    dst0 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                             filt3);
    dst1 = HEVC_FILT_8TAP_SH(vec4, vec5, vec6, vec7, filt0, filt1, filt2,
                             filt3);
    dst2 = HEVC_FILT_8TAP_SH(vec8, vec9, vec10, vec11, filt0, filt1, filt2,
                             filt3);
    dst3 = HEVC_FILT_8TAP_SH(vec12, vec13, vec14, vec15, filt0, filt1,
                             filt2, filt3);

    VSHF_B4_SB(src4, src4, mask0, mask1, mask2, mask3, vec0, vec1, vec2, vec3);
    VSHF_B4_SB(src5, src5, mask0, mask1, mask2, mask3, vec4, vec5, vec6, vec7);
    VSHF_B4_SB(src6, src6, mask0, mask1, mask2, mask3, vec8, vec9, vec10,
               vec11);
    dst4 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                             filt3);
    dst5 = HEVC_FILT_8TAP_SH(vec4, vec5, vec6, vec7, filt0, filt1, filt2,
                             filt3);
    dst6 = HEVC_FILT_8TAP_SH(vec8, vec9, vec10, vec11, filt0, filt1, filt2,
                             filt3);

    for (loop_cnt = 8; loop_cnt--;) {
        LD_SB2(src_tmp, src_stride, src7, src8);
        XORI_B2_128_SB(src7, src8);
        src_tmp += 2 * src_stride;

        ILVR_H4_SH(dst1, dst0, dst3, dst2, dst5, dst4, dst2, dst1, dst10_r,
                   dst32_r, dst54_r, dst21_r);
        ILVL_H4_SH(dst1, dst0, dst3, dst2, dst5, dst4, dst2, dst1, dst10_l,
                   dst32_l, dst54_l, dst21_l);
        ILVR_H2_SH(dst4, dst3, dst6, dst5, dst43_r, dst65_r);
        ILVL_H2_SH(dst4, dst3, dst6, dst5, dst43_l, dst65_l);

        VSHF_B4_SB(src7, src7, mask0, mask1, mask2, mask3, vec0, vec1, vec2,
                   vec3);
        dst7 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                 filt3);

        ILVRL_H2_SH(dst7, dst6, dst76_r, dst76_l);
        dst0_r = HEVC_FILT_8TAP(dst10_r, dst32_r, dst54_r, dst76_r,
                                filt_h0, filt_h1, filt_h2, filt_h3);
        dst0_l = HEVC_FILT_8TAP(dst10_l, dst32_l, dst54_l, dst76_l,
                                filt_h0, filt_h1, filt_h2, filt_h3);
        dst0_r >>= 6;
        dst0_l >>= 6;

        VSHF_B4_SB(src8, src8, mask0, mask1, mask2, mask3, vec0, vec1, vec2,
                   vec3);
        dst8 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                 filt3);

        ILVRL_H2_SH(dst8, dst7, dst87_r, dst87_l);
        dst1_r = HEVC_FILT_8TAP(dst21_r, dst43_r, dst65_r, dst87_r,
                                filt_h0, filt_h1, filt_h2, filt_h3);
        dst1_l = HEVC_FILT_8TAP(dst21_l, dst43_l, dst65_l, dst87_l,
                                filt_h0, filt_h1, filt_h2, filt_h3);
        dst1_r >>= 6;
        dst1_l >>= 6;
        SRARI_W4_SW(dst0_r, dst0_l, dst1_r, dst1_l, 6);
        SAT_SW4_SW(dst0_r, dst0_l, dst1_r, dst1_l, 7);

        PCKEV_H2_SH(dst0_l, dst0_r, dst1_l, dst1_r, dst0, dst1);
        out0 = PCKEV_XORI128_UB(dst0, dst1);
        ST8x2_UB(out0, dst_tmp, dst_stride);
        dst_tmp += (2 * dst_stride);

        dst0 = dst2;
        dst1 = dst3;
        dst2 = dst4;
        dst3 = dst5;
        dst4 = dst6;
        dst5 = dst7;
        dst6 = dst8;
    }

    src += 8;
    dst += 8;

    mask4 = LD_SB(ff_hevc_mask_arr + 16);
    mask5 = mask4 + 2;
    mask6 = mask4 + 4;
    mask7 = mask4 + 6;

    LD_SB7(src, src_stride, src0, src1, src2, src3, src4, src5, src6);
    src += (7 * src_stride);
    XORI_B7_128_SB(src0, src1, src2, src3, src4, src5, src6);

    VSHF_B4_SB(src0, src3, mask4, mask5, mask6, mask7, vec0, vec1, vec2, vec3);
    VSHF_B4_SB(src1, src4, mask4, mask5, mask6, mask7, vec4, vec5, vec6, vec7);
    VSHF_B4_SB(src2, src5, mask4, mask5, mask6, mask7, vec8, vec9, vec10,
               vec11);
    VSHF_B4_SB(src3, src6, mask4, mask5, mask6, mask7, vec12, vec13, vec14,
               vec15);

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

    for (loop_cnt = 2; loop_cnt--;) {
        LD_SB8(src, src_stride, src7, src8, src9, src10, src11, src12, src13,
               src14);
        src += (8 * src_stride);
        XORI_B8_128_SB(src7, src8, src9, src10, src11, src12, src13, src14);

        VSHF_B4_SB(src7, src11, mask4, mask5, mask6, mask7, vec0, vec1, vec2,
                   vec3);
        VSHF_B4_SB(src8, src12, mask4, mask5, mask6, mask7, vec4, vec5, vec6,
                   vec7);
        VSHF_B4_SB(src9, src13, mask4, mask5, mask6, mask7, vec8, vec9, vec10,
                   vec11);
        VSHF_B4_SB(src10, src14, mask4, mask5, mask6, mask7, vec12, vec13,
                   vec14, vec15);

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