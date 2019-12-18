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
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  HORIZ_6TAP_8WID_4VECS_FILT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 scalar_t__ LD_UB (int /*<<< orphan*/ *) ; 
 scalar_t__ PCKEV_XORI128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_SH4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPLATI_H3_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_D4 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mc_filt_mask_arr ; 
 int /*<<< orphan*/ ** subpel_filters_msa ; 

void ff_put_vp8_epel8_h6_msa(uint8_t *dst, ptrdiff_t dst_stride,
                             uint8_t *src, ptrdiff_t src_stride,
                             int height, int mx, int my)
{
    uint32_t loop_cnt;
    const int8_t *filter = subpel_filters_msa[mx - 1];
    v16i8 src0, src1, src2, src3, filt0, filt1, filt2;
    v16u8 mask0, mask1, mask2, tmp0, tmp1;
    v8i16 filt, out0, out1, out2, out3;

    mask0 = LD_UB(&mc_filt_mask_arr[0]);

    src -= 2;

    /* rearranging filter */
    filt = LD_SH(filter);
    SPLATI_H3_SB(filt, 0, 1, 2, filt0, filt1, filt2);

    mask1 = mask0 + 2;
    mask2 = mask0 + 4;

    LD_SB4(src, src_stride, src0, src1, src2, src3);
    XORI_B4_128_SB(src0, src1, src2, src3);
    src += (4 * src_stride);
    HORIZ_6TAP_8WID_4VECS_FILT(src0, src1, src2, src3, mask0, mask1, mask2,
                               filt0, filt1, filt2, out0, out1, out2, out3);
    SRARI_H4_SH(out0, out1, out2, out3, 7);
    SAT_SH4_SH(out0, out1, out2, out3, 7);
    tmp0 = PCKEV_XORI128_UB(out0, out1);
    tmp1 = PCKEV_XORI128_UB(out2, out3);
    ST_D4(tmp0, tmp1, 0, 1, 0, 1, dst, dst_stride);
    dst += (4 * dst_stride);

    for (loop_cnt = (height >> 2) - 1; loop_cnt--;) {
        LD_SB4(src, src_stride, src0, src1, src2, src3);
        XORI_B4_128_SB(src0, src1, src2, src3);
        src += (4 * src_stride);
        HORIZ_6TAP_8WID_4VECS_FILT(src0, src1, src2, src3, mask0, mask1, mask2,
                                   filt0, filt1, filt2, out0, out1, out2, out3);
        SRARI_H4_SH(out0, out1, out2, out3, 7);
        SAT_SH4_SH(out0, out1, out2, out3, 7);
        tmp0 = PCKEV_XORI128_UB(out0, out1);
        tmp1 = PCKEV_XORI128_UB(out2, out3);
        ST_D4(tmp0, tmp1, 0, 1, 0, 1, dst, dst_stride);
        dst += (4 * dst_stride);
    }
}