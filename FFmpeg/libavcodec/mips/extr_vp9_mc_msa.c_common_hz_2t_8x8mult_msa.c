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
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOTP_UB4_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_UH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRARI_H4_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ST_D4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VSHF_B2_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_splati_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mc_filt_mask_arr ; 

__attribute__((used)) static void common_hz_2t_8x8mult_msa(const uint8_t *src, int32_t src_stride,
                                     uint8_t *dst, int32_t dst_stride,
                                     const int8_t *filter, int32_t height)
{
    v16u8 filt0;
    v16i8 src0, src1, src2, src3, mask, out0, out1;
    v8u16 vec0, vec1, vec2, vec3, filt;

    mask = LD_SB(&mc_filt_mask_arr[0]);

    /* rearranging filter */
    filt = LD_UH(filter);
    filt0 = (v16u8) __msa_splati_h((v8i16) filt, 0);

    LD_SB4(src, src_stride, src0, src1, src2, src3);
    src += (4 * src_stride);

    VSHF_B2_UH(src0, src0, src1, src1, mask, mask, vec0, vec1);
    VSHF_B2_UH(src2, src2, src3, src3, mask, mask, vec2, vec3);
    DOTP_UB4_UH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0,
                vec0, vec1, vec2, vec3);
    SRARI_H4_UH(vec0, vec1, vec2, vec3, 7);
    LD_SB4(src, src_stride, src0, src1, src2, src3);
    src += (4 * src_stride);

    PCKEV_B2_SB(vec1, vec0, vec3, vec2, out0, out1);
    ST_D4(out0, out1, 0, 1, 0, 1, dst, dst_stride);

    VSHF_B2_UH(src0, src0, src1, src1, mask, mask, vec0, vec1);
    VSHF_B2_UH(src2, src2, src3, src3, mask, mask, vec2, vec3);
    DOTP_UB4_UH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0,
                vec0, vec1, vec2, vec3);
    SRARI_H4_UH(vec0, vec1, vec2, vec3, 7);
    PCKEV_B2_SB(vec1, vec0, vec3, vec2, out0, out1);
    ST_D4(out0, out1, 0, 1, 0, 1, dst + 4 * dst_stride, dst_stride);
    dst += (8 * dst_stride);

    if (16 == height) {
        LD_SB4(src, src_stride, src0, src1, src2, src3);
        src += (4 * src_stride);

        VSHF_B2_UH(src0, src0, src1, src1, mask, mask, vec0, vec1);
        VSHF_B2_UH(src2, src2, src3, src3, mask, mask, vec2, vec3);
        DOTP_UB4_UH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0,
                    vec0, vec1, vec2, vec3);
        SRARI_H4_UH(vec0, vec1, vec2, vec3, 7);
        LD_SB4(src, src_stride, src0, src1, src2, src3);
        src += (4 * src_stride);

        PCKEV_B2_SB(vec1, vec0, vec3, vec2, out0, out1);
        ST_D4(out0, out1, 0, 1, 0, 1, dst, dst_stride);

        VSHF_B2_UH(src0, src0, src1, src1, mask, mask, vec0, vec1);
        VSHF_B2_UH(src2, src2, src3, src3, mask, mask, vec2, vec3);
        DOTP_UB4_UH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0,
                    vec0, vec1, vec2, vec3);
        SRARI_H4_UH(vec0, vec1, vec2, vec3, 7);
        PCKEV_B2_SB(vec1, vec0, vec3, vec2, out0, out1);
        ST_D4(out0, out1, 0, 1, 0, 1, dst + 4 * dst_stride, dst_stride);
    }
}