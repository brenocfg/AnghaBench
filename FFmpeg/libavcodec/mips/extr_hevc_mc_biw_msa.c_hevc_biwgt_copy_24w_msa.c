#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8i16 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  int /*<<< orphan*/  v16u8 ;
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_BIW_RND_CLIP4_MAX_SATU (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_B2_SH (TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  LD_SH4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_B3_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLLI_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_D4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_UB4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __msa_fill_w (int) ; 

__attribute__((used)) static void hevc_biwgt_copy_24w_msa(uint8_t *src0_ptr,
                                    int32_t src_stride,
                                    int16_t *src1_ptr,
                                    int32_t src2_stride,
                                    uint8_t *dst,
                                    int32_t dst_stride,
                                    int32_t height,
                                    int32_t weight0,
                                    int32_t weight1,
                                    int32_t offset0,
                                    int32_t offset1,
                                    int32_t rnd_val)
{
    uint32_t loop_cnt;
    int32_t offset, weight;
    v16u8 out0, out1, out2, out3, out4, out5;
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7, zero = { 0 };
    v8i16 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7, dst8, dst9, dst10;
    v8i16 in0, in1, in2, in3, in4, in5, in6, in7, in8, in9, in10, in11, dst11;
    v4i32 offset_vec, weight_vec, rnd_vec;

    offset = (offset0 + offset1) << rnd_val;
    weight0 = weight0 & 0x0000FFFF;
    weight = weight0 | (weight1 << 16);

    offset_vec = __msa_fill_w(offset);
    weight_vec = __msa_fill_w(weight);
    rnd_vec = __msa_fill_w(rnd_val + 1);

    for (loop_cnt = 8; loop_cnt--;) {
        LD_SB4(src0_ptr, src_stride, src0, src1, src4, src5);
        LD_SB4(src0_ptr + 16, src_stride, src2, src3, src6, src7);
        src0_ptr += (4 * src_stride);
        LD_SH4(src1_ptr, src2_stride, in0, in1, in2, in3);
        LD_SH4(src1_ptr + 8, src2_stride, in4, in5, in6, in7);
        LD_SH4(src1_ptr + 16, src2_stride, in8, in9, in10, in11);
        src1_ptr += (4 * src2_stride);

        ILVRL_B2_SH(zero, src0, dst0, dst1);
        ILVRL_B2_SH(zero, src1, dst2, dst3);
        ILVR_B2_SH(zero, src2, zero, src3, dst4, dst5);
        ILVRL_B2_SH(zero, src4, dst6, dst7);
        ILVRL_B2_SH(zero, src5, dst8, dst9);
        ILVR_B2_SH(zero, src6, zero, src7, dst10, dst11);
        SLLI_4V(dst0, dst1, dst2, dst3, 6);
        SLLI_4V(dst4, dst5, dst6, dst7, 6);
        SLLI_4V(dst8, dst9, dst10, dst11, 6);
        HEVC_BIW_RND_CLIP4_MAX_SATU(dst0, dst1, dst2, dst3, in0, in4, in1, in5,
                                    weight_vec, rnd_vec, offset_vec, dst0, dst1,
                                    dst2, dst3);
        HEVC_BIW_RND_CLIP4_MAX_SATU(dst4, dst5, dst6, dst7, in8, in9, in2, in6,
                                    weight_vec, rnd_vec, offset_vec, dst4, dst5,
                                    dst6, dst7);
        HEVC_BIW_RND_CLIP4_MAX_SATU(dst8, dst9, dst10, dst11, in3, in7, in10,
                                    in11, weight_vec, rnd_vec, offset_vec,
                                    dst8, dst9, dst10, dst11);
        PCKEV_B3_UB(dst1, dst0, dst3, dst2, dst5, dst4, out0, out1, out2);
        PCKEV_B3_UB(dst7, dst6, dst9, dst8, dst11, dst10, out3, out4, out5);
        ST_UB4(out0, out1, out3, out4, dst, dst_stride);
        ST_D4(out2, out5, 0, 1, 0, 1, dst + 16, dst_stride);
        dst += (4 * dst_stride);
    }
}