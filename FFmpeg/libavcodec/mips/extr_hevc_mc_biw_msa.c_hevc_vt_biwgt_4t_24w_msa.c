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
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_BIW_RND_CLIP2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HEVC_BIW_RND_CLIP4 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HEVC_FILT_4TAP_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVL_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_D2 (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_SH2 (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B2_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_fill_w (int) ; 
 scalar_t__ __msa_pckev_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hevc_vt_biwgt_4t_24w_msa(uint8_t *src0_ptr,
                                     int32_t src_stride,
                                     int16_t *src1_ptr,
                                     int32_t src2_stride,
                                     uint8_t *dst,
                                     int32_t dst_stride,
                                     const int8_t *filter,
                                     int32_t height,
                                     int32_t weight0,
                                     int32_t weight1,
                                     int32_t offset0,
                                     int32_t offset1,
                                     int32_t rnd_val)
{
    uint32_t loop_cnt;
    int32_t offset, weight, constant;
    v16i8 src0, src1, src2, src3, src4, src5;
    v16i8 src6, src7, src8, src9, src10, src11;
    v8i16 in0, in1, in2, in3, in4, in5;
    v16i8 src10_r, src32_r, src76_r, src98_r;
    v16i8 src10_l, src32_l, src21_l, src43_l;
    v16i8 src21_r, src43_r, src87_r, src109_r;
    v8i16 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5;
    v8i16 filt0, filt1;
    v8i16 filter_vec;
    v4i32 weight_vec, offset_vec, rnd_vec;

    src0_ptr -= src_stride;

    offset = (offset0 + offset1) << rnd_val;
    weight0 = weight0 & 0x0000FFFF;
    weight = weight0 | (weight1 << 16);
    constant = 128 * weight1;
    constant <<= 6;
    offset += constant;

    offset_vec = __msa_fill_w(offset);
    weight_vec = __msa_fill_w(weight);
    rnd_vec = __msa_fill_w(rnd_val + 1);

    filter_vec = LD_SH(filter);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    /* 16width */
    LD_SB3(src0_ptr, src_stride, src0, src1, src2);
    XORI_B3_128_SB(src0, src1, src2);
    ILVR_B2_SB(src1, src0, src2, src1, src10_r, src21_r);
    ILVL_B2_SB(src1, src0, src2, src1, src10_l, src21_l);
    /* 8width */
    LD_SB3(src0_ptr + 16, src_stride, src6, src7, src8);
    src0_ptr += (3 * src_stride);
    XORI_B3_128_SB(src6, src7, src8);
    ILVR_B2_SB(src7, src6, src8, src7, src76_r, src87_r);

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        /* 16width */
        LD_SB2(src0_ptr, src_stride, src3, src4);
        LD_SH2(src1_ptr, src2_stride, in0, in1);
        LD_SH2(src1_ptr + 8, src2_stride, in2, in3);
        XORI_B2_128_SB(src3, src4);
        ILVR_B2_SB(src3, src2, src4, src3, src32_r, src43_r);
        ILVL_B2_SB(src3, src2, src4, src3, src32_l, src43_l);

        /* 8width */
        LD_SB2(src0_ptr + 16, src_stride, src9, src10);
        src0_ptr += (2 * src_stride);
        LD_SH2(src1_ptr + 16, src2_stride, in4, in5);
        src1_ptr += (2 * src2_stride);
        XORI_B2_128_SB(src9, src10);
        ILVR_B2_SB(src9, src8, src10, src9, src98_r, src109_r);
        /* 16width */
        tmp0 = HEVC_FILT_4TAP_SH(src10_r, src32_r, filt0, filt1);
        tmp4 = HEVC_FILT_4TAP_SH(src10_l, src32_l, filt0, filt1);
        tmp1 = HEVC_FILT_4TAP_SH(src21_r, src43_r, filt0, filt1);
        tmp5 = HEVC_FILT_4TAP_SH(src21_l, src43_l, filt0, filt1);
        /* 8width */
        tmp2 = HEVC_FILT_4TAP_SH(src76_r, src98_r, filt0, filt1);
        tmp3 = HEVC_FILT_4TAP_SH(src87_r, src109_r, filt0, filt1);
        /* 16width */
        HEVC_BIW_RND_CLIP4(tmp0, tmp1, tmp4, tmp5,
                           in0, in1, in2, in3,
                           weight_vec, rnd_vec, offset_vec,
                           tmp0, tmp1, tmp4, tmp5);
        /* 8width */
        HEVC_BIW_RND_CLIP2(tmp2, tmp3, in4, in5,
                           weight_vec, rnd_vec, offset_vec,
                           tmp2, tmp3);
        /* 16width */
        PCKEV_B2_SH(tmp4, tmp0, tmp5, tmp1, tmp0, tmp1);
        /* 8width */
        tmp2 = (v8i16) __msa_pckev_b((v16i8) tmp3, (v16i8) tmp2);
        ST_SH2(tmp0, tmp1, dst, dst_stride);
        ST_D2(tmp2, 0, 1, dst + 16, dst_stride);
        dst += (2 * dst_stride);

        /* 16width */
        LD_SB2(src0_ptr, src_stride, src5, src2);
        LD_SH2(src1_ptr, src2_stride, in0, in1);
        LD_SH2(src1_ptr + 8, src2_stride, in2, in3);
        XORI_B2_128_SB(src5, src2);
        ILVR_B2_SB(src5, src4, src2, src5, src10_r, src21_r);
        ILVL_B2_SB(src5, src4, src2, src5, src10_l, src21_l);
        /* 8width */
        LD_SB2(src0_ptr + 16, src_stride, src11, src8);
        src0_ptr += (2 * src_stride);
        LD_SH2(src1_ptr + 16, src2_stride, in4, in5);
        src1_ptr += (2 * src2_stride);
        XORI_B2_128_SB(src11, src8);
        ILVR_B2_SB(src11, src10, src8, src11, src76_r, src87_r);
        /* 16width */
        tmp0 = HEVC_FILT_4TAP_SH(src32_r, src10_r, filt0, filt1);
        tmp4 = HEVC_FILT_4TAP_SH(src32_l, src10_l, filt0, filt1);
        tmp1 = HEVC_FILT_4TAP_SH(src43_r, src21_r, filt0, filt1);
        tmp5 = HEVC_FILT_4TAP_SH(src43_l, src21_l, filt0, filt1);
        /* 8width */
        tmp2 = HEVC_FILT_4TAP_SH(src98_r, src76_r, filt0, filt1);
        tmp3 = HEVC_FILT_4TAP_SH(src109_r, src87_r, filt0, filt1);
        /* 16width */
        HEVC_BIW_RND_CLIP4(tmp0, tmp1, tmp4, tmp5,
                           in0, in1, in2, in3,
                           weight_vec, rnd_vec, offset_vec,
                           tmp0, tmp1, tmp4, tmp5);
        /* 8width */
        HEVC_BIW_RND_CLIP2(tmp2, tmp3, in4, in5,
                           weight_vec, rnd_vec, offset_vec,
                           tmp2, tmp3);
        /* 16width */
        PCKEV_B2_SH(tmp4, tmp0, tmp5, tmp1, tmp0, tmp1);

        /* 8width */
        tmp2 = (v8i16) __msa_pckev_b((v16i8) tmp3, (v16i8) tmp2);
        ST_SH2(tmp0, tmp1, dst, dst_stride);
        ST_D2(tmp2, 0, 1, dst + 16, dst_stride);
        dst += (2 * dst_stride);
    }
}