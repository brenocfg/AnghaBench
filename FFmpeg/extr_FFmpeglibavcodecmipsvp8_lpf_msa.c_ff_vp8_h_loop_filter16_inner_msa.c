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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ILVL_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LPF_MASK_HEV (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST4x8_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRANSPOSE16x8_UB_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VP8_LPF_FILTER4_4W (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_b (int /*<<< orphan*/ ) ; 

void ff_vp8_h_loop_filter16_inner_msa(uint8_t *src, ptrdiff_t pitch,
                                      int32_t e, int32_t i, int32_t h)
{
    v16u8 mask, hev, flat;
    v16u8 thresh, b_limit, limit;
    v16u8 p3, p2, p1, p0, q3, q2, q1, q0;
    v16u8 row0, row1, row2, row3, row4, row5, row6, row7;
    v16u8 row8, row9, row10, row11, row12, row13, row14, row15;
    v8i16 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5;

    LD_UB8(src - 4, pitch, row0, row1, row2, row3, row4, row5, row6, row7);
    LD_UB8(src - 4 + (8 * pitch), pitch,
           row8, row9, row10, row11, row12, row13, row14, row15);
    TRANSPOSE16x8_UB_UB(row0, row1, row2, row3, row4, row5, row6, row7,
                        row8, row9, row10, row11, row12, row13, row14, row15,
                        p3, p2, p1, p0, q0, q1, q2, q3);

    thresh = (v16u8) __msa_fill_b(h);
    b_limit = (v16u8) __msa_fill_b(e);
    limit = (v16u8) __msa_fill_b(i);

    LPF_MASK_HEV(p3, p2, p1, p0, q0, q1, q2, q3, limit, b_limit, thresh,
                 hev, mask, flat);
    VP8_LPF_FILTER4_4W(p1, p0, q0, q1, mask, hev);
    ILVR_B2_SH(p0, p1, q1, q0, tmp0, tmp1);
    ILVRL_H2_SH(tmp1, tmp0, tmp2, tmp3);
    ILVL_B2_SH(p0, p1, q1, q0, tmp0, tmp1);
    ILVRL_H2_SH(tmp1, tmp0, tmp4, tmp5);

    src -= 2;
    ST4x8_UB(tmp2, tmp3, src, pitch);
    src += (8 * pitch);
    ST4x8_UB(tmp4, tmp5, src, pitch);
}