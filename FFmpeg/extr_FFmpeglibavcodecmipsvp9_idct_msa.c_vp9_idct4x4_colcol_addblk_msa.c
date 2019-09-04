#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_1__ ;

/* Type definitions */
struct TYPE_32__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v8i16 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDBLK_ST4x4_UB (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD4x4_SH (int /*<<< orphan*/ *,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SRARI_H4_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int) ; 
 int /*<<< orphan*/  ST_SH2 (TYPE_1__,TYPE_1__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRANSPOSE4x4_SH_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  VP9_IDCT4x4 (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 

__attribute__((used)) static void vp9_idct4x4_colcol_addblk_msa(int16_t *input, uint8_t *dst,
                                          int32_t dst_stride)
{
    v8i16 in0, in1, in2, in3;
    v8i16 zero = { 0 };

    /* load vector elements of 4x4 block */
    LD4x4_SH(input, in0, in1, in2, in3);
    ST_SH2(zero, zero, input, 8);
    /* rows */
    VP9_IDCT4x4(in0, in1, in2, in3, in0, in1, in2, in3);
    /* columns */
    TRANSPOSE4x4_SH_SH(in0, in1, in2, in3, in0, in1, in2, in3);
    VP9_IDCT4x4(in0, in1, in2, in3, in0, in1, in2, in3);
    /* rounding (add 2^3, divide by 2^4) */
    SRARI_H4_SH(in0, in1, in2, in3, 4);
    ADDBLK_ST4x4_UB(in0, in1, in2, in3, dst, dst_stride);
}