#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8i16 ;
typedef  int /*<<< orphan*/  v16u8 ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_BI_RND_CLIP4_MAX_SATU (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_B2_SH (TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  LD_SH4 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_B2_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLLI_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_UB4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hevc_bi_copy_16w_msa(uint8_t *src0_ptr,
                                 int32_t src_stride,
                                 int16_t *src1_ptr,
                                 int32_t src2_stride,
                                 uint8_t *dst,
                                 int32_t dst_stride,
                                 int32_t height)
{
    uint32_t loop_cnt;
    v16u8 out0, out1, out2, out3;
    v16i8 src0, src1, src2, src3;
    v8i16 in0, in1, in2, in3, in4, in5, in6, in7;
    v8i16 dst0_r, dst1_r, dst2_r, dst3_r, dst0_l, dst1_l, dst2_l, dst3_l;
    v16i8 zero = { 0 };

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_SB4(src0_ptr, src_stride, src0, src1, src2, src3);
        src0_ptr += (4 * src_stride);
        LD_SH4(src1_ptr, src2_stride, in0, in1, in2, in3);
        LD_SH4(src1_ptr + 8, src2_stride, in4, in5, in6, in7);
        src1_ptr += (4 * src2_stride);
        ILVRL_B2_SH(zero, src0, dst0_r, dst0_l);
        ILVRL_B2_SH(zero, src1, dst1_r, dst1_l);
        ILVRL_B2_SH(zero, src2, dst2_r, dst2_l);
        ILVRL_B2_SH(zero, src3, dst3_r, dst3_l);
        SLLI_4V(dst0_r, dst1_r, dst2_r, dst3_r, 6);
        SLLI_4V(dst0_l, dst1_l, dst2_l, dst3_l, 6);
        HEVC_BI_RND_CLIP4_MAX_SATU(in0, in1, in4, in5, dst0_r, dst1_r, dst0_l,
                                   dst1_l, 7, dst0_r, dst1_r, dst0_l, dst1_l);
        HEVC_BI_RND_CLIP4_MAX_SATU(in2, in3, in6, in7, dst2_r, dst3_r, dst2_l,
                                   dst3_l, 7, dst2_r, dst3_r, dst2_l, dst3_l);
        PCKEV_B2_UB(dst0_l, dst0_r, dst1_l, dst1_r, out0, out1);
        PCKEV_B2_UB(dst2_l, dst2_r, dst3_l, dst3_r, out2, out3);
        ST_UB4(out0, out1, out2, out3, dst, dst_stride);
        dst += (4 * dst_stride);
    }
}