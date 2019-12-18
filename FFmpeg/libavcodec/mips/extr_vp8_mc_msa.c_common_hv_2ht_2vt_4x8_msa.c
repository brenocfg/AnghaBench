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
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOTP_UB4_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HORIZ_2TAP_FILT_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  ILVEV_B2_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_UH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_UH4_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  SLDI_B3_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRARI_H4_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ST_W2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ __msa_pckod_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_splati_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mc_filt_mask_arr ; 

__attribute__((used)) static void common_hv_2ht_2vt_4x8_msa(uint8_t *src, int32_t src_stride,
                                      uint8_t *dst, int32_t dst_stride,
                                      const int8_t *filter_horiz,
                                      const int8_t *filter_vert)
{
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, src8, mask;
    v16i8 res0, res1, res2, res3;
    v16u8 filt_hz, filt_vt, vec0, vec1, vec2, vec3;
    v8u16 hz_out0, hz_out1, hz_out2, hz_out3, hz_out4, hz_out5, hz_out6;
    v8u16 hz_out7, hz_out8, vec4, vec5, vec6, vec7, filt;

    mask = LD_SB(&mc_filt_mask_arr[16]);

    /* rearranging filter */
    filt = LD_UH(filter_horiz);
    filt_hz = (v16u8) __msa_splati_h((v8i16) filt, 0);

    filt = LD_UH(filter_vert);
    filt_vt = (v16u8) __msa_splati_h((v8i16) filt, 0);

    LD_SB8(src, src_stride, src0, src1, src2, src3, src4, src5, src6, src7);
    src += (8 * src_stride);
    src8 = LD_SB(src);

    hz_out0 = HORIZ_2TAP_FILT_UH(src0, src1, mask, filt_hz, 7);
    hz_out2 = HORIZ_2TAP_FILT_UH(src2, src3, mask, filt_hz, 7);
    hz_out4 = HORIZ_2TAP_FILT_UH(src4, src5, mask, filt_hz, 7);
    hz_out6 = HORIZ_2TAP_FILT_UH(src6, src7, mask, filt_hz, 7);
    hz_out8 = HORIZ_2TAP_FILT_UH(src8, src8, mask, filt_hz, 7);
    SLDI_B3_UH(hz_out2, hz_out0, hz_out4, hz_out2, hz_out6, hz_out4, 8, hz_out1,
               hz_out3, hz_out5);
    hz_out7 = (v8u16) __msa_pckod_d((v2i64) hz_out8, (v2i64) hz_out6);

    ILVEV_B2_UB(hz_out0, hz_out1, hz_out2, hz_out3, vec0, vec1);
    ILVEV_B2_UB(hz_out4, hz_out5, hz_out6, hz_out7, vec2, vec3);
    DOTP_UB4_UH(vec0, vec1, vec2, vec3, filt_vt, filt_vt, filt_vt, filt_vt,
                vec4, vec5, vec6, vec7);
    SRARI_H4_UH(vec4, vec5, vec6, vec7, 7);
    SAT_UH4_UH(vec4, vec5, vec6, vec7, 7);
    PCKEV_B4_SB(vec4, vec4, vec5, vec5, vec6, vec6, vec7, vec7,
                res0, res1, res2, res3);
    ST_W2(res0, 0, 1, dst, dst_stride);
    ST_W2(res1, 0, 1, dst + 2 * dst_stride, dst_stride);
    ST_W2(res2, 0, 1, dst + 4 * dst_stride, dst_stride);
    ST_W2(res3, 0, 1, dst + 6 * dst_stride, dst_stride);
}