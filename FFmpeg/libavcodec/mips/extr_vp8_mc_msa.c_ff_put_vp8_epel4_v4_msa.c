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
typedef  int /*<<< orphan*/  v2i64 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  FILT_4TAP_DPADD_S_H (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_XORI128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_SH2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPLATI_H2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRARI_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_W4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ __msa_ilvr_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_xori_b (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** subpel_filters_msa ; 

void ff_put_vp8_epel4_v4_msa(uint8_t *dst, ptrdiff_t dst_stride,
                             uint8_t *src, ptrdiff_t src_stride,
                             int height, int mx, int my)
{
    uint32_t loop_cnt;
    const int8_t *filter = subpel_filters_msa[my - 1];
    v16i8 src0, src1, src2, src3, src4, src5;
    v16i8 src10_r, src32_r, src54_r, src21_r, src43_r, src65_r;
    v16i8 src2110, src4332, filt0, filt1;
    v8i16 filt, out10, out32;
    v16u8 out;

    src -= src_stride;

    filt = LD_SH(filter);
    SPLATI_H2_SB(filt, 0, 1, filt0, filt1);

    LD_SB3(src, src_stride, src0, src1, src2);
    src += (3 * src_stride);

    ILVR_B2_SB(src1, src0, src2, src1, src10_r, src21_r);

    src2110 = (v16i8) __msa_ilvr_d((v2i64) src21_r, (v2i64) src10_r);
    src2110 = (v16i8) __msa_xori_b((v16u8) src2110, 128);

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_SB3(src, src_stride, src3, src4, src5);
        src += (3 * src_stride);
        ILVR_B2_SB(src3, src2, src4, src3, src32_r, src43_r);
        src4332 = (v16i8) __msa_ilvr_d((v2i64) src43_r, (v2i64) src32_r);
        src4332 = (v16i8) __msa_xori_b((v16u8) src4332, 128);
        out10 = FILT_4TAP_DPADD_S_H(src2110, src4332, filt0, filt1);

        src2 = LD_SB(src);
        src += (src_stride);
        ILVR_B2_SB(src5, src4, src2, src5, src54_r, src65_r);
        src2110 = (v16i8) __msa_ilvr_d((v2i64) src65_r, (v2i64) src54_r);
        src2110 = (v16i8) __msa_xori_b((v16u8) src2110, 128);
        out32 = FILT_4TAP_DPADD_S_H(src4332, src2110, filt0, filt1);
        SRARI_H2_SH(out10, out32, 7);
        SAT_SH2_SH(out10, out32, 7);
        out = PCKEV_XORI128_UB(out10, out32);
        ST_W4(out, 0, 1, 2, 3, dst, dst_stride);
        dst += (4 * dst_stride);
    }
}