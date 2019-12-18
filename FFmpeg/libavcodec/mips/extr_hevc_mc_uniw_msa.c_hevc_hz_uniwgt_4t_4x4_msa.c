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
typedef  scalar_t__ v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ HEVC_FILT_4TAP_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HEVC_UNIW_RND_CLIP2_MAX_SATU_H (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (scalar_t__,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_W4 (scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_adds_s_h (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_h (int) ; 
 int /*<<< orphan*/  __msa_fill_w (int) ; 
 scalar_t__ __msa_pckev_b (scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_srar_h (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hz_uniwgt_4t_4x4_msa(uint8_t *src,
                                      int32_t src_stride,
                                      uint8_t *dst,
                                      int32_t dst_stride,
                                      const int8_t *filter,
                                      int32_t weight,
                                      int32_t offset,
                                      int32_t rnd_val)
{
    v16u8 out;
    v8i16 filt0, filt1;
    v16i8 src0, src1, src2, src3;
    v16i8 mask1, vec0, vec1, vec2, vec3;
    v8i16 dst0, dst1;
    v8i16 filter_vec, weight_vec_h, offset_vec, denom_vec;
    v4i32 weight_vec, rnd_vec;
    v16i8 mask0 = LD_SB(&ff_hevc_mask_arr[16]);

    src -= 1;

    /* rearranging filter */
    filter_vec = LD_SH(filter);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    mask1 = mask0 + 2;

    weight = weight & 0x0000FFFF;

    weight_vec = __msa_fill_w(weight);
    rnd_vec = __msa_fill_w(rnd_val);

    weight *= 128;
    rnd_val -= 6;

    weight_vec_h = __msa_fill_h(weight);
    offset_vec = __msa_fill_h(offset);
    denom_vec = __msa_fill_h(rnd_val);

    weight_vec_h = __msa_srar_h(weight_vec_h, denom_vec);
    offset_vec = __msa_adds_s_h(offset_vec, weight_vec_h);

    LD_SB4(src, src_stride, src0, src1, src2, src3);
    XORI_B4_128_SB(src0, src1, src2, src3);

    VSHF_B2_SB(src0, src1, src0, src1, mask0, mask1, vec0, vec1);
    VSHF_B2_SB(src2, src3, src2, src3, mask0, mask1, vec2, vec3);
    dst0 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
    dst1 = HEVC_FILT_4TAP_SH(vec2, vec3, filt0, filt1);

    HEVC_UNIW_RND_CLIP2_MAX_SATU_H(dst0, dst1, weight_vec, offset_vec, rnd_vec,
                                   dst0, dst1);

    out = (v16u8) __msa_pckev_b((v16i8) dst1, (v16i8) dst0);
    ST_W4(out, 0, 1, 2, 3, dst, dst_stride);
    dst += (4 * dst_stride);
}