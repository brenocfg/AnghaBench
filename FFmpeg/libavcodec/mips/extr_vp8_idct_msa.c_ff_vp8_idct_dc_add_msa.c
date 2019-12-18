#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8i16 ;
struct TYPE_19__ {int member_1; int member_2; int member_3; int member_4; int member_5; int member_6; int member_7; int /*<<< orphan*/  member_15; int /*<<< orphan*/  member_14; int /*<<< orphan*/  member_13; int /*<<< orphan*/  member_12; int /*<<< orphan*/  member_11; int /*<<< orphan*/  member_10; int /*<<< orphan*/  member_9; int /*<<< orphan*/  member_8; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int ptrdiff_t ;
typedef  scalar_t__ int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLIP_SH4_0_255 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B4_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB4 (int /*<<< orphan*/ *,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  ST_W2 (TYPE_1__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  VSHF_B2_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  __msa_fill_h (scalar_t__) ; 
 int /*<<< orphan*/  __msa_srari_h (int /*<<< orphan*/ ,int) ; 

void ff_vp8_idct_dc_add_msa(uint8_t *dst, int16_t in_dc[16], ptrdiff_t stride)
{
    v8i16 vec;
    v8i16 res0, res1, res2, res3;
    v16i8 zero = { 0 };
    v16i8 pred0, pred1, pred2, pred3, dest0, dest1;
    v16i8 mask = { 0, 2, 4, 6, 16, 18, 20, 22, 0, 0, 0, 0, 0, 0, 0, 0 };

    vec = __msa_fill_h(in_dc[0]);
    vec = __msa_srari_h(vec, 3);
    LD_SB4(dst, stride, pred0, pred1, pred2, pred3);
    ILVR_B4_SH(zero, pred0, zero, pred1, zero, pred2, zero, pred3,
               res0, res1, res2, res3);
    ADD4(res0, vec, res1, vec, res2, vec, res3, vec, res0, res1, res2, res3);
    CLIP_SH4_0_255(res0, res1, res2, res3);
    VSHF_B2_SB(res0, res1, res2, res3, mask, mask, dest0, dest1);
    ST_W2(dest0, 0, 1, dst, stride);
    ST_W2(dest1, 0, 1, dst + 2 * stride, stride);

    in_dc[0] = 0;
}