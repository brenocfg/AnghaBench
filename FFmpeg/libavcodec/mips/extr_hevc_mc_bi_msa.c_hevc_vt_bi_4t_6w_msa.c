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
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPADD_SB2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  HEVC_BI_RND_CLIP4 (int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ILVR_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH4 (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ST_H2 (int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_W2 (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B2_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __msa_ldi_h (int) ; 

__attribute__((used)) static void hevc_vt_bi_4t_6w_msa(uint8_t *src0_ptr,
                                 int32_t src_stride,
                                 int16_t *src1_ptr,
                                 int32_t src2_stride,
                                 uint8_t *dst,
                                 int32_t dst_stride,
                                 const int8_t *filter,
                                 int32_t height)
{
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v8i16 in0, in1, in2, in3;
    v16i8 src10_r, src32_r, src21_r, src43_r, src54_r, src65_r;
    v8i16 dst0_r, dst1_r, dst2_r, dst3_r;
    v8i16 filt0, filt1;
    v8i16 filter_vec, const_vec;

    src0_ptr -= src_stride;

    const_vec = __msa_ldi_h(128);
    const_vec <<= 6;

    filter_vec = LD_SH(filter);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    LD_SB3(src0_ptr, src_stride, src0, src1, src2);
    src0_ptr += (3 * src_stride);
    LD_SB2(src0_ptr, src_stride, src3, src4);
    src0_ptr += (2 * src_stride);
    LD_SB2(src0_ptr, src_stride, src5, src6);
    src0_ptr += (2 * src_stride);
    LD_SB2(src0_ptr, src_stride, src7, src8);
    src0_ptr += (2 * src_stride);
    LD_SB2(src0_ptr, src_stride, src9, src10);
    src0_ptr += (2 * src_stride);

    LD_SH4(src1_ptr, src2_stride, in0, in1, in2, in3);
    src1_ptr += (4 * src2_stride);

    XORI_B3_128_SB(src0, src1, src2);
    XORI_B2_128_SB(src3, src4);
    XORI_B2_128_SB(src5, src6);
    XORI_B2_128_SB(src7, src8);
    XORI_B2_128_SB(src9, src10);

    ILVR_B2_SB(src1, src0, src2, src1, src10_r, src21_r);
    ILVR_B2_SB(src3, src2, src4, src3, src32_r, src43_r);

    dst0_r = const_vec;
    DPADD_SB2_SH(src10_r, src32_r, filt0, filt1, dst0_r, dst0_r);
    dst1_r = const_vec;
    DPADD_SB2_SH(src21_r, src43_r, filt0, filt1, dst1_r, dst1_r);

    ILVR_B2_SB(src5, src4, src6, src5, src54_r, src65_r);

    dst2_r = const_vec;
    DPADD_SB2_SH(src32_r, src54_r, filt0, filt1, dst2_r, dst2_r);
    dst3_r = const_vec;
    DPADD_SB2_SH(src43_r, src65_r, filt0, filt1, dst3_r, dst3_r);

    HEVC_BI_RND_CLIP4(in0, in1, in2, in3,
                      dst0_r, dst1_r, dst2_r, dst3_r, 7,
                      dst0_r, dst1_r, dst2_r, dst3_r);

    PCKEV_B2_SH(dst1_r, dst0_r, dst3_r, dst2_r, dst0_r, dst1_r);
    ST_W2(dst0_r, 0, 2, dst, dst_stride);
    ST_H2(dst0_r, 2, 6, dst + 4, dst_stride);
    ST_W2(dst1_r, 0, 2, dst + 2 * dst_stride, dst_stride);
    ST_H2(dst1_r, 2, 6, dst + 2 * dst_stride + 4, dst_stride);
    dst += (4 * dst_stride);

    LD_SH4(src1_ptr, src2_stride, in0, in1, in2, in3);
    src1_ptr += (4 * src2_stride);
    ILVR_B2_SB(src7, src6, src8, src7, src32_r, src43_r);

    dst0_r = const_vec;
    DPADD_SB2_SH(src54_r, src32_r, filt0, filt1, dst0_r, dst0_r);
    dst1_r = const_vec;
    DPADD_SB2_SH(src65_r, src43_r, filt0, filt1, dst1_r, dst1_r);

    ILVR_B2_SB(src9, src8, src10, src9, src54_r, src65_r);

    dst2_r = const_vec;
    DPADD_SB2_SH(src32_r, src54_r, filt0, filt1, dst2_r, dst2_r);
    dst3_r = const_vec;
    DPADD_SB2_SH(src43_r, src65_r, filt0, filt1, dst3_r, dst3_r);

    HEVC_BI_RND_CLIP4(in0, in1, in2, in3,
                      dst0_r, dst1_r, dst2_r, dst3_r, 7,
                      dst0_r, dst1_r, dst2_r, dst3_r);

    PCKEV_B2_SH(dst1_r, dst0_r, dst3_r, dst2_r, dst0_r, dst1_r);
    ST_W2(dst0_r, 0, 2, dst, dst_stride);
    ST_H2(dst0_r, 2, 6, dst + 4, dst_stride);
    ST_W2(dst1_r, 0, 2, dst + 2 * dst_stride, dst_stride);
    ST_H2(dst1_r, 2, 6, dst + 2 * dst_stride + 4, dst_stride);
    dst += (4 * dst_stride);
}