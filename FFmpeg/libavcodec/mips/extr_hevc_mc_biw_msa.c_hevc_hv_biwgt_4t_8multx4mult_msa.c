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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_SH4_0_255 (int,int,int,int) ; 
 int HEVC_FILT_4TAP (int,int,int,int) ; 
 int HEVC_FILT_4TAP_SH (scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (int,int,int,int) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH4 (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_B2_UB (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_H4_SH (int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_H4_SW (int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_W2_SH (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SRAR_W4_SW (int,int,int,int,int) ; 
 int /*<<< orphan*/  SRA_4V (int,int,int,int,int) ; 
 int /*<<< orphan*/  ST_D4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UNPCK_R_SB_SH (int,int) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int __msa_dpadd_s_w (int,int,int) ; 
 int __msa_fill_w (int) ; 
 int /*<<< orphan*/  ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hv_biwgt_4t_8multx4mult_msa(uint8_t *src0_ptr,
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
                                             int32_t width)
{
    uint32_t loop_cnt;
    uint32_t cnt;
    int32_t offset, weight;
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
    v8i16 filter_vec;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v8i16 dsth0, dsth1, dsth2, dsth3, dsth4, dsth5, dsth6;
    v4i32 dst0_r, dst0_l, dst1_r, dst1_l, dst2_r, dst2_l, dst3_r, dst3_l;
    v8i16 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    v4i32 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;
    v8i16 dst10_r, dst32_r, dst54_r, dst21_r, dst43_r, dst65_r;
    v8i16 dst10_l, dst32_l, dst54_l, dst21_l, dst43_l, dst65_l, weight_vec;
    v4i32 offset_vec, rnd_vec, const_vec;

    src0_ptr -= (src_stride + 1);

    filter_vec = LD_SH(filter_x);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    filter_vec = LD_SH(filter_y);
    UNPCK_R_SB_SH(filter_vec, filter_vec);

    SPLATI_W2_SH(filter_vec, 0, filt_h0, filt_h1);

    mask1 = mask0 + 2;

    offset = (offset0 + offset1) << rnd_val;
    weight0 = weight0 & 0x0000FFFF;
    weight = weight0 | (weight1 << 16);

    const_vec = __msa_fill_w((128 * weight1));
    const_vec <<= 6;
    offset_vec = __msa_fill_w(offset);
    weight_vec = (v8i16) __msa_fill_w(weight);
    rnd_vec = __msa_fill_w(rnd_val + 1);
    offset_vec += const_vec;

    for (cnt = width >> 3; cnt--;) {
        src0_ptr_tmp = src0_ptr;
        src1_ptr_tmp = src1_ptr;
        dst_tmp = dst;

        LD_SB3(src0_ptr_tmp, src_stride, src0, src1, src2);
        src0_ptr_tmp += (3 * src_stride);
        XORI_B3_128_SB(src0, src1, src2);

        VSHF_B2_SB(src0, src0, src0, src0, mask0, mask1, vec0, vec1);
        VSHF_B2_SB(src1, src1, src1, src1, mask0, mask1, vec2, vec3);
        VSHF_B2_SB(src2, src2, src2, src2, mask0, mask1, vec4, vec5);
        dsth0 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
        dsth1 = HEVC_FILT_4TAP_SH(vec2, vec3, filt0, filt1);
        dsth2 = HEVC_FILT_4TAP_SH(vec4, vec5, filt0, filt1);

        ILVRL_H2_SH(dsth1, dsth0, dst10_r, dst10_l);
        ILVRL_H2_SH(dsth2, dsth1, dst21_r, dst21_l);

        for (loop_cnt = height >> 2; loop_cnt--;) {
            LD_SB4(src0_ptr_tmp, src_stride, src3, src4, src5, src6);
            src0_ptr_tmp += (4 * src_stride);
            LD_SH4(src1_ptr_tmp, src2_stride, in0, in1, in2, in3);
            src1_ptr_tmp += (4 * src2_stride);
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
            PCKEV_H4_SW(dst0_l, dst0_r, dst1_l, dst1_r, dst2_l, dst2_r, dst3_l,
                        dst3_r, dst0, dst1, dst2, dst3);
            ILVRL_H2_SH(dst0, in0, tmp0, tmp1);
            ILVRL_H2_SH(dst1, in1, tmp2, tmp3);
            ILVRL_H2_SH(dst2, in2, tmp4, tmp5);
            ILVRL_H2_SH(dst3, in3, tmp6, tmp7);
            dst0 = __msa_dpadd_s_w(offset_vec, tmp0, weight_vec);
            dst1 = __msa_dpadd_s_w(offset_vec, tmp1, weight_vec);
            dst2 = __msa_dpadd_s_w(offset_vec, tmp2, weight_vec);
            dst3 = __msa_dpadd_s_w(offset_vec, tmp3, weight_vec);
            dst4 = __msa_dpadd_s_w(offset_vec, tmp4, weight_vec);
            dst5 = __msa_dpadd_s_w(offset_vec, tmp5, weight_vec);
            dst6 = __msa_dpadd_s_w(offset_vec, tmp6, weight_vec);
            dst7 = __msa_dpadd_s_w(offset_vec, tmp7, weight_vec);
            SRAR_W4_SW(dst0, dst1, dst2, dst3, rnd_vec);
            SRAR_W4_SW(dst4, dst5, dst6, dst7, rnd_vec);
            PCKEV_H4_SH(dst1, dst0, dst3, dst2, dst5, dst4, dst7, dst6,
                        tmp0, tmp1, tmp2, tmp3);
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

        src0_ptr += 8;
        dst += 8;
        src1_ptr += 8;
    }
}