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
typedef  int /*<<< orphan*/  v2i64 ;
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LPF_MASK_HEV (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VP9_LPF_FILTER4_4W (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  __msa_copy_u_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __msa_fill_b (int /*<<< orphan*/ ) ; 

void ff_loop_filter_v_4_8_msa(uint8_t *src, ptrdiff_t pitch,
                              int32_t b_limit_ptr,
                              int32_t limit_ptr,
                              int32_t thresh_ptr)
{
    uint64_t p1_d, p0_d, q0_d, q1_d;
    v16u8 mask, hev, flat, thresh, b_limit, limit;
    v16u8 p3, p2, p1, p0, q3, q2, q1, q0, p1_out, p0_out, q0_out, q1_out;

    /* load vector elements */
    LD_UB8((src - 4 * pitch), pitch, p3, p2, p1, p0, q0, q1, q2, q3);

    thresh = (v16u8) __msa_fill_b(thresh_ptr);
    b_limit = (v16u8) __msa_fill_b(b_limit_ptr);
    limit = (v16u8) __msa_fill_b(limit_ptr);

    LPF_MASK_HEV(p3, p2, p1, p0, q0, q1, q2, q3, limit, b_limit, thresh,
                 hev, mask, flat);
    VP9_LPF_FILTER4_4W(p1, p0, q0, q1, mask, hev, p1_out, p0_out, q0_out,
                       q1_out);

    p1_d = __msa_copy_u_d((v2i64) p1_out, 0);
    p0_d = __msa_copy_u_d((v2i64) p0_out, 0);
    q0_d = __msa_copy_u_d((v2i64) q0_out, 0);
    q1_d = __msa_copy_u_d((v2i64) q1_out, 0);
    SD4(p1_d, p0_d, q0_d, q1_d, (src - 2 * pitch), pitch);
}