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
typedef  int v4i32 ;
typedef  scalar_t__ v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_SH_0_255 (int) ; 
 int HEVC_FILT_4TAP (int,int,int,int) ; 
 int HEVC_FILT_4TAP_SH (scalar_t__,scalar_t__,int,int) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (int,int,int,int) ; 
 int /*<<< orphan*/  INSERT_D2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LD2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_SB (scalar_t__) ; 
 int /*<<< orphan*/  LD_SB5 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  SPLATI_W2_SH (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SRAR_W2_SW (int,int,int) ; 
 int /*<<< orphan*/  ST_W2 (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  UNPCK_R_SB_SH (int,int) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B5_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int __msa_dpadd_s_w (int,int,int) ; 
 int __msa_fill_w (int) ; 
 scalar_t__ __msa_pckev_b (scalar_t__,scalar_t__) ; 
 int __msa_pckev_h (int,int) ; 
 scalar_t__ ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hv_biwgt_4t_4x2_msa(uint8_t *src0_ptr,
                                     int32_t src_stride,
                                     int16_t *src1_ptr,
                                     int32_t src2_stride,
                                     uint8_t *dst,
                                     int32_t dst_stride,
                                     const int8_t *filter_x,
                                     const int8_t *filter_y,
                                     int32_t weight0,
                                     int32_t weight1,
                                     int32_t offset0,
                                     int32_t offset1,
                                     int32_t rnd_val)
{
    uint64_t tp0, tp1;
    int32_t offset, weight;
    v8i16 in0 = { 0 };
    v16u8 out;
    v16i8 src0, src1, src2, src3, src4;
    v8i16 filt0, filt1;
    v8i16 filt_h0, filt_h1;
    v16i8 mask0 = LD_SB(ff_hevc_mask_arr + 16);
    v16i8 mask1;
    v8i16 filter_vec, tmp, weight_vec;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5;
    v8i16 dst20, dst31, dst42, dst10, dst32, dst21, dst43, tmp0, tmp1;
    v4i32 dst0, dst1, offset_vec, rnd_vec, const_vec;

    src0_ptr -= (src_stride + 1);

    filter_vec = LD_SH(filter_x);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    filter_vec = LD_SH(filter_y);
    UNPCK_R_SB_SH(filter_vec, filter_vec);

    SPLATI_W2_SH(filter_vec, 0, filt_h0, filt_h1);

    mask1 = mask0 + 2;

    offset = (offset0 + offset1) << rnd_val;
    weight0 = weight0 & 0x0000FFFF;
    weight = weight0 | (weight1 << 16);

    const_vec = __msa_fill_w((128 * weight1));
    const_vec <<= 6;
    offset_vec = __msa_fill_w(offset);
    weight_vec = (v8i16) __msa_fill_w(weight);
    rnd_vec = __msa_fill_w(rnd_val + 1);
    offset_vec += const_vec;

    LD_SB5(src0_ptr, src_stride, src0, src1, src2, src3, src4);
    XORI_B5_128_SB(src0, src1, src2, src3, src4);

    VSHF_B2_SB(src0, src2, src0, src2, mask0, mask1, vec0, vec1);
    VSHF_B2_SB(src1, src3, src1, src3, mask0, mask1, vec2, vec3);
    VSHF_B2_SB(src2, src4, src2, src4, mask0, mask1, vec4, vec5);

    dst20 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
    dst31 = HEVC_FILT_4TAP_SH(vec2, vec3, filt0, filt1);
    dst42 = HEVC_FILT_4TAP_SH(vec4, vec5, filt0, filt1);

    ILVRL_H2_SH(dst31, dst20, dst10, dst32);
    ILVRL_H2_SH(dst42, dst31, dst21, dst43);

    dst0 = HEVC_FILT_4TAP(dst10, dst32, filt_h0, filt_h1);
    dst1 = HEVC_FILT_4TAP(dst21, dst43, filt_h0, filt_h1);
    dst0 >>= 6;
    dst1 >>= 6;
    dst0 = (v4i32) __msa_pckev_h((v8i16) dst1, (v8i16) dst0);

    LD2(src1_ptr, src2_stride, tp0, tp1);
    INSERT_D2_SH(tp0, tp1, in0);

    ILVRL_H2_SH(dst0, in0, tmp0, tmp1);
    dst0 = __msa_dpadd_s_w(offset_vec, tmp0, weight_vec);
    dst1 = __msa_dpadd_s_w(offset_vec, tmp1, weight_vec);
    SRAR_W2_SW(dst0, dst1, rnd_vec);
    tmp = __msa_pckev_h((v8i16) dst1, (v8i16) dst0);
    CLIP_SH_0_255(tmp);
    out = (v16u8) __msa_pckev_b((v16i8) tmp, (v16i8) tmp);
    ST_W2(out, 0, 1, dst, dst_stride);
}