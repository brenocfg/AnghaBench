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
typedef  int v8i16 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPADD_SB4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  HEVC_BI_RND_CLIP2 (int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  HEVC_BI_RND_CLIP4 (int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB6 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH2 (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  LD_SH4 (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ST_D2 (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_D4 (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B6_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int __msa_ldi_h (int) ; 
 scalar_t__ __msa_pckev_b (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hz_bi_4t_8x6_msa(uint8_t *src0_ptr,
                                  int32_t src_stride,
                                  int16_t *src1_ptr,
                                  int32_t src2_stride,
                                  uint8_t *dst,
                                  int32_t dst_stride,
                                  const int8_t *filter,
                                  int32_t height)
{
    v8i16 filt0, filt1;
    v16i8 src0, src1, src2, src3, src4, src5;
    v8i16 in0, in1, in2, in3, in4, in5;
    v16i8 mask0 = LD_SB(&ff_hevc_mask_arr[0]);
    v16i8 mask1;
    v16i8 vec0, vec1, vec2, vec3;
    v8i16 dst0, dst1, dst2, dst3, dst4, dst5;
    v8i16 filter_vec, const_vec;

    src0_ptr -= 1;

    const_vec = __msa_ldi_h(128);
    const_vec <<= 6;

    filter_vec = LD_SH(filter);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    mask1 = mask0 + 2;

    LD_SB6(src0_ptr, src_stride, src0, src1, src2, src3, src4, src5);
    LD_SH4(src1_ptr, src2_stride, in0, in1, in2, in3);
    src1_ptr += (4 * src2_stride);
    LD_SH2(src1_ptr, src2_stride, in4, in5);
    XORI_B6_128_SB(src0, src1, src2, src3, src4, src5);

    dst0 = const_vec;
    dst1 = const_vec;
    dst2 = const_vec;
    dst3 = const_vec;
    VSHF_B2_SB(src0, src0, src1, src1, mask0, mask0, vec0, vec1);
    VSHF_B2_SB(src2, src2, src3, src3, mask0, mask0, vec2, vec3);
    DPADD_SB4_SH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0, dst0, dst1,
                 dst2, dst3);
    VSHF_B2_SB(src0, src0, src1, src1, mask1, mask1, vec0, vec1);
    VSHF_B2_SB(src2, src2, src3, src3, mask1, mask1, vec2, vec3);
    DPADD_SB4_SH(vec0, vec1, vec2, vec3, filt1, filt1, filt1, filt1, dst0, dst1,
                 dst2, dst3);
    dst4 = const_vec;
    dst5 = const_vec;

    VSHF_B2_SB(src4, src4, src5, src5, mask0, mask0, vec0, vec1);
    VSHF_B2_SB(src4, src4, src5, src5, mask1, mask1, vec2, vec3);
    DPADD_SB4_SH(vec0, vec1, vec2, vec3, filt0, filt0, filt1, filt1, dst4, dst5,
                 dst4, dst5);

    HEVC_BI_RND_CLIP4(in0, in1, in2, in3,
                      dst0, dst1, dst2, dst3, 7, dst0, dst1, dst2, dst3);
    HEVC_BI_RND_CLIP2(in4, in5, dst4, dst5, 7, dst4, dst5);

    PCKEV_B2_SH(dst1, dst0, dst3, dst2, dst0, dst1);
    dst2 = (v8i16) __msa_pckev_b((v16i8) dst5, (v16i8) dst4);
    ST_D4(dst0, dst1, 0, 1, 0, 1, dst, dst_stride);
    ST_D2(dst2, 0, 1, dst + 4 * dst_stride, dst_stride);
}