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
typedef  int /*<<< orphan*/  v8i16 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_BIW_RND_CLIP4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEVC_FILT_4TAP_SH (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_SH2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B8_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __msa_fill_w (int) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hz_biwgt_4t_16w_msa(uint8_t *src0_ptr,
                                     int32_t src_stride,
                                     int16_t *src1_ptr,
                                     int32_t src2_stride,
                                     uint8_t *dst,
                                     int32_t dst_stride,
                                     const int8_t *filter,
                                     int32_t height,
                                     int32_t weight0,
                                     int32_t weight1,
                                     int32_t offset0,
                                     int32_t offset1,
                                     int32_t rnd_val)
{
    uint32_t loop_cnt;
    int32_t offset, weight, constant;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7;
    v8i16 in0, in1, in2, in3, in4, in5, in6, in7;
    v8i16 filt0, filt1;
    v16i8 mask0 = LD_SB(&ff_hevc_mask_arr[0]);
    v16i8 mask1;
    v8i16 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;
    v16i8 vec0, vec1;
    v8i16 filter_vec;
    v4i32 weight_vec, offset_vec, rnd_vec;

    src0_ptr -= 1;

    filter_vec = LD_SH(filter);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    offset = (offset0 + offset1) << rnd_val;
    weight0 = weight0 & 0x0000FFFF;
    weight = weight0 | (weight1 << 16);
    constant = 128 * weight1;
    constant <<= 6;
    offset += constant;

    offset_vec = __msa_fill_w(offset);
    weight_vec = __msa_fill_w(weight);
    rnd_vec = __msa_fill_w(rnd_val + 1);

    mask1 = mask0 + 2;

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_SB4(src0_ptr, src_stride, src0, src2, src4, src6);
        LD_SB4(src0_ptr + 8, src_stride, src1, src3, src5, src7);
        src0_ptr += (4 * src_stride);
        LD_SH4(src1_ptr, src2_stride, in0, in2, in4, in6);
        LD_SH4(src1_ptr + 8, src2_stride, in1, in3, in5, in7);
        src1_ptr += (4 * src2_stride);
        XORI_B8_128_SB(src0, src1, src2, src3, src4, src5, src6, src7);

        VSHF_B2_SB(src0, src0, src0, src0, mask0, mask1, vec0, vec1);
        dst0 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
        VSHF_B2_SB(src1, src1, src1, src1, mask0, mask1, vec0, vec1);
        dst1 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
        VSHF_B2_SB(src2, src2, src2, src2, mask0, mask1, vec0, vec1);
        dst2 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
        VSHF_B2_SB(src3, src3, src3, src3, mask0, mask1, vec0, vec1);
        dst3 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
        VSHF_B2_SB(src4, src4, src4, src4, mask0, mask1, vec0, vec1);
        dst4 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
        VSHF_B2_SB(src5, src5, src5, src5, mask0, mask1, vec0, vec1);
        dst5 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
        VSHF_B2_SB(src6, src6, src6, src6, mask0, mask1, vec0, vec1);
        dst6 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
        VSHF_B2_SB(src7, src7, src7, src7, mask0, mask1, vec0, vec1);
        dst7 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
        HEVC_BIW_RND_CLIP4(dst0, dst1, dst2, dst3,
                           in0, in1, in2, in3,
                           weight_vec, rnd_vec, offset_vec,
                           dst0, dst1, dst2, dst3);

        PCKEV_B2_SH(dst1, dst0, dst3, dst2, dst0, dst1);
        ST_SH2(dst0, dst1, dst, dst_stride);
        dst += (2 * dst_stride);

        HEVC_BIW_RND_CLIP4(dst4, dst5, dst6, dst7,
                           in4, in5, in6, in7,
                           weight_vec, rnd_vec, offset_vec,
                           dst0, dst1, dst2, dst3);

        PCKEV_B2_SH(dst1, dst0, dst3, dst2, dst0, dst1);
        ST_SH2(dst0, dst1, dst, dst_stride);
        dst += (2 * dst_stride);
    }
}