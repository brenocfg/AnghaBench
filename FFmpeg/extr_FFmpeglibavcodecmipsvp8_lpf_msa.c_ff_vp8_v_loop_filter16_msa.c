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
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LPF_MASK_HEV (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_UB2 (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ST_UB4 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VP8_MBFILTER (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_b (int) ; 

void ff_vp8_v_loop_filter16_msa(uint8_t *src, ptrdiff_t pitch, int b_limit_in,
                                int limit_in, int thresh_in)
{
    uint8_t *temp_src;
    v16u8 p3, p2, p1, p0, q3, q2, q1, q0;
    v16u8 mask, hev, flat, thresh, limit, b_limit;

    b_limit = (v16u8) __msa_fill_b(b_limit_in);
    limit = (v16u8) __msa_fill_b(limit_in);
    thresh = (v16u8) __msa_fill_b(thresh_in);
    /* load vector elements */
    temp_src = src - (pitch << 2);
    LD_UB8(temp_src, pitch, p3, p2, p1, p0, q0, q1, q2, q3);
    LPF_MASK_HEV(p3, p2, p1, p0, q0, q1, q2, q3, limit, b_limit, thresh,
                 hev, mask, flat);
    VP8_MBFILTER(p2, p1, p0, q0, q1, q2, mask, hev);
    /* store vector elements */
    temp_src = src - 3 * pitch;
    ST_UB4(p2, p1, p0, q0, temp_src, pitch);
    temp_src += (4 * pitch);
    ST_UB2(q1, q2, temp_src, pitch);
}