#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v16u8 ;
struct TYPE_30__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ILVL_B2_SB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  ILVL_B4_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  ILVL_W2_UB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  ILVR_W2_UB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLDI_B4_UB (TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_UB8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRANSPOSE8x8_UB_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vp9_transpose_16x8_to_8x16(uint8_t *input, int32_t in_pitch,
                                       uint8_t *output, int32_t out_pitch)
{
    v16u8 p7_org, p6_org, p5_org, p4_org, p3_org, p2_org, p1_org, p0_org;
    v16i8 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    v16u8 p7, p6, p5, p4, p3, p2, p1, p0, q0, q1, q2, q3, q4, q5, q6, q7;
    v16i8 zeros = { 0 };

    LD_UB8(input, in_pitch,
           p7_org, p6_org, p5_org, p4_org, p3_org, p2_org, p1_org, p0_org);
    /* 8x8 transpose */
    TRANSPOSE8x8_UB_UB(p7_org, p6_org, p5_org, p4_org, p3_org, p2_org, p1_org,
                       p0_org, p7, p6, p5, p4, p3, p2, p1, p0);
    /* 8x8 transpose */
    ILVL_B4_SB(p5_org, p7_org, p4_org, p6_org, p1_org, p3_org, p0_org, p2_org,
               tmp0, tmp1, tmp2, tmp3);
    ILVR_B2_SB(tmp1, tmp0, tmp3, tmp2, tmp4, tmp6);
    ILVL_B2_SB(tmp1, tmp0, tmp3, tmp2, tmp5, tmp7);
    ILVR_W2_UB(tmp6, tmp4, tmp7, tmp5, q0, q4);
    ILVL_W2_UB(tmp6, tmp4, tmp7, tmp5, q2, q6);
    SLDI_B4_UB(zeros, q0, zeros, q2, zeros, q4, zeros, q6, 8, q1, q3, q5, q7);

    ST_UB8(p7, p6, p5, p4, p3, p2, p1, p0, output, out_pitch);
    output += (8 * out_pitch);
    ST_UB8(q0, q1, q2, q3, q4, q5, q6, q7, output, out_pitch);
}