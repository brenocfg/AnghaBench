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
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_BIW_RND_CLIP2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  HEVC_BIW_RND_CLIP4 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HEVC_FILT_8TAP_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SH4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SPLATI_H4_SH (scalar_t__,int /*<<< orphan*/ ,int,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_SH (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ST_SH2 (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VSHF_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B2_128_SB (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B3_128_SB (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __msa_fill_w (int) ; 
 scalar_t__ __msa_pckev_b (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hz_biwgt_8t_48w_msa(uint8_t *src0_ptr,
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
    v16i8 src0, src1, src2, src3, src4;
    v8i16 in0, in1, in2, in3;
    v8i16 filt0, filt1, filt2, filt3;
    v16i8 mask0 = LD_SB(&ff_hevc_mask_arr[0]);
    v16i8 mask1, mask2, mask3, mask4, mask5, mask6, mask7;
    v16i8 vec0, vec1, vec2, vec3;
    v8i16 dst0, dst1, dst2, dst3;
    v8i16 filter_vec, out0, out1, out2, out3;
    v4i32 weight_vec, offset_vec, rnd_vec;

    src0_ptr -= 3;
    offset = (offset0 + offset1) << rnd_val;
    weight0 = weight0 & 0x0000FFFF;
    weight = weight0 | (weight1 << 16);
    constant = 128 * weight1;
    constant <<= 6;
    offset += constant;

    offset_vec = __msa_fill_w(offset);
    weight_vec = __msa_fill_w(weight);
    rnd_vec = __msa_fill_w(rnd_val + 1);

    filter_vec = LD_SH(filter);
    SPLATI_H4_SH(filter_vec, 0, 1, 2, 3, filt0, filt1, filt2, filt3);

    mask1 = mask0 + 2;
    mask2 = mask0 + 4;
    mask3 = mask0 + 6;
    mask4 = mask0 + 8;
    mask5 = mask0 + 10;
    mask6 = mask0 + 12;
    mask7 = mask0 + 14;

    for (loop_cnt = 64; loop_cnt--;) {
        LD_SB2(src0_ptr, 16, src0, src1);
        src2 = LD_SB(src0_ptr + 24);
        LD_SH4(src1_ptr, 8, in0, in1, in2, in3);
        XORI_B3_128_SB(src0, src1, src2);
        LD_SB2(src0_ptr + 32, 8, src3, src4);
        src0_ptr += src_stride;
        XORI_B2_128_SB(src3, src4);

        VSHF_B4_SB(src0, src0, mask0, mask1, mask2, mask3,
                   vec0, vec1, vec2, vec3);
        dst0 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                 filt3);
        VSHF_B4_SB(src0, src1, mask4, mask5, mask6, mask7,
                   vec0, vec1, vec2, vec3);
        dst1 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                 filt3);
        VSHF_B4_SB(src1, src1, mask0, mask1, mask2, mask3,
                   vec0, vec1, vec2, vec3);
        dst2 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                 filt3);
        VSHF_B4_SB(src2, src2, mask0, mask1, mask2, mask3,
                   vec0, vec1, vec2, vec3);
        dst3 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                 filt3);

        HEVC_BIW_RND_CLIP4(dst0, dst1, dst2, dst3, in0, in1, in2, in3,
                           weight_vec, rnd_vec, offset_vec,
                           out0, out1, out2, out3);

        PCKEV_B2_SH(out1, out0, out3, out2, out0, out1);
        ST_SH2(out0, out1, dst, 16);

        LD_SH2(src1_ptr + 32, 8, in2, in3);
        src1_ptr += src2_stride;

        VSHF_B4_SB(src3, src3, mask0, mask1, mask2, mask3,
                   vec0, vec1, vec2, vec3);
        dst0 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                 filt3);
        VSHF_B4_SB(src4, src4, mask0, mask1, mask2, mask3,
                   vec0, vec1, vec2, vec3);
        dst1 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                                 filt3);

        HEVC_BIW_RND_CLIP2(dst0, dst1, in2, in3,
                           weight_vec, rnd_vec, offset_vec,
                           out0, out1);

        out0 = (v8i16) __msa_pckev_b((v16i8) out1, (v16i8) out0);
        ST_SH(out0, dst + 32);
        dst += dst_stride;
    }
}