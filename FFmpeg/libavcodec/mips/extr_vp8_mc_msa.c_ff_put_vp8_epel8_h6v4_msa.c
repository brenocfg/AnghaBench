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
 scalar_t__ FILT_4TAP_DPADD_S_H (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HORIZ_6TAP_FILT (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVEV_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_XORI128_UB (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SAT_SH4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_H3_SB (scalar_t__,int /*<<< orphan*/ ,int,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRARI_H4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ST_D4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_ilvev_b (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * mc_filt_mask_arr ; 
 int /*<<< orphan*/ ** subpel_filters_msa ; 

void ff_put_vp8_epel8_h6v4_msa(uint8_t *dst, ptrdiff_t dst_stride,
                               uint8_t *src, ptrdiff_t src_stride,
                               int height, int mx, int my)
{
    uint32_t loop_cnt;
    const int8_t *filter_horiz = subpel_filters_msa[mx - 1];
    const int8_t *filter_vert = subpel_filters_msa[my - 1];
    v16i8 src0, src1, src2, src3, src4, src5, src6;
    v16i8 filt_hz0, filt_hz1, filt_hz2, mask0, mask1, mask2;
    v8i16 filt, filt_vt0, filt_vt1, hz_out0, hz_out1, hz_out2, hz_out3;
    v8i16 tmp0, tmp1, tmp2, tmp3, vec0, vec1, vec2, vec3;
    v16u8 out0, out1;

    mask0 = LD_SB(&mc_filt_mask_arr[0]);
    src -= (2 + src_stride);

    /* rearranging filter */
    filt = LD_SH(filter_horiz);
    SPLATI_H3_SB(filt, 0, 1, 2, filt_hz0, filt_hz1, filt_hz2);

    mask1 = mask0 + 2;
    mask2 = mask0 + 4;

    LD_SB3(src, src_stride, src0, src1, src2);
    src += (3 * src_stride);

    XORI_B3_128_SB(src0, src1, src2);
    hz_out0 = HORIZ_6TAP_FILT(src0, src0, mask0, mask1, mask2, filt_hz0,
                              filt_hz1, filt_hz2);
    hz_out1 = HORIZ_6TAP_FILT(src1, src1, mask0, mask1, mask2, filt_hz0,
                              filt_hz1, filt_hz2);
    hz_out2 = HORIZ_6TAP_FILT(src2, src2, mask0, mask1, mask2, filt_hz0,
                              filt_hz1, filt_hz2);
    ILVEV_B2_SH(hz_out0, hz_out1, hz_out1, hz_out2, vec0, vec2);

    filt = LD_SH(filter_vert);
    SPLATI_H2_SH(filt, 0, 1, filt_vt0, filt_vt1);

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_SB4(src, src_stride, src3, src4, src5, src6);
        src += (4 * src_stride);

        XORI_B4_128_SB(src3, src4, src5, src6);

        hz_out3 = HORIZ_6TAP_FILT(src3, src3, mask0, mask1, mask2, filt_hz0,
                                  filt_hz1, filt_hz2);
        vec1 = (v8i16) __msa_ilvev_b((v16i8) hz_out3, (v16i8) hz_out2);
        tmp0 = FILT_4TAP_DPADD_S_H(vec0, vec1, filt_vt0, filt_vt1);

        hz_out0 = HORIZ_6TAP_FILT(src4, src4, mask0, mask1, mask2, filt_hz0,
                                  filt_hz1, filt_hz2);
        vec3 = (v8i16) __msa_ilvev_b((v16i8) hz_out0, (v16i8) hz_out3);
        tmp1 = FILT_4TAP_DPADD_S_H(vec2, vec3, filt_vt0, filt_vt1);

        hz_out1 = HORIZ_6TAP_FILT(src5, src5, mask0, mask1, mask2, filt_hz0,
                                  filt_hz1, filt_hz2);
        vec0 = (v8i16) __msa_ilvev_b((v16i8) hz_out1, (v16i8) hz_out0);
        tmp2 = FILT_4TAP_DPADD_S_H(vec1, vec0, filt_vt0, filt_vt1);

        hz_out2 = HORIZ_6TAP_FILT(src6, src6, mask0, mask1, mask2, filt_hz0,
                                  filt_hz1, filt_hz2);
        ILVEV_B2_SH(hz_out3, hz_out0, hz_out1, hz_out2, vec1, vec2);
        tmp3 = FILT_4TAP_DPADD_S_H(vec1, vec2, filt_vt0, filt_vt1);

        SRARI_H4_SH(tmp0, tmp1, tmp2, tmp3, 7);
        SAT_SH4_SH(tmp0, tmp1, tmp2, tmp3, 7);
        out0 = PCKEV_XORI128_UB(tmp0, tmp1);
        out1 = PCKEV_XORI128_UB(tmp2, tmp3);
        ST_D4(out0, out1, 0, 1, 0, 1, dst, dst_stride);
        dst += (4 * dst_stride);
    }
}