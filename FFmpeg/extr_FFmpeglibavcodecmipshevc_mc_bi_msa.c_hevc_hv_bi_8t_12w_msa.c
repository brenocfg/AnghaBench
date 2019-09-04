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
typedef  scalar_t__ v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  const int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDS_SH2_SH (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  CLIP_SH2_0_255_MAX_SATU (int,int) ; 
 int CLIP_SH_0_255_MAX_SATU (int) ; 
 int HEVC_FILT_8TAP (int,int,int,int,int,int,int,int) ; 
 int HEVC_FILT_8TAP_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (int,int,int,int) ; 
 int /*<<< orphan*/  INSERT_D2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LD2 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB7 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_H2_SH (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_H4_SH (int,int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_W4_SH (int,int,int,int,int) ; 
 int /*<<< orphan*/  SRARI_H2_SH (int,int,int) ; 
 int /*<<< orphan*/  SRA_4V (int,int,int,int,int) ; 
 int /*<<< orphan*/  ST4x4_UB (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST8x1_UB (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNPCK_R_SB_SH (int,int) ; 
 int /*<<< orphan*/  VSHF_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B7_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int __msa_ilvr_h (int,int) ; 
 int __msa_ldi_h (int) ; 
 scalar_t__ __msa_pckev_b (scalar_t__,scalar_t__) ; 
 int __msa_pckev_h (int,int) ; 
 scalar_t__ __msa_splati_d (int /*<<< orphan*/ ,int) ; 
 int __msa_srari_h (int,int) ; 
 scalar_t__ __msa_xori_b (scalar_t__,int) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hv_bi_8t_12w_msa(uint8_t *src0_ptr,
                                  int32_t src_stride,
                                  int16_t *src1_ptr,
                                  int32_t src2_stride,
                                  uint8_t *dst,
                                  int32_t dst_stride,
                                  const int8_t *filter_x,
                                  const int8_t *filter_y,
                                  int32_t height)
{
    uint32_t loop_cnt;
    uint8_t *src0_ptr_tmp, *dst_tmp;
    int16_t *src1_ptr_tmp;
    uint64_t tp0, tp1;
    v16u8 out;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v16i8 mask0, mask1, mask2, mask3, mask4, mask5, mask6, mask7;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v16i8 vec8, vec9, vec10, vec11, vec12, vec13, vec14, vec15;
    v8i16 in0, in1 = { 0 }, out0, out1, tmp, filter_vec, const_vec;
    v8i16 filt0, filt1, filt2, filt3, filt_h0, filt_h1, filt_h2, filt_h3;
    v8i16 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;
    v8i16 dst30, dst41, dst52, dst63, dst66, dst97, dst108;
    v8i16 dst10, dst32, dst54, dst76, dst98, dst21, dst43, dst65, dst87, dst109;
    v8i16 dst10_r, dst32_r, dst54_r, dst76_r;
    v8i16 dst10_l, dst32_l, dst54_l, dst76_l;
    v4i32 dst0_r, dst0_l, tmp0, tmp1, tmp2, tmp3;

    src0_ptr -= ((3 * src_stride) + 3);

    const_vec = __msa_ldi_h(128);
    const_vec <<= 6;

    filter_vec = LD_SH(filter_x);
    SPLATI_H4_SH(filter_vec, 0, 1, 2, 3, filt0, filt1, filt2, filt3);

    filter_vec = LD_SH(filter_y);
    UNPCK_R_SB_SH(filter_vec, filter_vec);

    SPLATI_W4_SH(filter_vec, filt_h0, filt_h1, filt_h2, filt_h3);

    mask0 = LD_SB(ff_hevc_mask_arr);
    mask1 = mask0 + 2;
    mask2 = mask0 + 4;
    mask3 = mask0 + 6;

    src0_ptr_tmp = src0_ptr;
    dst_tmp = dst;
    src1_ptr_tmp = src1_ptr;

    LD_SB7(src0_ptr_tmp, src_stride, src0, src1, src2, src3, src4, src5,
           src6);
    src0_ptr_tmp += (7 * src_stride);
    XORI_B7_128_SB(src0, src1, src2, src3, src4, src5, src6);

    /* row 0 row 1 row 2 row 3 */
    VSHF_B4_SB(src0, src0, mask0, mask1, mask2, mask3, vec0, vec1, vec2,
               vec3);
    VSHF_B4_SB(src1, src1, mask0, mask1, mask2, mask3, vec4, vec5, vec6,
               vec7);
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
    VSHF_B4_SB(src4, src4, mask0, mask1, mask2, mask3, vec0, vec1, vec2,
               vec3);
    VSHF_B4_SB(src5, src5, mask0, mask1, mask2, mask3, vec4, vec5, vec6,
               vec7);
    VSHF_B4_SB(src6, src6, mask0, mask1, mask2, mask3, vec8, vec9, vec10,
               vec11);
    dst4 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                             filt3);
    dst5 = HEVC_FILT_8TAP_SH(vec4, vec5, vec6, vec7, filt0, filt1, filt2,
                             filt3);
    dst6 = HEVC_FILT_8TAP_SH(vec8, vec9, vec10, vec11, filt0, filt1, filt2,
                             filt3);

    for (loop_cnt = 16; loop_cnt--;) {
        src7 = LD_SB(src0_ptr_tmp);
        src7 = (v16i8) __msa_xori_b((v16u8) src7, 128);
        src0_ptr_tmp += src_stride;

        in0 = LD_SH(src1_ptr_tmp);
        src1_ptr_tmp += src2_stride;

        VSHF_B4_SB(src7, src7, mask0, mask1, mask2, mask3, vec0, vec1, vec2,
                   vec3);
        dst7 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1,
                                 filt2, filt3);
        ILVRL_H2_SH(dst1, dst0, dst10_r, dst10_l);
        ILVRL_H2_SH(dst3, dst2, dst32_r, dst32_l);
        ILVRL_H2_SH(dst5, dst4, dst54_r, dst54_l);
        ILVRL_H2_SH(dst7, dst6, dst76_r, dst76_l);
        dst0_r = HEVC_FILT_8TAP(dst10_r, dst32_r, dst54_r, dst76_r, filt_h0,
                                filt_h1, filt_h2, filt_h3);
        dst0_l = HEVC_FILT_8TAP(dst10_l, dst32_l, dst54_l, dst76_l, filt_h0,
                                filt_h1, filt_h2, filt_h3);
        dst0_r >>= 6;
        dst0_l >>= 6;

        tmp = __msa_pckev_h((v8i16) dst0_l, (v8i16) dst0_r);
        ADDS_SH2_SH(tmp, in0, tmp, const_vec, tmp, tmp);
        tmp = __msa_srari_h(tmp, 7);
        tmp = CLIP_SH_0_255_MAX_SATU(tmp);
        out = (v16u8) __msa_pckev_b((v16i8) tmp, (v16i8) tmp);
        ST8x1_UB(out, dst_tmp);
        dst_tmp += dst_stride;

        dst0 = dst1;
        dst1 = dst2;
        dst2 = dst3;
        dst3 = dst4;
        dst4 = dst5;
        dst5 = dst6;
        dst6 = dst7;
    }

    src0_ptr += 8;
    dst += 8;
    src1_ptr += 8;

    mask4 = LD_SB(ff_hevc_mask_arr + 16);
    mask5 = mask4 + 2;
    mask6 = mask4 + 4;
    mask7 = mask4 + 6;

    LD_SB7(src0_ptr, src_stride, src0, src1, src2, src3, src4, src5, src6);
    src0_ptr += (7 * src_stride);
    XORI_B7_128_SB(src0, src1, src2, src3, src4, src5, src6);

    /* row 0 row 1 row 2 row 3 */
    VSHF_B4_SB(src0, src3, mask4, mask5, mask6, mask7, vec0, vec1, vec2, vec3);
    VSHF_B4_SB(src1, src4, mask4, mask5, mask6, mask7, vec4, vec5, vec6, vec7);
    VSHF_B4_SB(src2, src5, mask4, mask5, mask6, mask7,
               vec8, vec9, vec10, vec11);
    VSHF_B4_SB(src3, src6, mask4, mask5, mask6, mask7,
               vec12, vec13, vec14, vec15);
    dst30 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                              filt3);
    dst41 = HEVC_FILT_8TAP_SH(vec4, vec5, vec6, vec7, filt0, filt1, filt2,
                              filt3);
    dst52 = HEVC_FILT_8TAP_SH(vec8, vec9, vec10, vec11, filt0, filt1, filt2,
                              filt3);
    dst63 = HEVC_FILT_8TAP_SH(vec12, vec13, vec14, vec15, filt0, filt1, filt2,
                              filt3);

    ILVRL_H2_SH(dst41, dst30, dst10, dst43);
    ILVRL_H2_SH(dst52, dst41, dst21, dst54);
    ILVRL_H2_SH(dst63, dst52, dst32, dst65);

    dst66 = (v8i16) __msa_splati_d((v2i64) dst63, 1);

    for (loop_cnt = 4; loop_cnt--;) {
        LD_SB4(src0_ptr, src_stride, src7, src8, src9, src10);
        src0_ptr += (4 * src_stride);
        XORI_B4_128_SB(src7, src8, src9, src10);

        LD2(src1_ptr, src2_stride, tp0, tp1);
        INSERT_D2_SH(tp0, tp1, in0);
        src1_ptr += (2 * src2_stride);
        LD2(src1_ptr, src2_stride, tp0, tp1);
        INSERT_D2_SH(tp0, tp1, in1);
        src1_ptr += (2 * src2_stride);

        VSHF_B4_SB(src7, src9, mask4, mask5, mask6, mask7, vec0, vec1, vec2,
                   vec3);
        VSHF_B4_SB(src8, src10, mask4, mask5, mask6, mask7, vec4, vec5, vec6,
                   vec7);
        dst97 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                  filt3);
        dst108 = HEVC_FILT_8TAP_SH(vec4, vec5, vec6, vec7, filt0, filt1, filt2,
                                   filt3);

        dst76 = __msa_ilvr_h(dst97, dst66);
        ILVRL_H2_SH(dst108, dst97, dst87, dst109);
        dst66 = (v8i16) __msa_splati_d((v2i64) dst97, 1);
        dst98 = __msa_ilvr_h(dst66, dst108);

        tmp0 = HEVC_FILT_8TAP(dst10, dst32, dst54, dst76, filt_h0, filt_h1,
                              filt_h2, filt_h3);
        tmp1 = HEVC_FILT_8TAP(dst21, dst43, dst65, dst87, filt_h0, filt_h1,
                              filt_h2, filt_h3);
        tmp2 = HEVC_FILT_8TAP(dst32, dst54, dst76, dst98, filt_h0, filt_h1,
                              filt_h2, filt_h3);
        tmp3 = HEVC_FILT_8TAP(dst43, dst65, dst87, dst109, filt_h0, filt_h1,
                              filt_h2, filt_h3);
        SRA_4V(tmp0, tmp1, tmp2, tmp3, 6);
        PCKEV_H2_SH(tmp1, tmp0, tmp3, tmp2, out0, out1);
        ADDS_SH2_SH(out0, in0, out1, in1, out0, out1);
        ADDS_SH2_SH(out0, const_vec, out1, const_vec, out0, out1);
        SRARI_H2_SH(out0, out1, 7);
        CLIP_SH2_0_255_MAX_SATU(out0, out1);
        out = (v16u8) __msa_pckev_b((v16i8) out1, (v16i8) out0);
        ST4x4_UB(out, out, 0, 1, 2, 3, dst, dst_stride);
        dst += (4 * dst_stride);

        dst10 = dst54;
        dst32 = dst76;
        dst54 = dst98;
        dst21 = dst65;
        dst43 = dst87;
        dst65 = dst109;
        dst66 = (v8i16) __msa_splati_d((v2i64) dst108, 1);
    }
}