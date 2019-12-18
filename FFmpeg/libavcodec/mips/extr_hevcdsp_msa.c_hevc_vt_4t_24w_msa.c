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
 int /*<<< orphan*/  ILVL_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ST_SH (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ST_SH2 (int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B2_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __msa_ldi_h (int) ; 

__attribute__((used)) static void hevc_vt_4t_24w_msa(uint8_t *src,
                               int32_t src_stride,
                               int16_t *dst,
                               int32_t dst_stride,
                               const int8_t *filter,
                               int32_t height)
{
    int32_t loop_cnt;
    v16i8 src0, src1, src2, src3, src4, src5;
    v16i8 src6, src7, src8, src9, src10, src11;
    v16i8 src10_r, src32_r, src76_r, src98_r;
    v16i8 src21_r, src43_r, src87_r, src109_r;
    v8i16 dst0_r, dst1_r, dst2_r, dst3_r;
    v16i8 src10_l, src32_l, src21_l, src43_l;
    v8i16 dst0_l, dst1_l;
    v8i16 filt0, filt1;
    v8i16 filter_vec, const_vec;

    src -= src_stride;
    const_vec = __msa_ldi_h(128);
    const_vec <<= 6;

    filter_vec = LD_SH(filter);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    LD_SB3(src, src_stride, src0, src1, src2);
    XORI_B3_128_SB(src0, src1, src2);
    ILVR_B2_SB(src1, src0, src2, src1, src10_r, src21_r);
    ILVL_B2_SB(src1, src0, src2, src1, src10_l, src21_l);

    LD_SB3(src + 16, src_stride, src6, src7, src8);
    src += (3 * src_stride);
    XORI_B3_128_SB(src6, src7, src8);
    ILVR_B2_SB(src7, src6, src8, src7, src76_r, src87_r);

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_SB2(src, src_stride, src3, src4);
        XORI_B2_128_SB(src3, src4);
        ILVR_B2_SB(src3, src2, src4, src3, src32_r, src43_r);
        ILVL_B2_SB(src3, src2, src4, src3, src32_l, src43_l);

        LD_SB2(src + 16, src_stride, src9, src10);
        src += (2 * src_stride);
        XORI_B2_128_SB(src9, src10);
        ILVR_B2_SB(src9, src8, src10, src9, src98_r, src109_r);

        dst0_r = const_vec;
        DPADD_SB2_SH(src10_r, src32_r, filt0, filt1, dst0_r, dst0_r);
        dst0_l = const_vec;
        DPADD_SB2_SH(src10_l, src32_l, filt0, filt1, dst0_l, dst0_l);
        dst1_r = const_vec;
        DPADD_SB2_SH(src21_r, src43_r, filt0, filt1, dst1_r, dst1_r);
        dst1_l = const_vec;
        DPADD_SB2_SH(src21_l, src43_l, filt0, filt1, dst1_l, dst1_l);
        dst2_r = const_vec;
        DPADD_SB2_SH(src76_r, src98_r, filt0, filt1, dst2_r, dst2_r);
        dst3_r = const_vec;
        DPADD_SB2_SH(src87_r, src109_r, filt0, filt1, dst3_r, dst3_r);

        ST_SH2(dst0_r, dst0_l, dst, 8);
        ST_SH(dst2_r, dst + 16);
        dst += dst_stride;
        ST_SH2(dst1_r, dst1_l, dst, 8);
        ST_SH(dst3_r, dst + 16);
        dst += dst_stride;

        LD_SB2(src, src_stride, src5, src2);
        XORI_B2_128_SB(src5, src2);
        ILVR_B2_SB(src5, src4, src2, src5, src10_r, src21_r);
        ILVL_B2_SB(src5, src4, src2, src5, src10_l, src21_l);

        LD_SB2(src + 16, src_stride, src11, src8);
        src += (2 * src_stride);
        XORI_B2_128_SB(src11, src8);
        ILVR_B2_SB(src11, src10, src8, src11, src76_r, src87_r);

        dst0_r = const_vec;
        DPADD_SB2_SH(src32_r, src10_r, filt0, filt1, dst0_r, dst0_r);
        dst0_l = const_vec;
        DPADD_SB2_SH(src32_l, src10_l, filt0, filt1, dst0_l, dst0_l);
        dst1_r = const_vec;
        DPADD_SB2_SH(src43_r, src21_r, filt0, filt1, dst1_r, dst1_r);
        dst1_l = const_vec;
        DPADD_SB2_SH(src43_l, src21_l, filt0, filt1, dst1_l, dst1_l);
        dst2_r = const_vec;
        DPADD_SB2_SH(src98_r, src76_r, filt0, filt1, dst2_r, dst2_r);
        dst3_r = const_vec;
        DPADD_SB2_SH(src109_r, src87_r, filt0, filt1, dst3_r, dst3_r);

        ST_SH2(dst0_r, dst0_l, dst, 8);
        ST_SH(dst2_r, dst + 16);
        dst += dst_stride;
        ST_SH2(dst1_r, dst1_l, dst, 8);
        ST_SH(dst3_r, dst + 16);
        dst += dst_stride;
    }
}