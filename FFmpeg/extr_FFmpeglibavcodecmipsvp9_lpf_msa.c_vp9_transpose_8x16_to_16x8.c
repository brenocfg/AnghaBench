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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_UB8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRANSPOSE16x8_UB_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vp9_transpose_8x16_to_16x8(uint8_t *input, int32_t in_pitch,
                                       uint8_t *output, int32_t out_pitch)
{
    v16u8 p7_o, p6_o, p5_o, p4_o, p3_o, p2_o, p1_o, p0_o;
    v16u8 p7, p6, p5, p4, p3, p2, p1, p0, q0, q1, q2, q3, q4, q5, q6, q7;

    LD_UB8(input, in_pitch, p7, p6, p5, p4, p3, p2, p1, p0);
    LD_UB8(input + (8 * in_pitch), in_pitch, q0, q1, q2, q3, q4, q5, q6, q7);
    TRANSPOSE16x8_UB_UB(p7, p6, p5, p4, p3, p2, p1, p0, q0, q1, q2, q3, q4, q5,
                        q6, q7, p7_o, p6_o, p5_o, p4_o, p3_o, p2_o, p1_o, p0_o);
    ST_UB8(p7_o, p6_o, p5_o, p4_o, p3_o, p2_o, p1_o, p0_o, output, out_pitch);
}