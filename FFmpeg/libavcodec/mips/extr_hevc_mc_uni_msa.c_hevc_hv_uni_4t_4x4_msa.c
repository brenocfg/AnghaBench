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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_FILT_4TAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEVC_FILT_4TAP_SH (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LD_SB (scalar_t__) ; 
 int /*<<< orphan*/  LD_SB7 (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_XORI128_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_SH2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SPLATI_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLATI_W2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRARI_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SRA_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_W4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  UNPCK_R_SB_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VSHF_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B7_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hv_uni_4t_4x4_msa(uint8_t *src,
                                   int32_t src_stride,
                                   uint8_t *dst,
                                   int32_t dst_stride,
                                   const int8_t *filter_x,
                                   const int8_t *filter_y)
{
    v16u8 out;
    v16i8 src0, src1, src2, src3, src4, src5, src6;
    v8i16 filt0, filt1;
    v8i16 filt_h0, filt_h1;
    v16i8 mask0 = LD_SB(ff_hevc_mask_arr + 16);
    v16i8 mask1;
    v16i8 vec0, vec1, vec2, vec3, vec4, vec5, vec6, vec7;
    v8i16 filter_vec, tmp0, tmp1;
    v8i16 dst30, dst41, dst52, dst63;
    v8i16 dst10, dst32, dst54, dst21, dst43, dst65;
    v4i32 dst0, dst1, dst2, dst3;

    src -= (src_stride + 1);

    filter_vec = LD_SH(filter_x);
    SPLATI_H2_SH(filter_vec, 0, 1, filt0, filt1);

    filter_vec = LD_SH(filter_y);
    UNPCK_R_SB_SH(filter_vec, filter_vec);

    SPLATI_W2_SH(filter_vec, 0, filt_h0, filt_h1);

    mask1 = mask0 + 2;

    LD_SB7(src, src_stride, src0, src1, src2, src3, src4, src5, src6);
    XORI_B7_128_SB(src0, src1, src2, src3, src4, src5, src6);

    VSHF_B2_SB(src0, src3, src0, src3, mask0, mask1, vec0, vec1);
    VSHF_B2_SB(src1, src4, src1, src4, mask0, mask1, vec2, vec3);
    VSHF_B2_SB(src2, src5, src2, src5, mask0, mask1, vec4, vec5);
    VSHF_B2_SB(src3, src6, src3, src6, mask0, mask1, vec6, vec7);

    dst30 = HEVC_FILT_4TAP_SH(vec0, vec1, filt0, filt1);
    dst41 = HEVC_FILT_4TAP_SH(vec2, vec3, filt0, filt1);
    dst52 = HEVC_FILT_4TAP_SH(vec4, vec5, filt0, filt1);
    dst63 = HEVC_FILT_4TAP_SH(vec6, vec7, filt0, filt1);

    ILVRL_H2_SH(dst41, dst30, dst10, dst43);
    ILVRL_H2_SH(dst52, dst41, dst21, dst54);
    ILVRL_H2_SH(dst63, dst52, dst32, dst65);
    dst0 = HEVC_FILT_4TAP(dst10, dst32, filt_h0, filt_h1);
    dst1 = HEVC_FILT_4TAP(dst21, dst43, filt_h0, filt_h1);
    dst2 = HEVC_FILT_4TAP(dst32, dst54, filt_h0, filt_h1);
    dst3 = HEVC_FILT_4TAP(dst43, dst65, filt_h0, filt_h1);
    SRA_4V(dst0, dst1, dst2, dst3, 6);
    PCKEV_H2_SH(dst1, dst0, dst3, dst2, tmp0, tmp1);
    SRARI_H2_SH(tmp0, tmp1, 6);
    SAT_SH2_SH(tmp0, tmp1, 7);
    out = PCKEV_XORI128_UB(tmp0, tmp1);
    ST_W4(out, 0, 1, 2, 3, dst, dst_stride);
}