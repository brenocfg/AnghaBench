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
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONVERT_UB_AVG_ST8x4_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 scalar_t__ FILT_8TAP_DPADD_S_H (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HORIZ_8TAP_FILT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVEV_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  INSERT_D2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LD4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB7 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 scalar_t__ LD_UB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SAT_SH4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SPLATI_H4_SB (scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLATI_H4_SH (scalar_t__,int /*<<< orphan*/ ,int,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRARI_H4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XORI_B7_128_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_ilvev_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mc_filt_mask_arr ; 

__attribute__((used)) static void common_hv_8ht_8vt_and_aver_dst_8w_msa(const uint8_t *src,
                                                  int32_t src_stride,
                                                  uint8_t *dst,
                                                  int32_t dst_stride,
                                                  const int8_t *filter_horiz,
                                                  const int8_t *filter_vert,
                                                  int32_t height)
{
    uint32_t loop_cnt;
    uint64_t tp0, tp1, tp2, tp3;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, src9, src10;
    v16i8 filt_hz0, filt_hz1, filt_hz2, filt_hz3;
    v8i16 filt, filt_vt0, filt_vt1, filt_vt2, filt_vt3;
    v16u8 dst0, dst1, mask0, mask1, mask2, mask3;
    v8i16 hz_out0, hz_out1, hz_out2, hz_out3, hz_out4, hz_out5, hz_out6;
    v8i16 hz_out7, hz_out8, hz_out9, hz_out10, tmp0, tmp1, tmp2, tmp3;
    v8i16 out0, out1, out2, out3, out4, out5, out6, out7, out8, out9;

    mask0 = LD_UB(&mc_filt_mask_arr[0]);
    src -= (3 + 3 * src_stride);

    /* rearranging filter */
    filt = LD_SH(filter_horiz);
    SPLATI_H4_SB(filt, 0, 1, 2, 3, filt_hz0, filt_hz1, filt_hz2, filt_hz3);

    mask1 = mask0 + 2;
    mask2 = mask0 + 4;
    mask3 = mask0 + 6;

    LD_SB7(src, src_stride, src0, src1, src2, src3, src4, src5, src6);
    src += (7 * src_stride);

    XORI_B7_128_SB(src0, src1, src2, src3, src4, src5, src6);
    hz_out0 = HORIZ_8TAP_FILT(src0, src0, mask0, mask1, mask2, mask3, filt_hz0,
                              filt_hz1, filt_hz2, filt_hz3);
    hz_out1 = HORIZ_8TAP_FILT(src1, src1, mask0, mask1, mask2, mask3, filt_hz0,
                              filt_hz1, filt_hz2, filt_hz3);
    hz_out2 = HORIZ_8TAP_FILT(src2, src2, mask0, mask1, mask2, mask3, filt_hz0,
                              filt_hz1, filt_hz2, filt_hz3);
    hz_out3 = HORIZ_8TAP_FILT(src3, src3, mask0, mask1, mask2, mask3, filt_hz0,
                              filt_hz1, filt_hz2, filt_hz3);
    hz_out4 = HORIZ_8TAP_FILT(src4, src4, mask0, mask1, mask2, mask3, filt_hz0,
                              filt_hz1, filt_hz2, filt_hz3);
    hz_out5 = HORIZ_8TAP_FILT(src5, src5, mask0, mask1, mask2, mask3, filt_hz0,
                              filt_hz1, filt_hz2, filt_hz3);
    hz_out6 = HORIZ_8TAP_FILT(src6, src6, mask0, mask1, mask2, mask3, filt_hz0,
                              filt_hz1, filt_hz2, filt_hz3);

    filt = LD_SH(filter_vert);
    SPLATI_H4_SH(filt, 0, 1, 2, 3, filt_vt0, filt_vt1, filt_vt2, filt_vt3);

    ILVEV_B2_SH(hz_out0, hz_out1, hz_out2, hz_out3, out0, out1);
    ILVEV_B2_SH(hz_out4, hz_out5, hz_out1, hz_out2, out2, out4);
    ILVEV_B2_SH(hz_out3, hz_out4, hz_out5, hz_out6, out5, out6);

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_SB4(src, src_stride, src7, src8, src9, src10);
        XORI_B4_128_SB(src7, src8, src9, src10);
        src += (4 * src_stride);

        LD4(dst, dst_stride, tp0, tp1, tp2, tp3);
        INSERT_D2_UB(tp0, tp1, dst0);
        INSERT_D2_UB(tp2, tp3, dst1);

        hz_out7 = HORIZ_8TAP_FILT(src7, src7, mask0, mask1, mask2, mask3,
                                  filt_hz0, filt_hz1, filt_hz2, filt_hz3);
        out3 = (v8i16) __msa_ilvev_b((v16i8) hz_out7, (v16i8) hz_out6);
        tmp0 = FILT_8TAP_DPADD_S_H(out0, out1, out2, out3, filt_vt0, filt_vt1,
                                   filt_vt2, filt_vt3);

        hz_out8 = HORIZ_8TAP_FILT(src8, src8, mask0, mask1, mask2, mask3,
                                  filt_hz0, filt_hz1, filt_hz2, filt_hz3);
        out7 = (v8i16) __msa_ilvev_b((v16i8) hz_out8, (v16i8) hz_out7);
        tmp1 = FILT_8TAP_DPADD_S_H(out4, out5, out6, out7, filt_vt0, filt_vt1,
                                   filt_vt2, filt_vt3);

        hz_out9 = HORIZ_8TAP_FILT(src9, src9, mask0, mask1, mask2, mask3,
                                  filt_hz0, filt_hz1, filt_hz2, filt_hz3);
        out8 = (v8i16) __msa_ilvev_b((v16i8) hz_out9, (v16i8) hz_out8);
        tmp2 = FILT_8TAP_DPADD_S_H(out1, out2, out3, out8, filt_vt0, filt_vt1,
                                   filt_vt2, filt_vt3);

        hz_out10 = HORIZ_8TAP_FILT(src10, src10, mask0, mask1, mask2, mask3,
                                   filt_hz0, filt_hz1, filt_hz2, filt_hz3);
        out9 = (v8i16) __msa_ilvev_b((v16i8) hz_out10, (v16i8) hz_out9);
        tmp3 = FILT_8TAP_DPADD_S_H(out5, out6, out7, out9, filt_vt0, filt_vt1,
                                   filt_vt2, filt_vt3);

        SRARI_H4_SH(tmp0, tmp1, tmp2, tmp3, 7);
        SAT_SH4_SH(tmp0, tmp1, tmp2, tmp3, 7);
        CONVERT_UB_AVG_ST8x4_UB(tmp0, tmp1, tmp2, tmp3, dst0, dst1,
                                dst, dst_stride);
        dst += (4 * dst_stride);

        hz_out6 = hz_out10;
        out0 = out2;
        out1 = out3;
        out2 = out8;
        out4 = out6;
        out5 = out7;
        out6 = out9;
    }
}