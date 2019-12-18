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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 scalar_t__ DPADD_SH3_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HORIZ_4TAP_FILT (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVEV_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB5 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_XORI128_UB (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SAT_SH2_SH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SPLATI_H2_SB (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_H3_SH (scalar_t__,int /*<<< orphan*/ ,int,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRARI_H2_SH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ST_W4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B5_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_ilvev_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_sldi_b (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/ * mc_filt_mask_arr ; 
 int /*<<< orphan*/ ** subpel_filters_msa ; 

void ff_put_vp8_epel4_h4v6_msa(uint8_t *dst, ptrdiff_t dst_stride,
                               uint8_t *src, ptrdiff_t src_stride,
                               int height, int mx, int my)
{
    uint32_t loop_cnt;
    const int8_t *filter_horiz = subpel_filters_msa[mx - 1];
    const int8_t *filter_vert = subpel_filters_msa[my - 1];
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8;
    v16i8 filt_hz0, filt_hz1, mask0, mask1;
    v16u8 out;
    v8i16 hz_out0, hz_out1, hz_out2, hz_out3, hz_out4, hz_out5, hz_out6;
    v8i16 hz_out7, tmp0, tmp1, out0, out1, out2, out3;
    v8i16 filt, filt_vt0, filt_vt1, filt_vt2;

    mask0 = LD_SB(&mc_filt_mask_arr[16]);

    src -= (1 + 2 * src_stride);

    /* rearranging filter */
    filt = LD_SH(filter_horiz);
    SPLATI_H2_SB(filt, 0, 1, filt_hz0, filt_hz1);

    mask1 = mask0 + 2;

    LD_SB5(src, src_stride, src0, src1, src2, src3, src4);
    src += (5 * src_stride);

    XORI_B5_128_SB(src0, src1, src2, src3, src4);
    hz_out0 = HORIZ_4TAP_FILT(src0, src1, mask0, mask1, filt_hz0, filt_hz1);
    hz_out2 = HORIZ_4TAP_FILT(src2, src3, mask0, mask1, filt_hz0, filt_hz1);
    hz_out3 = HORIZ_4TAP_FILT(src3, src4, mask0, mask1, filt_hz0, filt_hz1);
    hz_out1 = (v8i16) __msa_sldi_b((v16i8) hz_out2, (v16i8) hz_out0, 8);
    ILVEV_B2_SH(hz_out0, hz_out1, hz_out2, hz_out3, out0, out1);

    filt = LD_SH(filter_vert);
    SPLATI_H3_SH(filt, 0, 1, 2, filt_vt0, filt_vt1, filt_vt2);

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_SB4(src, src_stride, src5, src6, src7, src8);
        XORI_B4_128_SB(src5, src6, src7, src8);
        src += (4 * src_stride);

        hz_out5 = HORIZ_4TAP_FILT(src5, src6, mask0, mask1, filt_hz0, filt_hz1);
        hz_out4 = (v8i16) __msa_sldi_b((v16i8) hz_out5, (v16i8) hz_out3, 8);
        out2 = (v8i16) __msa_ilvev_b((v16i8) hz_out5, (v16i8) hz_out4);
        tmp0 = DPADD_SH3_SH(out0, out1, out2, filt_vt0, filt_vt1, filt_vt2);

        hz_out7 = HORIZ_4TAP_FILT(src7, src8, mask0, mask1, filt_hz0, filt_hz1);
        hz_out6 = (v8i16) __msa_sldi_b((v16i8) hz_out7, (v16i8) hz_out5, 8);
        out3 = (v8i16) __msa_ilvev_b((v16i8) hz_out7, (v16i8) hz_out6);
        tmp1 = DPADD_SH3_SH(out1, out2, out3, filt_vt0, filt_vt1, filt_vt2);

        SRARI_H2_SH(tmp0, tmp1, 7);
        SAT_SH2_SH(tmp0, tmp1, 7);
        out = PCKEV_XORI128_UB(tmp0, tmp1);
        ST_W4(out, 0, 1, 2, 3, dst, dst_stride);
        dst += (4 * dst_stride);

        hz_out3 = hz_out7;
        out0 = out2;
        out1 = out3;
    }
}