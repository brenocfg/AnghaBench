#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8i16 ;
struct TYPE_29__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ILVL_B2_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVL_B4_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B4_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB3 (int /*<<< orphan*/ *,int,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SLLI_4V (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ST_SH6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void hevc_copy_48w_msa(uint8_t *src, int32_t src_stride,
                              int16_t *dst, int32_t dst_stride,
                              int32_t height)
{
    uint32_t loop_cnt;
    v16i8 zero = { 0 };
    v16i8 src0, src1, src2, src3, src4, src5, src6, src7;
    v16i8 src8, src9, src10, src11;
    v8i16 in0_r, in1_r, in2_r, in3_r, in4_r, in5_r;
    v8i16 in0_l, in1_l, in2_l, in3_l, in4_l, in5_l;

    for (loop_cnt = (height >> 2); loop_cnt--;) {
        LD_SB3(src, 16, src0, src1, src2);
        src += src_stride;
        LD_SB3(src, 16, src3, src4, src5);
        src += src_stride;
        LD_SB3(src, 16, src6, src7, src8);
        src += src_stride;
        LD_SB3(src, 16, src9, src10, src11);
        src += src_stride;

        ILVR_B4_SH(zero, src0, zero, src1, zero, src2, zero, src3,
                   in0_r, in1_r, in2_r, in3_r);
        ILVL_B4_SH(zero, src0, zero, src1, zero, src2, zero, src3,
                   in0_l, in1_l, in2_l, in3_l);
        ILVR_B2_SH(zero, src4, zero, src5, in4_r, in5_r);
        ILVL_B2_SH(zero, src4, zero, src5, in4_l, in5_l);
        SLLI_4V(in0_r, in1_r, in2_r, in3_r, 6);
        SLLI_4V(in0_l, in1_l, in2_l, in3_l, 6);
        SLLI_4V(in4_r, in5_r, in4_l, in5_l, 6);
        ST_SH6(in0_r, in0_l, in1_r, in1_l, in2_r, in2_l, dst, 8);
        dst += dst_stride;
        ST_SH6(in3_r, in3_l, in4_r, in4_l, in5_r, in5_l, dst, 8);
        dst += dst_stride;

        ILVR_B4_SH(zero, src6, zero, src7, zero, src8, zero, src9,
                   in0_r, in1_r, in2_r, in3_r);
        ILVL_B4_SH(zero, src6, zero, src7, zero, src8, zero, src9,
                   in0_l, in1_l, in2_l, in3_l);
        ILVR_B2_SH(zero, src10, zero, src11, in4_r, in5_r);
        ILVL_B2_SH(zero, src10, zero, src11, in4_l, in5_l);
        SLLI_4V(in0_r, in1_r, in2_r, in3_r, 6);
        SLLI_4V(in0_l, in1_l, in2_l, in3_l, 6);
        SLLI_4V(in4_r, in5_r, in4_l, in5_l, 6);
        ST_SH6(in0_r, in0_l, in1_r, in1_l, in2_r, in2_l, dst, 8);
        dst += dst_stride;
        ST_SH6(in3_r, in3_l, in4_r, in4_l, in5_r, in5_l, dst, 8);
        dst += dst_stride;
    }
}