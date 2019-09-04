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
typedef  int /*<<< orphan*/  ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ILVL_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_B2_SH (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LPF_MASK_HEV (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRANSPOSE16x8_UB_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VP8_MBFILTER (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VP8_ST6x1_UB (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ __msa_fill_b (int) ; 

void ff_vp8_h_loop_filter8uv_msa(uint8_t *src_u, uint8_t *src_v,
                                 ptrdiff_t pitch, int b_limit_in, int limit_in,
                                 int thresh_in)
{
    v16u8 p3, p2, p1, p0, q3, q2, q1, q0;
    v16u8 mask, hev, flat, thresh, limit, b_limit;
    v16u8 row0, row1, row2, row3, row4, row5, row6, row7, row8;
    v16u8 row9, row10, row11, row12, row13, row14, row15;
    v8i16 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;

    b_limit = (v16u8) __msa_fill_b(b_limit_in);
    limit = (v16u8) __msa_fill_b(limit_in);
    thresh = (v16u8) __msa_fill_b(thresh_in);

    LD_UB8(src_u - 4, pitch, row0, row1, row2, row3, row4, row5, row6, row7);
    LD_UB8(src_v - 4, pitch,
           row8, row9, row10, row11, row12, row13, row14, row15);
    TRANSPOSE16x8_UB_UB(row0, row1, row2, row3, row4, row5, row6, row7,
                        row8, row9, row10, row11, row12, row13, row14, row15,
                        p3, p2, p1, p0, q0, q1, q2, q3);

    LPF_MASK_HEV(p3, p2, p1, p0, q0, q1, q2, q3, limit, b_limit, thresh,
                 hev, mask, flat);
    VP8_MBFILTER(p2, p1, p0, q0, q1, q2, mask, hev);

    ILVR_B2_SH(p1, p2, q0, p0, tmp0, tmp1);
    ILVRL_H2_SH(tmp1, tmp0, tmp3, tmp4);
    ILVL_B2_SH(p1, p2, q0, p0, tmp0, tmp1);
    ILVRL_H2_SH(tmp1, tmp0, tmp6, tmp7);
    ILVRL_B2_SH(q2, q1, tmp2, tmp5);

    src_u -= 3;
    VP8_ST6x1_UB(tmp3, 0, tmp2, 0, src_u, 4);
    src_u += pitch;
    VP8_ST6x1_UB(tmp3, 1, tmp2, 1, src_u, 4);
    src_u += pitch;
    VP8_ST6x1_UB(tmp3, 2, tmp2, 2, src_u, 4);
    src_u += pitch;
    VP8_ST6x1_UB(tmp3, 3, tmp2, 3, src_u, 4);
    src_u += pitch;
    VP8_ST6x1_UB(tmp4, 0, tmp2, 4, src_u, 4);
    src_u += pitch;
    VP8_ST6x1_UB(tmp4, 1, tmp2, 5, src_u, 4);
    src_u += pitch;
    VP8_ST6x1_UB(tmp4, 2, tmp2, 6, src_u, 4);
    src_u += pitch;
    VP8_ST6x1_UB(tmp4, 3, tmp2, 7, src_u, 4);

    src_v -= 3;
    VP8_ST6x1_UB(tmp6, 0, tmp5, 0, src_v, 4);
    src_v += pitch;
    VP8_ST6x1_UB(tmp6, 1, tmp5, 1, src_v, 4);
    src_v += pitch;
    VP8_ST6x1_UB(tmp6, 2, tmp5, 2, src_v, 4);
    src_v += pitch;
    VP8_ST6x1_UB(tmp6, 3, tmp5, 3, src_v, 4);
    src_v += pitch;
    VP8_ST6x1_UB(tmp7, 0, tmp5, 4, src_v, 4);
    src_v += pitch;
    VP8_ST6x1_UB(tmp7, 1, tmp5, 5, src_v, 4);
    src_v += pitch;
    VP8_ST6x1_UB(tmp7, 2, tmp5, 6, src_v, 4);
    src_v += pitch;
    VP8_ST6x1_UB(tmp7, 3, tmp5, 7, src_v, 4);
}