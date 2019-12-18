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
typedef  scalar_t__ v4i32 ;
typedef  int /*<<< orphan*/  v2i64 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  const int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_SH_0_255 (scalar_t__) ; 
 int /*<<< orphan*/  HEVC_BIW_RND_CLIP2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ HEVC_FILT_8TAP_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVRL_H2_SW (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 scalar_t__ LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH2 (int /*<<< orphan*/  const*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPLATI_H4_SH (scalar_t__,int /*<<< orphan*/ ,int,int,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SRAR_W2_SW (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_SH (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VSHF_B4_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B2_128_SB (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __msa_copy_u_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_dpadd_s_w (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_w (int) ; 
 scalar_t__ __msa_pckev_h (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hz_biwgt_8t_24w_msa(uint8_t *src0_ptr,
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
    uint64_t dst_val0;
    int32_t offset, weight, constant;
    v16i8 src0, src1;
    v8i16 in0, in1, in2;
    v8i16 filt0, filt1, filt2, filt3;
    v16i8 mask1, mask2, mask3, mask4, mask5, mask6, mask7;
    v16i8 vec0, vec1, vec2, vec3;
    v8i16 dst0, dst1, dst2;
    v4i32 dst2_r, dst2_l;
    v8i16 filter_vec, out0, out1, out2;
    v4i32 weight_vec, offset_vec, rnd_vec;
    v16i8 mask0 = LD_SB(&ff_hevc_mask_arr[0]);

    src0_ptr = src0_ptr - 3;
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

    LD_SB2(src0_ptr, 16, src0, src1);
    src0_ptr += src_stride;
    LD_SH2(src1_ptr, 8, in0, in1);
    in2 = LD_SH(src1_ptr + 16);
    src1_ptr += src2_stride;
    XORI_B2_128_SB(src0, src1);

    for (loop_cnt = 31; loop_cnt--;) {
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

        HEVC_BIW_RND_CLIP2(dst0, dst1, in0, in1,
                           weight_vec, rnd_vec, offset_vec,
                           out0, out1);

        ILVRL_H2_SW(dst2, in2, dst2_r, dst2_l);
        dst2_r = __msa_dpadd_s_w(offset_vec, (v8i16) dst2_r,
                                 (v8i16) weight_vec);
        dst2_l = __msa_dpadd_s_w(offset_vec, (v8i16) dst2_l,
                                 (v8i16) weight_vec);
        SRAR_W2_SW(dst2_r, dst2_l, rnd_vec);
        out2 = __msa_pckev_h((v8i16) dst2_l, (v8i16) dst2_r);
        CLIP_SH_0_255(out2);

        LD_SB2(src0_ptr, 16, src0, src1);
        src0_ptr += src_stride;
        LD_SH2(src1_ptr, 8, in0, in1);
        in2 = LD_SH(src1_ptr + 16);
        src1_ptr += src2_stride;
        XORI_B2_128_SB(src0, src1);
        PCKEV_B2_SH(out1, out0, out2, out2, out0, out2);
        dst_val0 = __msa_copy_u_d((v2i64) out2, 0);
        ST_SH(out0, dst);
        SD(dst_val0, dst + 16);
        dst += dst_stride;
    }

    VSHF_B4_SB(src0, src0, mask0, mask1, mask2, mask3, vec0, vec1, vec2, vec3);
    dst0 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                             filt3);
    VSHF_B4_SB(src0, src1, mask4, mask5, mask6, mask7, vec0, vec1, vec2, vec3);
    dst1 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                             filt3);
    VSHF_B4_SB(src1, src1, mask0, mask1, mask2, mask3, vec0, vec1, vec2, vec3);
    dst2 = HEVC_FILT_8TAP_SH(vec0, vec1, vec2, vec3, filt0, filt1, filt2,
                             filt3);
    HEVC_BIW_RND_CLIP2(dst0, dst1, in0, in1, weight_vec, rnd_vec, offset_vec,
                       out0, out1);
    ILVRL_H2_SW(dst2, in2, dst2_r, dst2_l);
    dst2_r = __msa_dpadd_s_w(offset_vec, (v8i16) dst2_r, (v8i16) weight_vec);
    dst2_l = __msa_dpadd_s_w(offset_vec, (v8i16) dst2_l, (v8i16) weight_vec);
    SRAR_W2_SW(dst2_r, dst2_l, rnd_vec);
    out2 = __msa_pckev_h((v8i16) dst2_l, (v8i16) dst2_r);
    CLIP_SH_0_255(out2);
    PCKEV_B2_SH(out1, out0, out2, out2, out0, out2);
    dst_val0 = __msa_copy_u_d((v2i64) out2, 0);
    ST_SH(out0, dst);
    SD(dst_val0, dst + 16);
    dst += dst_stride;
}