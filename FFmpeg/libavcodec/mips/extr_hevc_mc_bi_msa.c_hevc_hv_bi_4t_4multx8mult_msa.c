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
typedef  int /*<<< orphan*/  v2i64 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
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
 int /*<<< orphan*/  INSERT_D2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LD2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_SB (scalar_t__) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_B2_UB (int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_W2_SH (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int,int,int,int,int) ; 
 int /*<<< orphan*/  SRA_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_W8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UNPCK_R_SB_SH (int,int) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int __msa_ilvr_h (int,int) ; 
 int __msa_ldi_h (int) ; 
 scalar_t__ __msa_splati_d (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hv_bi_4t_4multx8mult_msa(uint8_t *src0_ptr,
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
    uint64_t tp0, tp1;
    v16u8 out0, out1;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v8i16 filt0, filt1;
    v8i16 filt_h0, filt_h1;
    v16i8 mask0 = LD_SB(ff_hevc_mask_arr + 16);
    v16i8 mask1;
    v8i16 filter_vec, const_vec;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v8i16 tmp0, tmp1, tmp2, tmp3;
    v8i16 dst10, dst21, dst22, dst73, dst84, dst95, dst106;
    v8i16 dst10_r, dst32_r, dst54_r, dst76_r;
    v8i16 dst21_r, dst43_r, dst65_r, dst87_r;
    v8i16 dst98_r, dst109_r;
    v8i16 in0 = { 0 }, in1 = { 0 }, in2 = { 0 }, in3 = { 0 };
    v4i32 dst0_r, dst1_r, dst2_r, dst3_r, dst4_r, dst5_r, dst6_r, dst7_r;

    src0_ptr -= (src_stride + 1);

    filter_vec = LD_SH(filter_x);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    filter_vec = LD_SH(filter_y);
    UNPCK_R_SB_SH(filter_vec, filter_vec);

    SPLATI_W2_SH(filter_vec, 0, filt_h0, filt_h1);

    mask1 = mask0 + 2;

    const_vec = __msa_ldi_h(128);
    const_vec <<= 6;

    LD_SB3(src0_ptr, src_stride, src0, src1, src2);
    src0_ptr += (3 * src_stride);
    XORI_B3_128_SB(src0, src1, src2);

    VSHF_B2_SB(src0, src1, src0, src1, mask0, mask1, vec0, vec1);
    VSHF_B2_SB(src1, src2, src1, src2, mask0, mask1, vec2, vec3);
    dst10 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
    dst21 = HEVC_FILT_4TAP_SH(vec2, vec3, filt0, filt1);
    ILVRL_H2_SH(dst21, dst10, dst10_r, dst21_r);
    dst22 = (v8i16) __msa_splati_d((v2i64) dst21, 1);


    for (loop_cnt = height >> 3; loop_cnt--;) {
        LD_SB8(src0_ptr, src_stride,
               src3, src4, src5, src6, src7, src8, src9, src10);
        src0_ptr += (8 * src_stride);
        XORI_B8_128_SB(src3, src4, src5, src6, src7, src8, src9, src10);
        VSHF_B2_SB(src3, src7, src3, src7, mask0, mask1, vec0, vec1);
        VSHF_B2_SB(src4, src8, src4, src8, mask0, mask1, vec2, vec3);
        VSHF_B2_SB(src5, src9, src5, src9, mask0, mask1, vec4, vec5);
        VSHF_B2_SB(src6, src10, src6, src10, mask0, mask1, vec6, vec7);

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

        LD2(src1_ptr, src2_stride, tp0, tp1);
        src1_ptr += 2 * src2_stride;
        INSERT_D2_SH(tp0, tp1, in0);
        LD2(src1_ptr, src2_stride, tp0, tp1);
        src1_ptr += 2 * src2_stride;
        INSERT_D2_SH(tp0, tp1, in1);

        LD2(src1_ptr, src2_stride, tp0, tp1);
        src1_ptr += 2 * src2_stride;
        INSERT_D2_SH(tp0, tp1, in2);
        LD2(src1_ptr, src2_stride, tp0, tp1);
        src1_ptr += 2 * src2_stride;
        INSERT_D2_SH(tp0, tp1, in3);

        ADDS_SH4_SH(in0, const_vec, in1, const_vec, in2, const_vec, in3,
                    const_vec, in0, in1, in2, in3);
        dst0_r = HEVC_FILT_4TAP(dst10_r, dst32_r, filt_h0, filt_h1);
        dst1_r = HEVC_FILT_4TAP(dst21_r, dst43_r, filt_h0, filt_h1);
        dst2_r = HEVC_FILT_4TAP(dst32_r, dst54_r, filt_h0, filt_h1);
        dst3_r = HEVC_FILT_4TAP(dst43_r, dst65_r, filt_h0, filt_h1);
        dst4_r = HEVC_FILT_4TAP(dst54_r, dst76_r, filt_h0, filt_h1);
        dst5_r = HEVC_FILT_4TAP(dst65_r, dst87_r, filt_h0, filt_h1);
        dst6_r = HEVC_FILT_4TAP(dst76_r, dst98_r, filt_h0, filt_h1);
        dst7_r = HEVC_FILT_4TAP(dst87_r, dst109_r, filt_h0, filt_h1);
        SRA_4V(dst0_r, dst1_r, dst2_r, dst3_r, 6);
        SRA_4V(dst4_r, dst5_r, dst6_r, dst7_r, 6);
        PCKEV_H4_SH(dst1_r, dst0_r, dst3_r, dst2_r,
                    dst5_r, dst4_r, dst7_r, dst6_r, tmp0, tmp1, tmp2, tmp3);
        ADDS_SH4_SH(in0, tmp0, in1, tmp1, in2, tmp2, in3, tmp3, tmp0, tmp1,
                    tmp2, tmp3);
        SRARI_H4_SH(tmp0, tmp1, tmp2, tmp3, 7);
        CLIP_SH4_0_255(tmp0, tmp1, tmp2, tmp3);
        PCKEV_B2_UB(tmp1, tmp0, tmp3, tmp2, out0, out1);
        ST_W8(out0, out1, 0, 1, 2, 3, 0, 1, 2, 3, dst, dst_stride);
        dst += (8 * dst_stride);

        dst10_r = dst98_r;
        dst21_r = dst109_r;
        dst22 = (v8i16) __msa_splati_d((v2i64) dst106, 1);
    }
}