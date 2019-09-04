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
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  HEVC_IDCT_LUMA4x4_COL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ILVRL_H2_SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_W2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SH2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_SH2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRANSPOSE4x4_SW_SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNPCK_SH_SW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hevc_idct_luma_4x4_msa(int16_t *coeffs)
{
    v8i16 in0, in1, dst0, dst1;
    v4i32 in_r0, in_l0, in_r1, in_l1, res0, res1, res2, res3;

    LD_SH2(coeffs, 8, in0, in1);
    UNPCK_SH_SW(in0, in_r0, in_l0);
    UNPCK_SH_SW(in1, in_r1, in_l1);
    HEVC_IDCT_LUMA4x4_COL(in_r0, in_l0, in_r1, in_l1, res0, res1, res2, res3,
                          7);
    TRANSPOSE4x4_SW_SW(res0, res1, res2, res3, in_r0, in_l0, in_r1, in_l1);
    HEVC_IDCT_LUMA4x4_COL(in_r0, in_l0, in_r1, in_l1, res0, res1, res2, res3,
                          12);

    /* Pack and transpose */
    PCKEV_H2_SH(res2, res0, res3, res1, dst0, dst1);
    ILVRL_H2_SW(dst1, dst0, res0, res1);
    ILVRL_W2_SH(res1, res0, dst0, dst1);

    ST_SH2(dst0, dst1, coeffs, 8);
}