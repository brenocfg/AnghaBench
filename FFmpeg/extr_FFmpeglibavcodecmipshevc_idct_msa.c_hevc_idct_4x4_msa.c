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
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v8i16 ;
typedef  int /*<<< orphan*/  v4i32 ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_IDCT4x4_COL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ILVRL_H2_SW (TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_W2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  LD_SH2 (int /*<<< orphan*/ *,int,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  PCKEV_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  ST_SH2 (TYPE_1__,TYPE_1__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRANSPOSE4x4_SW_SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hevc_idct_4x4_msa(int16_t *coeffs)
{
    v8i16 in0, in1;
    v4i32 in_r0, in_l0, in_r1, in_l1;
    v4i32 sum0, sum1, sum2, sum3;
    v8i16 zeros = { 0 };

    LD_SH2(coeffs, 8, in0, in1);
    ILVRL_H2_SW(zeros, in0, in_r0, in_l0);
    ILVRL_H2_SW(zeros, in1, in_r1, in_l1);

    HEVC_IDCT4x4_COL(in_r0, in_l0, in_r1, in_l1, sum0, sum1, sum2, sum3, 7);
    TRANSPOSE4x4_SW_SW(sum0, sum1, sum2, sum3, in_r0, in_l0, in_r1, in_l1);
    HEVC_IDCT4x4_COL(in_r0, in_l0, in_r1, in_l1, sum0, sum1, sum2, sum3, 12);

    /* Pack and transpose */
    PCKEV_H2_SH(sum2, sum0, sum3, sum1, in0, in1);
    ILVRL_H2_SW(in1, in0, sum0, sum1);
    ILVRL_W2_SH(sum1, sum0, in0, in1);

    ST_SH2(in0, in1, coeffs, 8);
}