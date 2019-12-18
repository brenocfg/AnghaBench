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
typedef  scalar_t__ v8u16 ;
typedef  int /*<<< orphan*/  v8i16 ;
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ HORIZ_2TAP_FILT_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  INSERT_D2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LD4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_AVG_ST8x4_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SAT_UH2_UH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SRARI_H2_UH (scalar_t__,scalar_t__,int) ; 
 scalar_t__ __msa_dotp_u_h (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_ilvev_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_splati_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* mc_filt_mask_arr ; 

__attribute__((used)) static void common_hv_2ht_2vt_and_aver_dst_8x8mult_msa(const uint8_t *src,
                                                       int32_t src_stride,
                                                       uint8_t *dst,
                                                       int32_t dst_stride,
                                                       const int8_t *filter_horiz,
                                                       const int8_t *filter_vert,
                                                       int32_t height)
{
    uint32_t loop_cnt;
    uint64_t tp0, tp1, tp2, tp3;
    v16i8 src0, src1, src2, src3, src4, mask;
    v16u8 filt_hz, filt_vt, vec0, dst0, dst1;
    v8u16 hz_out0, hz_out1, tmp0, tmp1, tmp2, tmp3;
    v8i16 filt;

    mask = LD_SB(&mc_filt_mask_arr[0]);

    /* rearranging filter */
    filt = LD_SH(filter_horiz);
    filt_hz = (v16u8) __msa_splati_h(filt, 0);

    filt = LD_SH(filter_vert);
    filt_vt = (v16u8) __msa_splati_h(filt, 0);

    src0 = LD_SB(src);
    src += src_stride;

    hz_out0 = HORIZ_2TAP_FILT_UH(src0, src0, mask, filt_hz, 7);

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_SB4(src, src_stride, src1, src2, src3, src4);
        src += (4 * src_stride);

        hz_out1 = HORIZ_2TAP_FILT_UH(src1, src1, mask, filt_hz, 7);
        vec0 = (v16u8) __msa_ilvev_b((v16i8) hz_out1, (v16i8) hz_out0);
        tmp0 = __msa_dotp_u_h(vec0, filt_vt);

        hz_out0 = HORIZ_2TAP_FILT_UH(src2, src2, mask, filt_hz, 7);
        vec0 = (v16u8) __msa_ilvev_b((v16i8) hz_out0, (v16i8) hz_out1);
        tmp1 = __msa_dotp_u_h(vec0, filt_vt);

        SRARI_H2_UH(tmp0, tmp1, 7);
        SAT_UH2_UH(tmp0, tmp1, 7);

        hz_out1 = HORIZ_2TAP_FILT_UH(src3, src3, mask, filt_hz, 7);
        vec0 = (v16u8) __msa_ilvev_b((v16i8) hz_out1, (v16i8) hz_out0);
        tmp2 = __msa_dotp_u_h(vec0, filt_vt);

        hz_out0 = HORIZ_2TAP_FILT_UH(src4, src4, mask, filt_hz, 7);
        vec0 = (v16u8) __msa_ilvev_b((v16i8) hz_out0, (v16i8) hz_out1);
        tmp3 = __msa_dotp_u_h(vec0, filt_vt);

        SRARI_H2_UH(tmp2, tmp3, 7);
        SAT_UH2_UH(tmp2, tmp3, 7);
        LD4(dst, dst_stride, tp0, tp1, tp2, tp3);
        INSERT_D2_UB(tp0, tp1, dst0);
        INSERT_D2_UB(tp2, tp3, dst1);
        PCKEV_AVG_ST8x4_UB(tmp0, tmp1, tmp2, tmp3, dst0, dst1, dst, dst_stride);
        dst += (4 * dst_stride);
    }
}