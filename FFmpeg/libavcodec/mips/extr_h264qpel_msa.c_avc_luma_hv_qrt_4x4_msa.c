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
typedef  int /*<<< orphan*/  v4i32 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 scalar_t__ AVC_DOT_SH3_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ AVC_HORZ_FILTER_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB5 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_XORI128_UB (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SAT_SH2_SH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SRARI_H2_SH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ST_W4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_h (int const) ; 
 scalar_t__ __msa_insve_w (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_srari_h (scalar_t__,int) ; 
 int /*<<< orphan*/ * luma_mask_arr ; 

__attribute__((used)) static void avc_luma_hv_qrt_4x4_msa(const uint8_t *src_x, const uint8_t *src_y,
                                    uint8_t *dst, int32_t stride)
{
    const int16_t filt_const0 = 0xfb01;
    const int16_t filt_const1 = 0x1414;
    const int16_t filt_const2 = 0x1fb;
    v16u8 out;
    v16i8 src_hz0, src_hz1, src_hz2, src_hz3, src_vt7, src_vt8;
    v16i8 src_vt0, src_vt1, src_vt2, src_vt3, src_vt4, src_vt5, src_vt6;
    v16i8 src_vt10_r, src_vt32_r, src_vt54_r, src_vt76_r;
    v16i8 mask0, mask1, mask2, filt0, filt1, filt2;
    v8i16 hz_out0, hz_out1, vt_out0, vt_out1, out0, out1;

    filt0 = (v16i8) __msa_fill_h(filt_const0);
    filt1 = (v16i8) __msa_fill_h(filt_const1);
    filt2 = (v16i8) __msa_fill_h(filt_const2);

    LD_SB3(&luma_mask_arr[48], 16, mask0, mask1, mask2);

    LD_SB5(src_y, stride, src_vt0, src_vt1, src_vt2, src_vt3, src_vt4);
    src_y += (5 * stride);

    src_vt0 = (v16i8) __msa_insve_w((v4i32) src_vt0, 1, (v4i32) src_vt1);
    src_vt1 = (v16i8) __msa_insve_w((v4i32) src_vt1, 1, (v4i32) src_vt2);
    src_vt2 = (v16i8) __msa_insve_w((v4i32) src_vt2, 1, (v4i32) src_vt3);
    src_vt3 = (v16i8) __msa_insve_w((v4i32) src_vt3, 1, (v4i32) src_vt4);

    XORI_B4_128_SB(src_vt0, src_vt1, src_vt2, src_vt3);

    LD_SB4(src_x, stride, src_hz0, src_hz1, src_hz2, src_hz3);
    XORI_B4_128_SB(src_hz0, src_hz1, src_hz2, src_hz3);
    hz_out0 = AVC_HORZ_FILTER_SH(src_hz0, src_hz1, mask0, mask1, mask2);
    hz_out1 = AVC_HORZ_FILTER_SH(src_hz2, src_hz3, mask0, mask1, mask2);

    SRARI_H2_SH(hz_out0, hz_out1, 5);
    SAT_SH2_SH(hz_out0, hz_out1, 7);

    LD_SB4(src_y, stride, src_vt5, src_vt6, src_vt7, src_vt8);

    src_vt4 = (v16i8) __msa_insve_w((v4i32) src_vt4, 1, (v4i32) src_vt5);
    src_vt5 = (v16i8) __msa_insve_w((v4i32) src_vt5, 1, (v4i32) src_vt6);
    src_vt6 = (v16i8) __msa_insve_w((v4i32) src_vt6, 1, (v4i32) src_vt7);
    src_vt7 = (v16i8) __msa_insve_w((v4i32) src_vt7, 1, (v4i32) src_vt8);

    XORI_B4_128_SB(src_vt4, src_vt5, src_vt6, src_vt7);
    ILVR_B2_SB(src_vt1, src_vt0, src_vt3, src_vt2, src_vt10_r, src_vt32_r);
    ILVR_B2_SB(src_vt5, src_vt4, src_vt7, src_vt6, src_vt54_r, src_vt76_r);
    vt_out0 = AVC_DOT_SH3_SH(src_vt10_r, src_vt32_r, src_vt54_r, filt0, filt1,
                             filt2);
    vt_out1 = AVC_DOT_SH3_SH(src_vt32_r, src_vt54_r, src_vt76_r, filt0, filt1,
                             filt2);
    SRARI_H2_SH(vt_out0, vt_out1, 5);
    SAT_SH2_SH(vt_out0, vt_out1, 7);

    out0 = __msa_srari_h((hz_out0 + vt_out0), 1);
    out1 = __msa_srari_h((hz_out1 + vt_out1), 1);

    SAT_SH2_SH(out0, out1, 7);
    out = PCKEV_XORI128_UB(out0, out1);
    ST_W4(out, 0, 1, 2, 3, dst, stride);
}