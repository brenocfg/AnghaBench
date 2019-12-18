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
typedef  int /*<<< orphan*/  v4i32 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDS_SH4_SH (int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  CLIP_SH4_0_255 (int,int,int,int) ; 
 int /*<<< orphan*/  HEVC_FILT_4TAP (int,int,int,int) ; 
 int HEVC_FILT_4TAP_SH (scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (int,int,int,int) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH4 (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_B2_UB (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_W2_SH (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int,int,int,int,int) ; 
 int /*<<< orphan*/  SRA_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_D4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UNPCK_R_SB_SH (int,int) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int __msa_ldi_h (int) ; 
 int /*<<< orphan*/  ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hv_bi_4t_8multx4mult_msa(uint8_t *src0_ptr,
                                          int32_t src_stride,
                                          int16_t *src1_ptr,
                                          int32_t src2_stride,
                                          uint8_t *dst,
                                          int32_t dst_stride,
                                          const int8_t *filter_x,
                                          const int8_t *filter_y,
                                          int32_t height,
                                          int32_t width)
{
    uint32_t loop_cnt, cnt;
    uint8_t *src0_ptr_tmp;
    int16_t *src1_ptr_tmp;
    uint8_t *dst_tmp;
    v16u8 out0, out1;
    v16i8 src0, src1, src2, src3, src4, src5, src6;
    v8i16 in0, in1, in2, in3;
    v8i16 filt0, filt1;
    v8i16 filt_h0, filt_h1;
    v16i8 mask0 = LD_SB(ff_hevc_mask_arr);
    v16i8 mask1;
    v8i16 filter_vec, const_vec;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v8i16 dst0, dst1, dst2, dst3, dst4, dst5;
    v4i32 dst0_r, dst0_l, dst1_r, dst1_l, dst2_r, dst2_l, dst3_r, dst3_l;
    v8i16 tmp0, tmp1, tmp2, tmp3;
    v8i16 dst10_r, dst32_r, dst21_r, dst43_r;
    v8i16 dst10_l, dst32_l, dst21_l, dst43_l;
    v8i16 dst54_r, dst54_l, dst65_r, dst65_l, dst6;

    src0_ptr -= (src_stride + 1);

    filter_vec = LD_SH(filter_x);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    filter_vec = LD_SH(filter_y);
    UNPCK_R_SB_SH(filter_vec, filter_vec);

    SPLATI_W2_SH(filter_vec, 0, filt_h0, filt_h1);

    mask1 = mask0 + 2;

    const_vec = __msa_ldi_h(128);
    const_vec <<= 6;

    for (cnt = width >> 3; cnt--;) {
        src0_ptr_tmp = src0_ptr;
        dst_tmp = dst;
        src1_ptr_tmp = src1_ptr;

        LD_SB3(src0_ptr_tmp, src_stride, src0, src1, src2);
        src0_ptr_tmp += (3 * src_stride);
        XORI_B3_128_SB(src0, src1, src2);

        VSHF_B2_SB(src0, src0, src0, src0, mask0, mask1, vec0, vec1);
        VSHF_B2_SB(src1, src1, src1, src1, mask0, mask1, vec2, vec3);
        VSHF_B2_SB(src2, src2, src2, src2, mask0, mask1, vec4, vec5);

        dst0 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
        dst1 = HEVC_FILT_4TAP_SH(vec2, vec3, filt0, filt1);
        dst2 = HEVC_FILT_4TAP_SH(vec4, vec5, filt0, filt1);

        ILVRL_H2_SH(dst1, dst0, dst10_r, dst10_l);
        ILVRL_H2_SH(dst2, dst1, dst21_r, dst21_l);

        for (loop_cnt = height >> 2; loop_cnt--;) {
            LD_SB4(src0_ptr_tmp, src_stride, src3, src4, src5, src6);
            src0_ptr_tmp += (4 * src_stride);
            LD_SH4(src1_ptr_tmp, src2_stride, in0, in1, in2, in3);
            src1_ptr_tmp += (4 * src2_stride);
            XORI_B4_128_SB(src3, src4, src5, src6);

            ADDS_SH4_SH(in0, const_vec, in1, const_vec, in2, const_vec, in3,
                        const_vec, in0, in1, in2, in3);

            VSHF_B2_SB(src3, src3, src3, src3, mask0, mask1, vec0, vec1);
            VSHF_B2_SB(src4, src4, src4, src4, mask0, mask1, vec2, vec3);
            VSHF_B2_SB(src5, src5, src5, src5, mask0, mask1, vec4, vec5);
            VSHF_B2_SB(src6, src6, src6, src6, mask0, mask1, vec6, vec7);

            dst3 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
            dst4 = HEVC_FILT_4TAP_SH(vec2, vec3, filt0, filt1);
            dst5 = HEVC_FILT_4TAP_SH(vec4, vec5, filt0, filt1);
            dst6 = HEVC_FILT_4TAP_SH(vec6, vec7, filt0, filt1);

            ILVRL_H2_SH(dst3, dst2, dst32_r, dst32_l);
            ILVRL_H2_SH(dst4, dst3, dst43_r, dst43_l);
            ILVRL_H2_SH(dst5, dst4, dst54_r, dst54_l);
            ILVRL_H2_SH(dst6, dst5, dst65_r, dst65_l);

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
            PCKEV_H4_SH(dst0_l, dst0_r, dst1_l, dst1_r, dst2_l, dst2_r, dst3_l,
                        dst3_r, tmp0, tmp1, tmp2, tmp3);
            ADDS_SH4_SH(in0, tmp0, in1, tmp1, in2, tmp2, in3, tmp3,
                        tmp0, tmp1, tmp2, tmp3);
            SRARI_H4_SH(tmp0, tmp1, tmp2, tmp3, 7);
            CLIP_SH4_0_255(tmp0, tmp1, tmp2, tmp3);
            PCKEV_B2_UB(tmp1, tmp0, tmp3, tmp2, out0, out1);
            ST_D4(out0, out1, 0, 1, 0, 1, dst_tmp, dst_stride);
            dst_tmp += (4 * dst_stride);

            dst10_r = dst54_r;
            dst10_l = dst54_l;
            dst21_r = dst65_r;
            dst21_l = dst65_l;
            dst2 = dst6;
        }

        src0_ptr += 8;
        dst += 8;
        src1_ptr += 8;
    }
}