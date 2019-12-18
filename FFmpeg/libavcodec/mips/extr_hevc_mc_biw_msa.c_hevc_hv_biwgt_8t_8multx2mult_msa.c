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
typedef  int v4i32 ;
typedef  scalar_t__ v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_SW4_0_255 (int,int,int,int) ; 
 int HEVC_FILT_8TAP (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HEVC_FILT_8TAP_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVL_H2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVL_H4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_H2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_H4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB7 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_H2_SH (int,int,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_H4_SH (scalar_t__,int /*<<< orphan*/ ,int,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_W4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRAR_W4_SW (int,int,int,int,int) ; 
 int /*<<< orphan*/  ST_D2 (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UNPCK_R_SB_SH (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VSHF_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B2_128_SB (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B7_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int __msa_dpadd_s_w (int,scalar_t__,scalar_t__) ; 
 int __msa_fill_w (int) ; 
 scalar_t__ __msa_pckev_b (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hv_biwgt_8t_8multx2mult_msa(uint8_t *src0_ptr,
                                             int32_t src_stride,
                                             int16_t *src1_ptr,
                                             int32_t src2_stride,
                                             uint8_t *dst,
                                             int32_t dst_stride,
                                             const int8_t *filter_x,
                                             const int8_t *filter_y,
                                             int32_t height,
                                             int32_t weight0,
                                             int32_t weight1,
                                             int32_t offset0,
                                             int32_t offset1,
                                             int32_t rnd_val,
                                             int32_t width8mult)
{
    uint32_t loop_cnt, cnt;
    int32_t offset, weight;
    uint8_t *src0_ptr_tmp;
    int16_t *src1_ptr_tmp;
    uint8_t *dst_tmp;
    v16u8 out;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8;
    v8i16 in0, in1;
    v8i16 filt0, filt1, filt2, filt3;
    v8i16 filt_h0, filt_h1, filt_h2, filt_h3;
    v16i8 mask0 = LD_SB(ff_hevc_mask_arr);
    v16i8 mask1, mask2, mask3;
    v8i16 filter_vec, weight_vec;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v16i8 vec8, vec9, vec10, vec11, vec12, vec13, vec14, vec15;
    v8i16 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7, dst8;
    v4i32 dst0_r, dst0_l, dst1_r, dst1_l;
    v8i16 tmp0, tmp1, tmp2, tmp3;
    v8i16 dst10_r, dst32_r, dst54_r, dst76_r;
    v8i16 dst10_l, dst32_l, dst54_l, dst76_l;
    v8i16 dst21_r, dst43_r, dst65_r, dst87_r;
    v8i16 dst21_l, dst43_l, dst65_l, dst87_l;
    v4i32 offset_vec, rnd_vec, const_vec;

    src0_ptr -= ((3 * src_stride) + 3);

    offset = (offset0 + offset1) << rnd_val;
    weight0 = weight0 & 0x0000FFFF;
    weight = weight0 | (weight1 << 16);

    const_vec = __msa_fill_w((128 * weight1));
    const_vec <<= 6;
    offset_vec = __msa_fill_w(offset);
    rnd_vec = __msa_fill_w(rnd_val + 1);
    offset_vec += const_vec;
    weight_vec = (v8i16) __msa_fill_w(weight);

    filter_vec = LD_SH(filter_x);
    SPLATI_H4_SH(filter_vec, 0, 1, 2, 3, filt0, filt1, filt2, filt3);

    filter_vec = LD_SH(filter_y);
    UNPCK_R_SB_SH(filter_vec, filter_vec);

    SPLATI_W4_SH(filter_vec, filt_h0, filt_h1, filt_h2, filt_h3);

    mask1 = mask0 + 2;
    mask2 = mask0 + 4;
    mask3 = mask0 + 6;

    for (cnt = width8mult; cnt--;) {
        src0_ptr_tmp = src0_ptr;
        src1_ptr_tmp = src1_ptr;
        dst_tmp = dst;

        LD_SB7(src0_ptr_tmp, src_stride,
               src0, src1, src2, src3, src4, src5, src6);
        src0_ptr_tmp += (7 * src_stride);

        XORI_B7_128_SB(src0, src1, src2, src3, src4, src5, src6);

        /* row 0 row 1 row 2 row 3 */
        VSHF_B4_SB(src0, src0, mask0, mask1, mask2, mask3,
                   vec0, vec1, vec2, vec3);
        VSHF_B4_SB(src1, src1, mask0, mask1, mask2, mask3,
                   vec4, vec5, vec6, vec7);
        VSHF_B4_SB(src2, src2, mask0, mask1, mask2, mask3,
                   vec8, vec9, vec10, vec11);
        VSHF_B4_SB(src3, src3, mask0, mask1, mask2, mask3,
                   vec12, vec13, vec14, vec15);

        dst0 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                 filt3);
        dst1 = HEVC_FILT_8TAP_SH(vec4, vec5, vec6, vec7, filt0, filt1, filt2,
                                 filt3);
        dst2 = HEVC_FILT_8TAP_SH(vec8, vec9, vec10, vec11, filt0, filt1, filt2,
                                 filt3);
        dst3 = HEVC_FILT_8TAP_SH(vec12, vec13, vec14, vec15, filt0, filt1,
                                 filt2, filt3);

        /* row 4 row 5 row 6 */
        VSHF_B4_SB(src4, src4, mask0, mask1, mask2, mask3,
                   vec0, vec1, vec2, vec3);
        VSHF_B4_SB(src5, src5, mask0, mask1, mask2, mask3,
                   vec4, vec5, vec6, vec7);
        VSHF_B4_SB(src6, src6, mask0, mask1, mask2, mask3,
                   vec8, vec9, vec10, vec11);

        dst4 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                 filt3);
        dst5 = HEVC_FILT_8TAP_SH(vec4, vec5, vec6, vec7, filt0, filt1, filt2,
                                 filt3);
        dst6 = HEVC_FILT_8TAP_SH(vec8, vec9, vec10, vec11, filt0, filt1, filt2,
                                 filt3);

        for (loop_cnt = height >> 1; loop_cnt--;) {
            LD_SB2(src0_ptr_tmp, src_stride, src7, src8);
            XORI_B2_128_SB(src7, src8);
            src0_ptr_tmp += 2 * src_stride;

            LD_SH2(src1_ptr_tmp, src2_stride, in0, in1);
            src1_ptr_tmp += (2 * src2_stride);

            ILVR_H4_SH(dst1, dst0, dst3, dst2, dst5, dst4, dst2, dst1, dst10_r,
                       dst32_r, dst54_r, dst21_r);
            ILVL_H4_SH(dst1, dst0, dst3, dst2, dst5, dst4, dst2, dst1, dst10_l,
                       dst32_l, dst54_l, dst21_l);
            ILVR_H2_SH(dst4, dst3, dst6, dst5, dst43_r, dst65_r);
            ILVL_H2_SH(dst4, dst3, dst6, dst5, dst43_l, dst65_l);

            VSHF_B4_SB(src7, src7, mask0, mask1, mask2, mask3,
                       vec0, vec1, vec2, vec3);
            dst7 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1,
                                     filt2, filt3);

            ILVRL_H2_SH(dst7, dst6, dst76_r, dst76_l);
            dst0_r = HEVC_FILT_8TAP(dst10_r, dst32_r, dst54_r, dst76_r,
                                    filt_h0, filt_h1, filt_h2, filt_h3);
            dst0_l = HEVC_FILT_8TAP(dst10_l, dst32_l, dst54_l, dst76_l,
                                    filt_h0, filt_h1, filt_h2, filt_h3);

            dst0_r >>= 6;
            dst0_l >>= 6;

            /* row 8 */
            VSHF_B4_SB(src8, src8, mask0, mask1, mask2, mask3,
                       vec0, vec1, vec2, vec3);
            dst8 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1,
                                     filt2, filt3);

            ILVRL_H2_SH(dst8, dst7, dst87_r, dst87_l);
            dst1_r = HEVC_FILT_8TAP(dst21_r, dst43_r, dst65_r, dst87_r,
                                    filt_h0, filt_h1, filt_h2, filt_h3);
            dst1_l = HEVC_FILT_8TAP(dst21_l, dst43_l, dst65_l, dst87_l,
                                    filt_h0, filt_h1, filt_h2, filt_h3);

            dst1_r >>= 6;
            dst1_l >>= 6;

            PCKEV_H2_SH(dst0_l, dst0_r, dst1_l, dst1_r, tmp1, tmp3);
            ILVRL_H2_SH(tmp1, in0, tmp0, tmp1);
            ILVRL_H2_SH(tmp3, in1, tmp2, tmp3);
            dst0_r = __msa_dpadd_s_w(offset_vec, tmp0, weight_vec);
            dst0_l = __msa_dpadd_s_w(offset_vec, tmp1, weight_vec);
            dst1_r = __msa_dpadd_s_w(offset_vec, tmp2, weight_vec);
            dst1_l = __msa_dpadd_s_w(offset_vec, tmp3, weight_vec);
            SRAR_W4_SW(dst0_l, dst0_r, dst1_l, dst1_r, rnd_vec);
            CLIP_SW4_0_255(dst0_l, dst0_r, dst1_l, dst1_r);
            PCKEV_H2_SH(dst0_l, dst0_r, dst1_l, dst1_r, tmp0, tmp1);
            out = (v16u8) __msa_pckev_b((v16i8) tmp1, (v16i8) tmp0);
            ST_D2(out, 0, 1, dst_tmp, dst_stride);
            dst_tmp += (2 * dst_stride);

            dst0 = dst2;
            dst1 = dst3;
            dst2 = dst4;
            dst3 = dst5;
            dst4 = dst6;
            dst5 = dst7;
            dst6 = dst8;
        }

        src0_ptr += 8;
        src1_ptr += 8;
        dst += 8;
    }
}