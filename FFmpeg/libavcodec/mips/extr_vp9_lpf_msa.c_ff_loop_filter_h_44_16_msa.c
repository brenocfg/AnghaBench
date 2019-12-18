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
typedef  int /*<<< orphan*/  v2i64 ;
typedef  scalar_t__ v16u8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ILVL_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVRL_H2_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B2_SH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB8 (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LPF_MASK_HEV (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ST_W8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TRANSPOSE16x8_UB_UB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  VP9_LPF_FILTER4_4W (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ __msa_fill_b (int) ; 
 scalar_t__ __msa_ilvr_d (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ff_loop_filter_h_44_16_msa(uint8_t *src, ptrdiff_t pitch,
                                int32_t b_limit_ptr,
                                int32_t limit_ptr,
                                int32_t thresh_ptr)
{
    v16u8 mask, hev, flat;
    v16u8 thresh0, b_limit0, limit0, thresh1, b_limit1, limit1;
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

    thresh0 = (v16u8) __msa_fill_b(thresh_ptr);
    thresh1 = (v16u8) __msa_fill_b(thresh_ptr >> 8);
    thresh0 = (v16u8) __msa_ilvr_d((v2i64) thresh1, (v2i64) thresh0);

    b_limit0 = (v16u8) __msa_fill_b(b_limit_ptr);
    b_limit1 = (v16u8) __msa_fill_b(b_limit_ptr >> 8);
    b_limit0 = (v16u8) __msa_ilvr_d((v2i64) b_limit1, (v2i64) b_limit0);

    limit0 = (v16u8) __msa_fill_b(limit_ptr);
    limit1 = (v16u8) __msa_fill_b(limit_ptr >> 8);
    limit0 = (v16u8) __msa_ilvr_d((v2i64) limit1, (v2i64) limit0);

    LPF_MASK_HEV(p3, p2, p1, p0, q0, q1, q2, q3, limit0, b_limit0, thresh0,
                 hev, mask, flat);
    VP9_LPF_FILTER4_4W(p1, p0, q0, q1, mask, hev, p1, p0, q0, q1);
    ILVR_B2_SH(p0, p1, q1, q0, tmp0, tmp1);
    ILVRL_H2_SH(tmp1, tmp0, tmp2, tmp3);
    ILVL_B2_SH(p0, p1, q1, q0, tmp0, tmp1);
    ILVRL_H2_SH(tmp1, tmp0, tmp4, tmp5);

    src -= 2;

    ST_W8(tmp2, tmp3, 0, 1, 2, 3, 0, 1, 2, 3, src, pitch);
    ST_W8(tmp4, tmp5, 0, 1, 2, 3, 0, 1, 2, 3, src + 8 * pitch, pitch);
}