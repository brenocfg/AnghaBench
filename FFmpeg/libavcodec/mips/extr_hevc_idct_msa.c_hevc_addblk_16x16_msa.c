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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int uint8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLIP_SH8_0_255 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SH4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_UB4 (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_B4_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_UB4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  UNPCK_UB_SH (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void hevc_addblk_16x16_msa(int16_t *coeffs, uint8_t *dst, int32_t stride)
{
    uint8_t loop_cnt;
    uint8_t *temp_dst = dst;
    v16u8 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;
    v8i16 dst_r0, dst_l0, dst_r1, dst_l1, dst_r2, dst_l2, dst_r3, dst_l3;
    v8i16 in0, in1, in2, in3, in4, in5, in6, in7;

    /* Pre-load for next iteration */
    LD_UB4(temp_dst, stride, dst4, dst5, dst6, dst7);
    temp_dst += (4 * stride);
    LD_SH4(coeffs, 16, in0, in2, in4, in6);
    LD_SH4((coeffs + 8), 16, in1, in3, in5, in7);
    coeffs += 64;

    for (loop_cnt = 3; loop_cnt--;) {
        UNPCK_UB_SH(dst4, dst_r0, dst_l0);
        UNPCK_UB_SH(dst5, dst_r1, dst_l1);
        UNPCK_UB_SH(dst6, dst_r2, dst_l2);
        UNPCK_UB_SH(dst7, dst_r3, dst_l3);

        dst_r0 += in0;
        dst_l0 += in1;
        dst_r1 += in2;
        dst_l1 += in3;
        dst_r2 += in4;
        dst_l2 += in5;
        dst_r3 += in6;
        dst_l3 += in7;

        /* Pre-load for next iteration */
        LD_UB4(temp_dst, stride, dst4, dst5, dst6, dst7);
        temp_dst += (4 * stride);
        LD_SH4(coeffs, 16, in0, in2, in4, in6);
        LD_SH4((coeffs + 8), 16, in1, in3, in5, in7);
        coeffs += 64;

        CLIP_SH8_0_255(dst_r0, dst_l0, dst_r1, dst_l1,
                       dst_r2, dst_l2, dst_r3, dst_l3);

        PCKEV_B4_UB(dst_l0, dst_r0, dst_l1, dst_r1, dst_l2, dst_r2, dst_l3,
                    dst_r3, dst0, dst1, dst2, dst3);
        ST_UB4(dst0, dst1, dst2, dst3, dst, stride);
        dst += (4 * stride);
    }

    UNPCK_UB_SH(dst4, dst_r0, dst_l0);
    UNPCK_UB_SH(dst5, dst_r1, dst_l1);
    UNPCK_UB_SH(dst6, dst_r2, dst_l2);
    UNPCK_UB_SH(dst7, dst_r3, dst_l3);

    dst_r0 += in0;
    dst_l0 += in1;
    dst_r1 += in2;
    dst_l1 += in3;
    dst_r2 += in4;
    dst_l2 += in5;
    dst_r3 += in6;
    dst_l3 += in7;

    CLIP_SH8_0_255(dst_r0, dst_l0, dst_r1, dst_l1,
                   dst_r2, dst_l2, dst_r3, dst_l3);
    PCKEV_B4_UB(dst_l0, dst_r0, dst_l1, dst_r1, dst_l2, dst_r2, dst_l3,
                dst_r3, dst0, dst1, dst2, dst3);
    ST_UB4(dst0, dst1, dst2, dst3, dst, stride);
}