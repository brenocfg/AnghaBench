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
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  LD_UB4 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_UB2 (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VP8_SIMPLE_FILT (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VP8_SIMPLE_MASK (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_b (int) ; 

void ff_vp8_v_loop_filter_simple_msa(uint8_t *src, ptrdiff_t pitch,
                                     int b_limit_ptr)
{
    v16u8 p1, p0, q1, q0;
    v16u8 mask, b_limit;

    b_limit = (v16u8) __msa_fill_b(b_limit_ptr);
    /* load vector elements */
    LD_UB4(src - (pitch << 1), pitch, p1, p0, q0, q1);
    VP8_SIMPLE_MASK(p1, p0, q0, q1, b_limit, mask);
    VP8_SIMPLE_FILT(p1, p0, q0, q1, mask);
    ST_UB2(p0, q0, (src - pitch), pitch);
}