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
typedef  int /*<<< orphan*/  v4i32 ;
typedef  int /*<<< orphan*/  v2i64 ;
typedef  scalar_t__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_SH_0_255 (int) ; 
 int /*<<< orphan*/  DPADD_SB2_SH (scalar_t__,scalar_t__,int,int,int,int) ; 
 int /*<<< orphan*/  HEVC_BI_RND_CLIP2 (int,int,int,int,int,int,int) ; 
 scalar_t__ LD_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LD_SB2 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int LD_SH (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  LD_SH2 (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SD (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPLATI_H4_SH (int,int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SW (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VSHF_B3_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  XORI_B4_128_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int __msa_adds_s_h (int,int) ; 
 int /*<<< orphan*/  __msa_copy_s_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __msa_copy_s_w (int /*<<< orphan*/ ,int) ; 
 int __msa_dpadd_s_h (int,scalar_t__,scalar_t__) ; 
 int __msa_ldi_h (int) ; 
 scalar_t__ __msa_pckev_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __msa_srari_h (int,int) ; 
 int /*<<< orphan*/ * ff_hevc_mask_arr ; 

__attribute__((used)) static void hevc_hz_bi_8t_12w_msa(uint8_t *src0_ptr,
                                  int32_t src_stride,
                                  int16_t *src1_ptr,
                                  int32_t src2_stride,
                                  uint8_t *dst,
                                  int32_t dst_stride,
                                  const int8_t *filter,
                                  int32_t height)
{
    uint32_t loop_cnt;
    int32_t tmp0, tmp1;
    int64_t tmp2, tmp3;
    v16i8 src0, src1, src2, src3;
    v16i8 vec0, vec1, vec2;
    v8i16 filt0, filt1, filt2, filt3;
    v16i8 mask0, mask1, mask2, mask3, mask4, mask5, mask6, mask7;
    v8i16 dst0, dst1, dst2;
    v8i16 in0, in1, in2, in3;
    v8i16 filter_vec, const_vec;

    src0_ptr -= 3;
    const_vec = __msa_ldi_h(128);
    const_vec <<= 6;

    filter_vec = LD_SH(filter);
    SPLATI_H4_SH(filter_vec, 0, 1, 2, 3, filt0, filt1, filt2, filt3);

    mask0 = LD_SB(ff_hevc_mask_arr);
    mask1 = mask0 + 2;
    mask2 = mask0 + 4;
    mask3 = mask0 + 6;
    mask4 = LD_SB(&ff_hevc_mask_arr[16]);
    mask5 = mask4 + 2;
    mask6 = mask4 + 4;
    mask7 = mask4 + 6;

    for (loop_cnt = 8; loop_cnt--;) {
        LD_SB2(src0_ptr, 8, src0, src1);
        src0_ptr += src_stride;
        LD_SB2(src0_ptr, 8, src2, src3);
        src0_ptr += src_stride;
        LD_SH2(src1_ptr, 8, in0, in1);
        src1_ptr += src2_stride;
        LD_SH2(src1_ptr, 8, in2, in3);
        src1_ptr += src2_stride;
        XORI_B4_128_SB(src0, src1, src2, src3);

        dst0 = const_vec;
        dst1 = const_vec;
        dst2 = const_vec;

        VSHF_B3_SB(src0, src0, src1, src3, src2, src2, mask0, mask4, mask0,
                   vec0, vec1, vec2);
        DPADD_SB2_SH(vec0, vec1, filt0, filt0, dst0, dst1);
        dst2 = __msa_dpadd_s_h(dst2, vec2, (v16i8) filt0);
        VSHF_B3_SB(src0, src0, src1, src3, src2, src2, mask1, mask5, mask1,
                   vec0, vec1, vec2);
        DPADD_SB2_SH(vec0, vec1, filt1, filt1, dst0, dst1);
        dst2 = __msa_dpadd_s_h(dst2, vec2, (v16i8) filt1);
        VSHF_B3_SB(src0, src0, src1, src3, src2, src2, mask2, mask6, mask2,
                   vec0, vec1, vec2);
        DPADD_SB2_SH(vec0, vec1, filt2, filt2, dst0, dst1);
        dst2 = __msa_dpadd_s_h(dst2, vec2, (v16i8) filt2);
        VSHF_B3_SB(src0, src0, src1, src3, src2, src2, mask3, mask7, mask3,
                   vec0, vec1, vec2);
        DPADD_SB2_SH(vec0, vec1, filt3, filt3, dst0, dst1);
        dst2 = __msa_dpadd_s_h(dst2, vec2, (v16i8) filt3);

        in1 = (v8i16) __msa_pckev_d((v2i64) in3, (v2i64) in1);
        HEVC_BI_RND_CLIP2(in0, in1, dst0, dst1, 7, dst0, dst1);
        dst2 = __msa_adds_s_h(in2, dst2);
        dst2 = __msa_srari_h(dst2, 7);
        CLIP_SH_0_255(dst2);
        PCKEV_B2_SH(dst1, dst0, dst2, dst2, dst0, dst1);

        tmp2 = __msa_copy_s_d((v2i64) dst0, 0);
        tmp0 = __msa_copy_s_w((v4i32) dst0, 2);
        tmp3 = __msa_copy_s_d((v2i64) dst1, 0);
        tmp1 = __msa_copy_s_w((v4i32) dst0, 3);
        SD(tmp2, dst);
        SW(tmp0, dst + 8);
        dst += dst_stride;
        SD(tmp3, dst);
        SW(tmp1, dst + 8);
        dst += dst_stride;
    }
}