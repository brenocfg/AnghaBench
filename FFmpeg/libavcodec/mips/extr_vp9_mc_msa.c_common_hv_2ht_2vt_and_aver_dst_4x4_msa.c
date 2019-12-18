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
typedef  int /*<<< orphan*/  v2i64 ;
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOTP_UB2_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HORIZ_2TAP_FILT_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ILVEV_B2_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  INSERT_W4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB5 (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_UH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LW4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_UH2_UH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SRARI_H2_UH (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ST_W4 (scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_aver_u_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_pckev_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_pckod_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_sldi_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ __msa_splati_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mc_filt_mask_arr ; 

__attribute__((used)) static void common_hv_2ht_2vt_and_aver_dst_4x4_msa(const uint8_t *src,
                                                   int32_t src_stride,
                                                   uint8_t *dst,
                                                   int32_t dst_stride,
                                                   const int8_t *filter_horiz,
                                                   const int8_t *filter_vert)
{
    uint32_t tp0, tp1, tp2, tp3;
    v16i8 src0, src1, src2, src3, src4, mask;
    v16u8 filt_hz, filt_vt, vec0, vec1;
    v16u8 dst0, out;
    v8u16 hz_out0, hz_out1, hz_out2, hz_out3, hz_out4, tmp0, tmp1, filt;

    mask = LD_SB(&mc_filt_mask_arr[16]);

    /* rearranging filter */
    filt = LD_UH(filter_horiz);
    filt_hz = (v16u8) __msa_splati_h((v8i16) filt, 0);

    filt = LD_UH(filter_vert);
    filt_vt = (v16u8) __msa_splati_h((v8i16) filt, 0);

    LD_SB5(src, src_stride, src0, src1, src2, src3, src4);

    hz_out0 = HORIZ_2TAP_FILT_UH(src0, src1, mask, filt_hz, 7);
    hz_out2 = HORIZ_2TAP_FILT_UH(src2, src3, mask, filt_hz, 7);
    hz_out4 = HORIZ_2TAP_FILT_UH(src4, src4, mask, filt_hz, 7);
    hz_out1 = (v8u16) __msa_sldi_b((v16i8) hz_out2, (v16i8) hz_out0, 8);
    hz_out3 = (v8u16) __msa_pckod_d((v2i64) hz_out4, (v2i64) hz_out2);
    ILVEV_B2_UB(hz_out0, hz_out1, hz_out2, hz_out3, vec0, vec1);

    LW4(dst, dst_stride, tp0, tp1, tp2, tp3);
    INSERT_W4_UB(tp0, tp1, tp2, tp3, dst0);

    DOTP_UB2_UH(vec0, vec1, filt_vt, filt_vt, tmp0, tmp1);
    SRARI_H2_UH(tmp0, tmp1, 7);
    SAT_UH2_UH(tmp0, tmp1, 7);

    out = (v16u8) __msa_pckev_b((v16i8) tmp1, (v16i8) tmp0);
    out = __msa_aver_u_b(out, dst0);

    ST_W4(out, 0, 1, 2, 3, dst, dst_stride);
}