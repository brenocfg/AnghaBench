#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8i16 ;
typedef  int v4i32 ;
struct TYPE_14__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD4 (int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  CLIP_SW8_0_255 (int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ILVR_B8_SW (TYPE_1__,int,TYPE_1__,int,TYPE_1__,int,TYPE_1__,int,TYPE_1__,int,TYPE_1__,int,TYPE_1__,int,TYPE_1__,int,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  ILVR_H4_SW (TYPE_1__,int,TYPE_1__,int,TYPE_1__,int,TYPE_1__,int,int,int,int,int) ; 
 int /*<<< orphan*/  LD_SH8 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SW8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  PCKEV_B2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_H4_SH (int,int,int,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ST_D8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_W8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSPOSE4x4_SW_SW (int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  UNPCK_R_SH_SW (int /*<<< orphan*/ ,int) ; 

void ff_vc1_inv_trans_4x8_msa(uint8_t *dest, ptrdiff_t linesize, int16_t *block)
{
    v8i16 in0, in1, in2, in3, in4, in5, in6, in7;
    v4i32 in_r0, in_r1, in_r2, in_r3, in_r4, in_r5, in_r6, in_r7;
    v4i32 t1, t2, t3, t4, t5, t6, t7, t8;
    v4i32 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;
    v16i8 zero_m = { 0 };
    v4i32 cnst_17 = {17, 17, 17, 17};
    v4i32 cnst_22 = {22, 22, 22, 22};
    v4i32 cnst_10 = {10, 10, 10, 10};
    v4i32 cnst_12 = {12, 12, 12, 12};
    v4i32 cnst_64 = {64, 64, 64, 64};
    v4i32 cnst_16 = {16, 16, 16, 16};
    v4i32 cnst_15 = {15, 15, 15, 15};
    v4i32 cnst_4 = {4, 4, 4, 4};
    v4i32 cnst_6 = {6, 6, 6, 6};
    v4i32 cnst_9 = {9, 9, 9, 9};
    v4i32 cnst_1 = {1, 1, 1, 1};

    LD_SH8(block, 8, in0, in1, in2, in3, in4, in5, in6, in7);
    UNPCK_R_SH_SW(in0, in_r0);
    UNPCK_R_SH_SW(in1, in_r1);
    UNPCK_R_SH_SW(in2, in_r2);
    UNPCK_R_SH_SW(in3, in_r3);
    UNPCK_R_SH_SW(in4, in_r4);
    UNPCK_R_SH_SW(in5, in_r5);
    UNPCK_R_SH_SW(in6, in_r6);
    UNPCK_R_SH_SW(in7, in_r7);
    // First loop
    TRANSPOSE4x4_SW_SW(in_r0, in_r1, in_r2, in_r3, in_r0, in_r1, in_r2, in_r3);
    TRANSPOSE4x4_SW_SW(in_r4, in_r5, in_r6, in_r7, in_r4, in_r5, in_r6, in_r7);
    t1 = cnst_17 * (in_r0 + in_r2) + cnst_4;
    t5 = cnst_17 * (in_r4 + in_r6) + cnst_4;
    t2 = cnst_17 * (in_r0 - in_r2) + cnst_4;
    t6 = cnst_17 * (in_r4 - in_r6) + cnst_4;
    t3 = cnst_22 * in_r1 + cnst_10 * in_r3;
    t7 = cnst_22 * in_r5 + cnst_10 * in_r7;
    t4 = cnst_22 * in_r3 - cnst_10 * in_r1;
    t8 = cnst_22 * in_r7 - cnst_10 * in_r5;

    in_r0 = (t1 + t3) >> 3;
    in_r4 = (t5 + t7) >> 3;
    in_r1 = (t2 - t4) >> 3;
    in_r5 = (t6 - t8) >> 3;
    in_r2 = (t2 + t4) >> 3;
    in_r6 = (t6 + t8) >> 3;
    in_r3 = (t1 - t3) >> 3;
    in_r7 = (t5 - t7) >> 3;
    TRANSPOSE4x4_SW_SW(in_r0, in_r1, in_r2, in_r3, in_r0, in_r1, in_r2, in_r3);
    TRANSPOSE4x4_SW_SW(in_r4, in_r5, in_r6, in_r7, in_r4, in_r5, in_r6, in_r7);
    PCKEV_H4_SH(in_r1, in_r0, in_r3, in_r2, in_r5, in_r4, in_r7, in_r6,
                in0, in1, in2, in3);
    ST_D8(in0, in1, in2, in3, 0, 1, 0, 1, 0, 1, 0, 1, block, 8);
    // Second loop
    t1 = cnst_12 * (in_r0 + in_r4) + cnst_64;
    t2 = cnst_12 * (in_r0 - in_r4) + cnst_64;
    t3 = cnst_16 * in_r2 + cnst_6 * in_r6;
    t4 = cnst_6 * in_r2 - cnst_16 * in_r6;
    t5 = t1 + t3, t6 = t2 + t4;
    t7 = t2 - t4, t8 = t1 - t3;
    t1 = cnst_16 * in_r1 + cnst_15 * in_r3 + cnst_9 * in_r5 + cnst_4 * in_r7;
    t2 = cnst_15 * in_r1 - cnst_4 * in_r3 - cnst_16 * in_r5 - cnst_9 * in_r7;
    t3 = cnst_9 * in_r1 - cnst_16 * in_r3 + cnst_4 * in_r5 + cnst_15 * in_r7;
    t4 = cnst_4 * in_r1 - cnst_9 * in_r3 + cnst_15 * in_r5 - cnst_16 * in_r7;
    LD_SW8(dest, linesize, dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7);
    ILVR_B8_SW(zero_m, dst0, zero_m, dst1, zero_m, dst2, zero_m, dst3,
               zero_m, dst4, zero_m, dst5, zero_m, dst6, zero_m, dst7,
               dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7);
    ILVR_H4_SW(zero_m, dst0, zero_m, dst1, zero_m, dst2, zero_m, dst3,
               dst0, dst1, dst2, dst3);
    ILVR_H4_SW(zero_m, dst4, zero_m, dst5, zero_m, dst6, zero_m, dst7,
               dst4, dst5, dst6, dst7);
    in_r0 = (t5 + t1) >> 7;
    in_r1 = (t6 + t2) >> 7;
    in_r2 = (t7 + t3) >> 7;
    in_r3 = (t8 + t4) >> 7;
    in_r4 = (t8 - t4 + cnst_1) >> 7;
    in_r5 = (t7 - t3 + cnst_1) >> 7;
    in_r6 = (t6 - t2 + cnst_1) >> 7;
    in_r7 = (t5 - t1 + cnst_1) >> 7;
    ADD4(in_r0, dst0, in_r1, dst1, in_r2, dst2, in_r3, dst3,
         in_r0, in_r1, in_r2, in_r3);
    ADD4(in_r4, dst4, in_r5, dst5, in_r6, dst6, in_r7, dst7,
         in_r4, in_r5, in_r6, in_r7);
    CLIP_SW8_0_255(in_r0, in_r1, in_r2, in_r3, in_r4, in_r5, in_r6, in_r7);
    PCKEV_H4_SH(in_r1, in_r0, in_r3, in_r2, in_r5, in_r4, in_r7, in_r6,
                in0, in1, in2, in3);
    PCKEV_B2_SH(in1, in0, in3, in2, in0, in1);
    ST_W8(in0, in1, 0, 1, 2, 3, 0, 1, 2, 3, dest, linesize);
}