#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_74__   TYPE_1__ ;

/* Type definitions */
struct TYPE_74__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v8i16 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  LD_SH8 (int /*<<< orphan*/ *,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  SRARI_H4_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int) ; 
 int /*<<< orphan*/  ST_SH8 (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRANSPOSE8x8_SH_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  VP9_ADDBLK_ST8x4_UB (int /*<<< orphan*/ *,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  VP9_IADST8x8_1D (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  VP9_IDCT8x8_1D (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 

__attribute__((used)) static void vp9_idct_iadst_8x8_add_msa(int16_t *input, uint8_t *dst,
                                       int32_t dst_stride, int32_t eob)
{
    v8i16 in0, in1, in2, in3, in4, in5, in6, in7;
    v8i16 zero = { 0 };

    /* load vector elements of 8x8 block */
    LD_SH8(input, 8, in0, in1, in2, in3, in4, in5, in6, in7);
    ST_SH8(zero, zero, zero, zero, zero, zero, zero, zero, input, 8);

    /* 1D idct8x8 */
    VP9_IDCT8x8_1D(in0, in1, in2, in3, in4, in5, in6, in7,
                   in0, in1, in2, in3, in4, in5, in6, in7);
    /* columns transform */
    TRANSPOSE8x8_SH_SH(in0, in1, in2, in3, in4, in5, in6, in7,
                       in1, in6, in3, in4, in5, in2, in7, in0);
    /* 1D idct8x8 */
    VP9_IADST8x8_1D(in0, in1, in2, in3, in4, in5, in6, in7,
                    in0, in1, in2, in3, in4, in5, in6, in7);
    /* final rounding (add 2^4, divide by 2^5) and shift */
    SRARI_H4_SH(in0, in1, in2, in3, 5);
    SRARI_H4_SH(in4, in5, in6, in7, 5);
    /* add block and store 8x8 */
    VP9_ADDBLK_ST8x4_UB(dst, dst_stride, in0, in1, in2, in3);
    dst += (4 * dst_stride);
    VP9_ADDBLK_ST8x4_UB(dst, dst_stride, in4, in5, in6, in7);
}