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
 int /*<<< orphan*/  ST_UB (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mc_filt_mask_arr ; 
 int /*<<< orphan*/ ** subpel_filters_msa ; 

void ff_put_vp8_epel16_h6_msa(uint8_t *dst, ptrdiff_t dst_stride,
                              uint8_t *src, ptrdiff_t src_stride,
                              int height, int mx, int my)
{
    uint32_t loop_cnt;
    const int8_t *filter = subpel_filters_msa[mx - 1];
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, filt0, filt1, filt2;
    v16u8 mask0, mask1, mask2, out;
    v8i16 filt, out0, out1, out2, out3, out4, out5, out6, out7;

    mask0 = LD_UB(&mc_filt_mask_arr[0]);
    src -= 2;

    /* rearranging filter */
    filt = LD_SH(filter);
    SPLATI_H3_SB(filt, 0, 1, 2, filt0, filt1, filt2);

    mask1 = mask0 + 2;
    mask2 = mask0 + 4;

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_SB4(src, src_stride, src0, src2, src4, src6);
        LD_SB4(src + 8, src_stride, src1, src3, src5, src7);
        XORI_B8_128_SB(src0, src1, src2, src3, src4, src5, src6, src7);
        src += (4 * src_stride);

        HORIZ_6TAP_8WID_4VECS_FILT(src0, src1, src2, src3, mask0, mask1, mask2,
                                   filt0, filt1, filt2, out0, out1, out2, out3);
        HORIZ_6TAP_8WID_4VECS_FILT(src4, src5, src6, src7, mask0, mask1, mask2,
                                   filt0, filt1, filt2, out4, out5, out6, out7);
        SRARI_H4_SH(out0, out1, out2, out3, 7);
        SRARI_H4_SH(out4, out5, out6, out7, 7);
        SAT_SH4_SH(out0, out1, out2, out3, 7);
        SAT_SH4_SH(out4, out5, out6, out7, 7);
        out = PCKEV_XORI128_UB(out0, out1);
        ST_UB(out, dst);
        dst += dst_stride;
        out = PCKEV_XORI128_UB(out2, out3);
        ST_UB(out, dst);
        dst += dst_stride;
        out = PCKEV_XORI128_UB(out4, out5);
        ST_UB(out, dst);
        dst += dst_stride;
        out = PCKEV_XORI128_UB(out6, out7);
        ST_UB(out, dst);
        dst += dst_stride;
    }
}