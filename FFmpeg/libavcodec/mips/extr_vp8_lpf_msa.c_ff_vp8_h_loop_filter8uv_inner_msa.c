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
typedef  scalar_t__ v4i32 ;
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ILVRL_H2_SW (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B2_SW (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LPF_MASK_HEV (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_W8 (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSPOSE16x8_UB_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VP8_LPF_FILTER4_4W (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_b (int) ; 
 scalar_t__ __msa_ilvl_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_vp8_h_loop_filter8uv_inner_msa(uint8_t *src_u, uint8_t *src_v,
                                       ptrdiff_t pitch, int b_limit_in,
                                       int limit_in, int thresh_in)
{
    v16u8 p3, p2, p1, p0, q3, q2, q1, q0;
    v16u8 mask, hev, flat, thresh, limit, b_limit;
    v16u8 row0, row1, row2, row3, row4, row5, row6, row7, row8;
    v16u8 row9, row10, row11, row12, row13, row14, row15;
    v4i32 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5;

    thresh = (v16u8) __msa_fill_b(thresh_in);
    limit = (v16u8) __msa_fill_b(limit_in);
    b_limit = (v16u8) __msa_fill_b(b_limit_in);

    LD_UB8(src_u - 4, pitch, row0, row1, row2, row3, row4, row5, row6, row7);
    LD_UB8(src_v - 4, pitch,
           row8, row9, row10, row11, row12, row13, row14, row15);
    TRANSPOSE16x8_UB_UB(row0, row1, row2, row3, row4, row5, row6, row7,
                        row8, row9, row10, row11, row12, row13, row14, row15,
                        p3, p2, p1, p0, q0, q1, q2, q3);

    LPF_MASK_HEV(p3, p2, p1, p0, q0, q1, q2, q3, limit, b_limit, thresh,
                 hev, mask, flat);
    VP8_LPF_FILTER4_4W(p1, p0, q0, q1, mask, hev);
    ILVR_B2_SW(p0, p1, q1, q0, tmp0, tmp1);
    ILVRL_H2_SW(tmp1, tmp0, tmp2, tmp3);
    tmp0 = (v4i32) __msa_ilvl_b((v16i8) p0, (v16i8) p1);
    tmp1 = (v4i32) __msa_ilvl_b((v16i8) q1, (v16i8) q0);
    ILVRL_H2_SW(tmp1, tmp0, tmp4, tmp5);

    ST_W8(tmp2, tmp3, 0, 1, 2, 3, 0, 1, 2, 3, src_u - 2, pitch);
    ST_W8(tmp4, tmp5, 0, 1, 2, 3, 0, 1, 2, 3, src_v - 2, pitch);
}