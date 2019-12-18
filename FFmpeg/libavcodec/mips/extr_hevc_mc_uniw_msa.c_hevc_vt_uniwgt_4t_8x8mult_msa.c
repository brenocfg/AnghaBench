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
typedef  int /*<<< orphan*/  v8i16 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_FILT_4TAP_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEVC_UNIW_RND_CLIP4_MAX_SATU_H (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_B2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_D8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_adds_s_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_fill_h (int) ; 
 int /*<<< orphan*/  __msa_fill_w (int) ; 
 int /*<<< orphan*/  __msa_srar_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hevc_vt_uniwgt_4t_8x8mult_msa(uint8_t *src,
                                          int32_t src_stride,
                                          uint8_t *dst,
                                          int32_t dst_stride,
                                          const int8_t *filter,
                                          int32_t height,
                                          int32_t weight,
                                          int32_t offset,
                                          int32_t rnd_val)
{
    int32_t loop_cnt;
    v16u8 out0, out1, out2, out3;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v16i8 src10_r, src32_r, src21_r, src43_r;
    v16i8 src54_r, src65_r, src76_r, src87_r, src98_r, src109_r;
    v8i16 filt0, filt1;
    v8i16 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;
    v8i16 filter_vec, weight_vec_h, offset_vec, denom_vec;
    v4i32 weight_vec, rnd_vec;

    src -= src_stride;

    weight = weight & 0x0000FFFF;

    weight_vec = __msa_fill_w(weight);
    rnd_vec = __msa_fill_w(rnd_val);

    weight *= 128;
    rnd_val -= 6;

    weight_vec_h = __msa_fill_h(weight);
    offset_vec = __msa_fill_h(offset);
    denom_vec = __msa_fill_h(rnd_val);

    weight_vec_h = __msa_srar_h(weight_vec_h, denom_vec);
    offset_vec = __msa_adds_s_h(offset_vec, weight_vec_h);

    filter_vec = LD_SH(filter);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    LD_SB3(src, src_stride, src0, src1, src2);
    src += (3 * src_stride);
    XORI_B3_128_SB(src0, src1, src2);
    ILVR_B2_SB(src1, src0, src2, src1, src10_r, src21_r);

    for (loop_cnt = (height >> 3); loop_cnt--;) {
        LD_SB8(src, src_stride,
               src3, src4, src5, src6, src7, src8, src9, src10);
        src += (8 * src_stride);
        XORI_B8_128_SB(src3, src4, src5, src6, src7, src8, src9, src10);
        ILVR_B2_SB(src3, src2, src4, src3, src32_r, src43_r);
        ILVR_B2_SB(src5, src4, src6, src5, src54_r, src65_r);
        ILVR_B2_SB(src7, src6, src8, src7, src76_r, src87_r);
        ILVR_B2_SB(src9, src8, src10, src9, src98_r, src109_r);
        dst0 = HEVC_FILT_4TAP_SH(src10_r, src32_r, filt0, filt1);
        dst1 = HEVC_FILT_4TAP_SH(src21_r, src43_r, filt0, filt1);
        dst2 = HEVC_FILT_4TAP_SH(src32_r, src54_r, filt0, filt1);
        dst3 = HEVC_FILT_4TAP_SH(src43_r, src65_r, filt0, filt1);
        dst4 = HEVC_FILT_4TAP_SH(src54_r, src76_r, filt0, filt1);
        dst5 = HEVC_FILT_4TAP_SH(src65_r, src87_r, filt0, filt1);
        dst6 = HEVC_FILT_4TAP_SH(src76_r, src98_r, filt0, filt1);
        dst7 = HEVC_FILT_4TAP_SH(src87_r, src109_r, filt0, filt1);
        HEVC_UNIW_RND_CLIP4_MAX_SATU_H(dst0, dst1, dst2, dst3, weight_vec,
                                       offset_vec, rnd_vec, dst0, dst1, dst2,
                                       dst3);
        HEVC_UNIW_RND_CLIP4_MAX_SATU_H(dst4, dst5, dst6, dst7, weight_vec,
                                       offset_vec, rnd_vec, dst4, dst5, dst6,
                                       dst7);
        PCKEV_B2_UB(dst1, dst0, dst3, dst2, out0, out1);
        PCKEV_B2_UB(dst5, dst4, dst7, dst6, out2, out3);
        ST_D8(out0, out1, out2, out3, 0, 1, 0, 1, 0, 1, 0, 1, dst, dst_stride);
        dst += (8 * dst_stride);

        src2 = src10;
        src10_r = src98_r;
        src21_r = src109_r;
    }
}