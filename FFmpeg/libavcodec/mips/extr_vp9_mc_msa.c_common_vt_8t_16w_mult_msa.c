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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILT_8TAP_DPADD_S_H (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVL_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVL_B4_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B4_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB7 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_B4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_SH4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPLATI_H4_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_UB4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XORI_B4_128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XORI_B7_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void common_vt_8t_16w_mult_msa(const uint8_t *src, int32_t src_stride,
                                      uint8_t *dst, int32_t dst_stride,
                                      const int8_t *filter, int32_t height,
                                      int32_t width)
{
    const uint8_t *src_tmp;
    uint8_t *dst_tmp;
    uint32_t loop_cnt, cnt;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v16i8 filt0, filt1, filt2, filt3;
    v16i8 src10_r, src32_r, src54_r, src76_r, src98_r, src21_r, src43_r;
    v16i8 src65_r, src87_r, src109_r, src10_l, src32_l, src54_l, src76_l;
    v16i8 src98_l, src21_l, src43_l, src65_l, src87_l, src109_l;
    v16u8 tmp0, tmp1, tmp2, tmp3;
    v8i16 filt, out0_r, out1_r, out2_r, out3_r, out0_l, out1_l, out2_l, out3_l;

    src -= (3 * src_stride);

    filt = LD_SH(filter);
    SPLATI_H4_SB(filt, 0, 1, 2, 3, filt0, filt1, filt2, filt3);

    for (cnt = (width >> 4); cnt--;) {
        src_tmp = src;
        dst_tmp = dst;

        LD_SB7(src_tmp, src_stride, src0, src1, src2, src3, src4, src5, src6);
        XORI_B7_128_SB(src0, src1, src2, src3, src4, src5, src6);
        src_tmp += (7 * src_stride);
        ILVR_B4_SB(src1, src0, src3, src2, src5, src4, src2, src1, src10_r,
                   src32_r, src54_r, src21_r);
        ILVR_B2_SB(src4, src3, src6, src5, src43_r, src65_r);
        ILVL_B4_SB(src1, src0, src3, src2, src5, src4, src2, src1, src10_l,
                   src32_l, src54_l, src21_l);
        ILVL_B2_SB(src4, src3, src6, src5, src43_l, src65_l);

        for (loop_cnt = (height >> 2); loop_cnt--;) {
            LD_SB4(src_tmp, src_stride, src7, src8, src9, src10);
            XORI_B4_128_SB(src7, src8, src9, src10);
            src_tmp += (4 * src_stride);
            ILVR_B4_SB(src7, src6, src8, src7, src9, src8, src10, src9, src76_r,
                       src87_r, src98_r, src109_r);
            ILVL_B4_SB(src7, src6, src8, src7, src9, src8, src10, src9, src76_l,
                       src87_l, src98_l, src109_l);
            out0_r = FILT_8TAP_DPADD_S_H(src10_r, src32_r, src54_r, src76_r,
                                         filt0, filt1, filt2, filt3);
            out1_r = FILT_8TAP_DPADD_S_H(src21_r, src43_r, src65_r, src87_r,
                                         filt0, filt1, filt2, filt3);
            out2_r = FILT_8TAP_DPADD_S_H(src32_r, src54_r, src76_r, src98_r,
                                         filt0, filt1, filt2, filt3);
            out3_r = FILT_8TAP_DPADD_S_H(src43_r, src65_r, src87_r, src109_r,
                                         filt0, filt1, filt2, filt3);
            out0_l = FILT_8TAP_DPADD_S_H(src10_l, src32_l, src54_l, src76_l,
                                         filt0, filt1, filt2, filt3);
            out1_l = FILT_8TAP_DPADD_S_H(src21_l, src43_l, src65_l, src87_l,
                                         filt0, filt1, filt2, filt3);
            out2_l = FILT_8TAP_DPADD_S_H(src32_l, src54_l, src76_l, src98_l,
                                         filt0, filt1, filt2, filt3);
            out3_l = FILT_8TAP_DPADD_S_H(src43_l, src65_l, src87_l, src109_l,
                                         filt0, filt1, filt2, filt3);
            SRARI_H4_SH(out0_r, out1_r, out2_r, out3_r, 7);
            SRARI_H4_SH(out0_l, out1_l, out2_l, out3_l, 7);
            SAT_SH4_SH(out0_r, out1_r, out2_r, out3_r, 7);
            SAT_SH4_SH(out0_l, out1_l, out2_l, out3_l, 7);
            PCKEV_B4_UB(out0_l, out0_r, out1_l, out1_r, out2_l, out2_r, out3_l,
                        out3_r, tmp0, tmp1, tmp2, tmp3);
            XORI_B4_128_UB(tmp0, tmp1, tmp2, tmp3);
            ST_UB4(tmp0, tmp1, tmp2, tmp3, dst_tmp, dst_stride);
            dst_tmp += (4 * dst_stride);

            src10_r = src54_r;
            src32_r = src76_r;
            src54_r = src98_r;
            src21_r = src65_r;
            src43_r = src87_r;
            src65_r = src109_r;
            src10_l = src54_l;
            src32_l = src76_l;
            src54_l = src98_l;
            src21_l = src65_l;
            src43_l = src87_l;
            src65_l = src109_l;
            src6 = src10;
        }

        src += 16;
        dst += 16;
    }
}