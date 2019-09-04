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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  DOTP_UB4_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_UB2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_UH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_AVG_ST_UB (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SRARI_H4_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  VSHF_B2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __msa_sldi_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ __msa_splati_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* mc_filt_mask_arr ; 
 int /*<<< orphan*/ ** vp9_bilinear_filters_msa ; 

void ff_avg_bilin_32h_msa(uint8_t *dst, ptrdiff_t dst_stride,
                          const uint8_t *src, ptrdiff_t src_stride,
                          int height, int mx, int my)
{
    uint32_t loop_cnt;
    const int8_t *filter = vp9_bilinear_filters_msa[mx - 1];
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, mask;
    v16u8 filt0, dst0, dst1, dst2, dst3;
    v16u8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v8u16 res0, res1, res2, res3, res4, res5, res6, res7, filt;

    mask = LD_SB(&mc_filt_mask_arr[0]);

    /* rearranging filter */
    filt = LD_UH(filter);
    filt0 = (v16u8) __msa_splati_h((v8i16) filt, 0);

    for (loop_cnt = (height >> 1); loop_cnt--;) {
        src0 = LD_SB(src);
        src2 = LD_SB(src + 16);
        src3 = LD_SB(src + 24);
        src1 = __msa_sldi_b(src2, src0, 8);
        src += src_stride;
        src4 = LD_SB(src);
        src6 = LD_SB(src + 16);
        src7 = LD_SB(src + 24);
        src5 = __msa_sldi_b(src6, src4, 8);
        src += src_stride;

        VSHF_B2_UB(src0, src0, src1, src1, mask, mask, vec0, vec1);
        VSHF_B2_UB(src2, src2, src3, src3, mask, mask, vec2, vec3);
        VSHF_B2_UB(src4, src4, src5, src5, mask, mask, vec4, vec5);
        VSHF_B2_UB(src6, src6, src7, src7, mask, mask, vec6, vec7);
        DOTP_UB4_UH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0,
                    res0, res1, res2, res3);
        DOTP_UB4_UH(vec4, vec5, vec6, vec7, filt0, filt0, filt0, filt0,
                    res4, res5, res6, res7);
        SRARI_H4_UH(res0, res1, res2, res3, 7);
        SRARI_H4_UH(res4, res5, res6, res7, 7);
        LD_UB2(dst, 16, dst0, dst1);
        PCKEV_AVG_ST_UB(res1, res0, dst0, dst);
        PCKEV_AVG_ST_UB(res3, res2, dst1, (dst + 16));
        dst += dst_stride;
        LD_UB2(dst, 16, dst2, dst3);
        PCKEV_AVG_ST_UB(res5, res4, dst2, dst);
        PCKEV_AVG_ST_UB(res7, res6, dst3, (dst + 16));
        dst += dst_stride;
    }
}