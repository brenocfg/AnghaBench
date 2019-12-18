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
typedef  int /*<<< orphan*/  v2i64 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_SH_0_255 (scalar_t__) ; 
 int /*<<< orphan*/  DOTP_SB3_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  DPADD_SB2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HEVC_BIW_RND_CLIP2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVL_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVL_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVRL_H2_SW (scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  ILVR_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_D3_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB7 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_H4_SH (scalar_t__,int /*<<< orphan*/ ,int,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRAR_W2_SW (int,int,int) ; 
 int /*<<< orphan*/  ST_D2 (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_W2 (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B2_128_SB (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B7_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_dpadd_s_h (scalar_t__,scalar_t__,scalar_t__) ; 
 int __msa_dpadd_s_w (int,scalar_t__,scalar_t__) ; 
 int __msa_fill_w (int) ; 
 scalar_t__ __msa_ilvr_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __msa_ldi_w (int) ; 
 scalar_t__ __msa_pckev_h (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void hevc_vt_biwgt_8t_12w_msa(uint8_t *src0_ptr,
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
    int32_t offset, weight;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8;
    v8i16 in0, in1, in2, in3;
    v16i8 src10_r, src32_r, src54_r, src76_r;
    v16i8 src21_r, src43_r, src65_r, src87_r;
    v8i16 tmp0, tmp1, tmp2;
    v16i8 src10_l, src32_l, src54_l, src76_l;
    v16i8 src21_l, src43_l, src65_l, src87_l;
    v16i8 src2110, src4332, src6554, src8776;
    v8i16 filt0, filt1, filt2, filt3;
    v8i16 out0, out1, out2, filter_vec;
    v4i32 dst2_r, dst2_l;
    v4i32 weight_vec, weight1_vec, offset_vec, rnd_vec, const_vec;

    src0_ptr -= (3 * src_stride);
    offset = (offset0 + offset1) << rnd_val;
    weight0 = weight0 & 0x0000FFFF;
    weight = weight0 | (weight1 << 16);

    const_vec = __msa_ldi_w(128);
    const_vec <<= 6;
    offset_vec = __msa_fill_w(offset);
    weight_vec = __msa_fill_w(weight);
    rnd_vec = __msa_fill_w(rnd_val + 1);
    weight1_vec = __msa_fill_w(weight1);
    offset_vec += const_vec * weight1_vec;

    filter_vec = LD_SH(filter);
    SPLATI_H4_SH(filter_vec, 0, 1, 2, 3, filt0, filt1, filt2, filt3);

    LD_SB7(src0_ptr, src_stride, src0, src1, src2, src3, src4, src5, src6);
    src0_ptr += (7 * src_stride);
    XORI_B7_128_SB(src0, src1, src2, src3, src4, src5, src6);

    ILVR_B4_SB(src1, src0, src3, src2, src5, src4, src2, src1,
               src10_r, src32_r, src54_r, src21_r);
    ILVR_B2_SB(src4, src3, src6, src5, src43_r, src65_r);
    ILVL_B4_SB(src1, src0, src3, src2, src5, src4, src2, src1,
               src10_l, src32_l, src54_l, src21_l);
    ILVL_B2_SB(src4, src3, src6, src5, src43_l, src65_l);
    ILVR_D3_SB(src21_l, src10_l, src43_l, src32_l, src65_l, src54_l,
               src2110, src4332, src6554);

    for (loop_cnt = 8; loop_cnt--;) {
        LD_SB2(src0_ptr, src_stride, src7, src8);
        src0_ptr += (2 * src_stride);
        LD_SH2(src1_ptr, src2_stride, in0, in1);
        LD_SH2((src1_ptr + 8), src2_stride, in2, in3);
        src1_ptr += (2 * src2_stride);
        in2 = (v8i16) __msa_ilvr_d((v2i64) in3, (v2i64) in2);
        XORI_B2_128_SB(src7, src8);

        ILVR_B2_SB(src7, src6, src8, src7, src76_r, src87_r);
        ILVL_B2_SB(src7, src6, src8, src7, src76_l, src87_l);
        src8776 = (v16i8) __msa_ilvr_d((v2i64) src87_l, (v2i64) src76_l);

        DOTP_SB3_SH(src10_r, src21_r, src2110, filt0, filt0, filt0,
                    tmp0, tmp1, tmp2);
        DPADD_SB2_SH(src32_r, src43_r, filt1, filt1, tmp0, tmp1);
        tmp2 = __msa_dpadd_s_h(tmp2, src4332, (v16i8) filt1);
        DPADD_SB2_SH(src54_r, src65_r, filt2, filt2, tmp0, tmp1);
        tmp2 = __msa_dpadd_s_h(tmp2, src6554, (v16i8) filt2);
        DPADD_SB2_SH(src76_r, src87_r, filt3, filt3, tmp0, tmp1);
        tmp2 = __msa_dpadd_s_h(tmp2, src8776, (v16i8) filt3);

        HEVC_BIW_RND_CLIP2(tmp0, tmp1, in0, in1,
                           weight_vec, rnd_vec, offset_vec,
                           out0, out1);

        ILVRL_H2_SW(tmp2, in2, dst2_r, dst2_l);
        dst2_r = __msa_dpadd_s_w(offset_vec, (v8i16) dst2_r,
                                 (v8i16) weight_vec);
        dst2_l = __msa_dpadd_s_w(offset_vec, (v8i16) dst2_l,
                                 (v8i16) weight_vec);
        SRAR_W2_SW(dst2_r, dst2_l, rnd_vec);
        out2 = __msa_pckev_h((v8i16) dst2_l, (v8i16) dst2_r);
        CLIP_SH_0_255(out2);
        PCKEV_B2_SH(out1, out0, out2, out2, out0, out2);
        ST_D2(out0, 0, 1, dst, dst_stride);
        ST_W2(out2, 0, 1, dst + 8, dst_stride);
        dst += (2 * dst_stride);

        src10_r = src32_r;
        src32_r = src54_r;
        src54_r = src76_r;
        src21_r = src43_r;
        src43_r = src65_r;
        src65_r = src87_r;
        src2110 = src4332;
        src4332 = src6554;
        src6554 = src8776;
        src6 = src8;
    }
}