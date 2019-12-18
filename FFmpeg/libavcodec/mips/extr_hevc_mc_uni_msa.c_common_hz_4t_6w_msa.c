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
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HORIZ_4TAP_8WID_4VECS_FILT (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_XORI128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_SH4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPLATI_H2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_H2 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_W2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void common_hz_4t_6w_msa(uint8_t *src, int32_t src_stride,
                                uint8_t *dst, int32_t dst_stride,
                                const int8_t *filter, int32_t height)
{
    v16i8 src0, src1, src2, src3, filt0, filt1, mask0, mask1;
    v16u8 out4, out5;
    v8i16 filt, out0, out1, out2, out3;

    mask0 = LD_SB(&ff_hevc_mask_arr[0]);
    src -= 1;

    /* rearranging filter */
    filt = LD_SH(filter);
    SPLATI_H2_SB(filt, 0, 1, filt0, filt1);

    mask1 = mask0 + 2;

    LD_SB4(src, src_stride, src0, src1, src2, src3);
    src += (4 * src_stride);

    XORI_B4_128_SB(src0, src1, src2, src3);
    HORIZ_4TAP_8WID_4VECS_FILT(src0, src1, src2, src3, mask0, mask1, filt0,
                               filt1, out0, out1, out2, out3);
    SRARI_H4_SH(out0, out1, out2, out3, 6);
    SAT_SH4_SH(out0, out1, out2, out3, 7);
    out4 = PCKEV_XORI128_UB(out0, out1);
    out5 = PCKEV_XORI128_UB(out2, out3);
    ST_W2(out4, 0, 2, dst, dst_stride);
    ST_H2(out4, 2, 6, dst + 4, dst_stride);
    ST_W2(out5, 0, 2, dst + 2 * dst_stride, dst_stride);
    ST_H2(out5, 2, 6, dst + 2 * dst_stride + 4, dst_stride);
    dst += (4 * dst_stride);

    LD_SB4(src, src_stride, src0, src1, src2, src3);
    src += (4 * src_stride);

    XORI_B4_128_SB(src0, src1, src2, src3);
    HORIZ_4TAP_8WID_4VECS_FILT(src0, src1, src2, src3, mask0, mask1, filt0,
                               filt1, out0, out1, out2, out3);
    SRARI_H4_SH(out0, out1, out2, out3, 6);
    SAT_SH4_SH(out0, out1, out2, out3, 7);
    out4 = PCKEV_XORI128_UB(out0, out1);
    out5 = PCKEV_XORI128_UB(out2, out3);
    ST_W2(out4, 0, 2, dst, dst_stride);
    ST_H2(out4, 2, 6, dst + 4, dst_stride);
    ST_W2(out5, 0, 2, dst + 2 * dst_stride, dst_stride);
    ST_H2(out5, 2, 6, dst + 2 * dst_stride + 4, dst_stride);
}