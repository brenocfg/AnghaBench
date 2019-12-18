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
typedef  int /*<<< orphan*/  v2i64 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ HEVC_FILT_4TAP_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVL_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_XORI128_UB (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SAT_SH2_SH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SAT_SH4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPLATI_H2_SB (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRARI_H2_SH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SRARI_H4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ST_D1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ST_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XORI_B2_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XORI_B2_128_SH (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_copy_u_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void common_vt_4t_24w_msa(uint8_t *src, int32_t src_stride,
                                 uint8_t *dst, int32_t dst_stride,
                                 const int8_t *filter, int32_t height)
{
    uint32_t loop_cnt;
    uint64_t out0, out1;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v16i8 src11, filt0, filt1;
    v16i8 src10_r, src32_r, src76_r, src98_r, src21_r, src43_r, src87_r;
    v16i8 src109_r, src10_l, src32_l, src21_l, src43_l;
    v16u8 out;
    v8i16 filt, out0_r, out1_r, out2_r, out3_r, out0_l, out1_l;

    src -= src_stride;

    filt = LD_SH(filter);
    SPLATI_H2_SB(filt, 0, 1, filt0, filt1);

    /* 16 width */
    LD_SB3(src, src_stride, src0, src1, src2);
    XORI_B3_128_SB(src0, src1, src2);
    ILVR_B2_SB(src1, src0, src2, src1, src10_r, src21_r);
    ILVL_B2_SB(src1, src0, src2, src1, src10_l, src21_l);

    /* 8 width */
    LD_SB3(src + 16, src_stride, src6, src7, src8);
    src += (3 * src_stride);
    XORI_B3_128_SB(src6, src7, src8);
    ILVR_B2_SB(src7, src6, src8, src7, src76_r, src87_r);

    for (loop_cnt = 8; loop_cnt--;) {
        /* 16 width */
        LD_SB2(src, src_stride, src3, src4);
        XORI_B2_128_SB(src3, src4);
        ILVR_B2_SB(src3, src2, src4, src3, src32_r, src43_r);
        ILVL_B2_SB(src3, src2, src4, src3, src32_l, src43_l);

        /* 8 width */
        LD_SB2(src + 16, src_stride, src9, src10);
        src += (2 * src_stride);
        XORI_B2_128_SB(src9, src10);
        ILVR_B2_SB(src9, src8, src10, src9, src98_r, src109_r);

        /* 16 width */
        out0_r = HEVC_FILT_4TAP_SH(src10_r, src32_r, filt0, filt1);
        out0_l = HEVC_FILT_4TAP_SH(src10_l, src32_l, filt0, filt1);
        out1_r = HEVC_FILT_4TAP_SH(src21_r, src43_r, filt0, filt1);
        out1_l = HEVC_FILT_4TAP_SH(src21_l, src43_l, filt0, filt1);

        /* 8 width */
        out2_r = HEVC_FILT_4TAP_SH(src76_r, src98_r, filt0, filt1);
        out3_r = HEVC_FILT_4TAP_SH(src87_r, src109_r, filt0, filt1);

        /* 16 + 8 width */
        SRARI_H4_SH(out0_r, out1_r, out2_r, out3_r, 6);
        SRARI_H2_SH(out0_l, out1_l, 6);
        SAT_SH4_SH(out0_r, out1_r, out2_r, out3_r, 7);
        SAT_SH2_SH(out0_l, out1_l, 7);
        out = PCKEV_XORI128_UB(out0_r, out0_l);
        ST_UB(out, dst);
        PCKEV_B2_SH(out2_r, out2_r, out3_r, out3_r, out2_r, out3_r);
        XORI_B2_128_SH(out2_r, out3_r);
        out0 = __msa_copy_u_d((v2i64) out2_r, 0);
        out1 = __msa_copy_u_d((v2i64) out3_r, 0);
        SD(out0, dst + 16);
        dst += dst_stride;
        out = PCKEV_XORI128_UB(out1_r, out1_l);
        ST_UB(out, dst);
        SD(out1, dst + 16);
        dst += dst_stride;

        /* 16 width */
        LD_SB2(src, src_stride, src5, src2);
        XORI_B2_128_SB(src5, src2);
        ILVR_B2_SB(src5, src4, src2, src5, src10_r, src21_r);
        ILVL_B2_SB(src5, src4, src2, src5, src10_l, src21_l);

        /* 8 width */
        LD_SB2(src + 16, src_stride, src11, src8);
        src += (2 * src_stride);
        XORI_B2_128_SB(src11, src8);
        ILVR_B2_SB(src11, src10, src8, src11, src76_r, src87_r);

        /* 16 width */
        out0_r = HEVC_FILT_4TAP_SH(src32_r, src10_r, filt0, filt1);
        out0_l = HEVC_FILT_4TAP_SH(src32_l, src10_l, filt0, filt1);
        out1_r = HEVC_FILT_4TAP_SH(src43_r, src21_r, filt0, filt1);
        out1_l = HEVC_FILT_4TAP_SH(src43_l, src21_l, filt0, filt1);

        /* 8 width */
        out2_r = HEVC_FILT_4TAP_SH(src98_r, src76_r, filt0, filt1);
        out3_r = HEVC_FILT_4TAP_SH(src109_r, src87_r, filt0, filt1);

        /* 16 + 8 width */
        SRARI_H4_SH(out0_r, out1_r, out2_r, out3_r, 6);
        SRARI_H2_SH(out0_l, out1_l, 6);
        SAT_SH4_SH(out0_r, out1_r, out2_r, out3_r, 7);
        SAT_SH2_SH(out0_l, out1_l, 7);
        out = PCKEV_XORI128_UB(out0_r, out0_l);
        ST_UB(out, dst);
        out = PCKEV_XORI128_UB(out2_r, out2_r);
        ST_D1(out, 0, dst + 16);
        dst += dst_stride;
        out = PCKEV_XORI128_UB(out1_r, out1_l);
        ST_UB(out, dst);
        out = PCKEV_XORI128_UB(out3_r, out3_r);
        ST_D1(out, 0, dst + 16);
        dst += dst_stride;
    }
}