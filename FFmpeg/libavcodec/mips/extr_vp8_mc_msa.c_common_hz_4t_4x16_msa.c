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
 int /*<<< orphan*/  HORIZ_4TAP_4WID_4VECS_FILT (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_XORI128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_SH4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPLATI_H2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRARI_H4_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_W4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * mc_filt_mask_arr ; 

__attribute__((used)) static void common_hz_4t_4x16_msa(uint8_t *src, int32_t src_stride,
                                  uint8_t *dst, int32_t dst_stride,
                                  const int8_t *filter)
{
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7;
    v16i8 filt0, filt1, mask0, mask1;
    v16u8 out;
    v8i16 filt, out0, out1, out2, out3;

    mask0 = LD_SB(&mc_filt_mask_arr[16]);
    src -= 1;

    /* rearranging filter */
    filt = LD_SH(filter);
    SPLATI_H2_SB(filt, 0, 1, filt0, filt1);

    mask1 = mask0 + 2;

    LD_SB8(src, src_stride, src0, src1, src2, src3, src4, src5, src6, src7);
    src += (8 * src_stride);
    XORI_B8_128_SB(src0, src1, src2, src3, src4, src5, src6, src7);
    HORIZ_4TAP_4WID_4VECS_FILT(src0, src1, src2, src3, mask0, mask1,
                               filt0, filt1, out0, out1);
    HORIZ_4TAP_4WID_4VECS_FILT(src4, src5, src6, src7, mask0, mask1,
                               filt0, filt1, out2, out3);
    SRARI_H4_SH(out0, out1, out2, out3, 7);
    SAT_SH4_SH(out0, out1, out2, out3, 7);
    out = PCKEV_XORI128_UB(out0, out1);
    ST_W4(out, 0, 1, 2, 3, dst, dst_stride);
    dst += (4 * dst_stride);
    out = PCKEV_XORI128_UB(out2, out3);
    ST_W4(out, 0, 1, 2, 3, dst, dst_stride);
    dst += (4 * dst_stride);

    LD_SB8(src, src_stride, src0, src1, src2, src3, src4, src5, src6, src7);
    src += (8 * src_stride);
    XORI_B8_128_SB(src0, src1, src2, src3, src4, src5, src6, src7);
    HORIZ_4TAP_4WID_4VECS_FILT(src0, src1, src2, src3, mask0, mask1,
                               filt0, filt1, out0, out1);
    HORIZ_4TAP_4WID_4VECS_FILT(src4, src5, src6, src7, mask0, mask1,
                               filt0, filt1, out2, out3);
    SRARI_H4_SH(out0, out1, out2, out3, 7);
    SAT_SH4_SH(out0, out1, out2, out3, 7);
    out = PCKEV_XORI128_UB(out0, out1);
    ST_W4(out, 0, 1, 2, 3, dst, dst_stride);
    dst += (4 * dst_stride);
    out = PCKEV_XORI128_UB(out2, out3);
    ST_W4(out, 0, 1, 2, 3, dst, dst_stride);
}