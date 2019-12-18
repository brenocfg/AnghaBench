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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPADD_SB4_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  HEVC_BI_RND_CLIP4 (int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ILVR_D2_SH (int,int,int,int,int,int) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH4 (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_B2_SB (int,int,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  ST_W8 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int __msa_ldi_h (int) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hz_bi_4t_4x8multiple_msa(uint8_t *src0_ptr,
                                          int32_t src_stride,
                                          int16_t *src1_ptr,
                                          int32_t src2_stride,
                                          uint8_t *dst,
                                          int32_t dst_stride,
                                          const int8_t *filter,
                                          int32_t height)
{
    uint32_t loop_cnt;
    v8i16 filt0, filt1;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7;
    v16i8 dst0, dst1;
    v8i16 in0, in1, in2, in3, in4, in5, in6, in7;
    v16i8 mask0 = LD_SB(&ff_hevc_mask_arr[16]);
    v16i8 mask1, vec0, vec1, vec2, vec3;
    v8i16 tmp0, tmp1, tmp2, tmp3;
    v8i16 filter_vec, const_vec;

    src0_ptr -= 1;

    const_vec = __msa_ldi_h(128);
    const_vec <<= 6;

    filter_vec = LD_SH(filter);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    mask1 = mask0 + 2;

    for (loop_cnt = (height >> 3); loop_cnt--;) {
        LD_SB8(src0_ptr, src_stride,
               src0, src1, src2, src3, src4, src5, src6, src7);
        src0_ptr += (8 * src_stride);
        LD_SH4(src1_ptr, src2_stride, in0, in1, in2, in3);
        src1_ptr += (4 * src2_stride);
        LD_SH4(src1_ptr, src2_stride, in4, in5, in6, in7);
        src1_ptr += (4 * src2_stride);
        ILVR_D2_SH(in1, in0, in3, in2, in0, in1);
        ILVR_D2_SH(in5, in4, in7, in6, in2, in3);
        XORI_B8_128_SB(src0, src1, src2, src3, src4, src5, src6, src7);

        tmp0 = const_vec;
        tmp1 = const_vec;
        tmp2 = const_vec;
        tmp3 = const_vec;
        VSHF_B2_SB(src0, src1, src2, src3, mask0, mask0, vec0, vec1);
        VSHF_B2_SB(src4, src5, src6, src7, mask0, mask0, vec2, vec3);
        DPADD_SB4_SH(vec0, vec1, vec2, vec3, filt0, filt0, filt0, filt0, tmp0,
                     tmp1, tmp2, tmp3);
        VSHF_B2_SB(src0, src1, src2, src3, mask1, mask1, vec0, vec1);
        VSHF_B2_SB(src4, src5, src6, src7, mask1, mask1, vec2, vec3);
        DPADD_SB4_SH(vec0, vec1, vec2, vec3, filt1, filt1, filt1, filt1, tmp0,
                     tmp1, tmp2, tmp3);

        HEVC_BI_RND_CLIP4(in0, in1, in2, in3,
                          tmp0, tmp1, tmp2, tmp3, 7, tmp0, tmp1, tmp2, tmp3);

        PCKEV_B2_SB(tmp1, tmp0, tmp3, tmp2, dst0, dst1);
        ST_W8(dst0, dst1, 0, 1, 2, 3, 0, 1, 2, 3, dst, dst_stride);
        dst += (8 * dst_stride);
    }
}