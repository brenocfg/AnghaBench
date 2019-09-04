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
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ILVRL_B2_SH (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST2x4_UB (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRANSPOSE16x4_UB_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VP8_SIMPLE_FILT (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VP8_SIMPLE_MASK (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_b (int) ; 

void ff_vp8_h_loop_filter_simple_msa(uint8_t *src, ptrdiff_t pitch,
                                     int b_limit_ptr)
{
    uint8_t *temp_src;
    v16u8 p1, p0, q1, q0;
    v16u8 mask, b_limit;
    v16u8 row0, row1, row2, row3, row4, row5, row6, row7, row8;
    v16u8 row9, row10, row11, row12, row13, row14, row15;
    v8i16 tmp0, tmp1;

    b_limit = (v16u8) __msa_fill_b(b_limit_ptr);
    temp_src = src - 2;
    LD_UB8(temp_src, pitch, row0, row1, row2, row3, row4, row5, row6, row7);
    temp_src += (8 * pitch);
    LD_UB8(temp_src, pitch,
           row8, row9, row10, row11, row12, row13, row14, row15);
    TRANSPOSE16x4_UB_UB(row0, row1, row2, row3, row4, row5, row6, row7,
                        row8, row9, row10, row11, row12, row13, row14, row15,
                        p1, p0, q0, q1);
    VP8_SIMPLE_MASK(p1, p0, q0, q1, b_limit, mask);
    VP8_SIMPLE_FILT(p1, p0, q0, q1, mask);
    ILVRL_B2_SH(q0, p0, tmp1, tmp0);

    src -= 1;
    ST2x4_UB(tmp1, 0, src, pitch);
    src += 4 * pitch;
    ST2x4_UB(tmp1, 4, src, pitch);
    src += 4 * pitch;
    ST2x4_UB(tmp0, 0, src, pitch);
    src += 4 * pitch;
    ST2x4_UB(tmp0, 4, src, pitch);
    src += 4 * pitch;
}