#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v8i16 ;
struct TYPE_24__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLIP_SH4_0_255 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILVR_B4_SH (TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_SB8 (int /*<<< orphan*/ *,int,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  PCKEV_B4_SB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__,TYPE_1__,TYPE_1__,TYPE_1__) ; 
 int /*<<< orphan*/  ST8x4_UB (TYPE_1__,TYPE_1__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __msa_fill_h (int) ; 

__attribute__((used)) static void avc_idct8_dc_addblk_msa(uint8_t *dst, int16_t *src,
                                    int32_t dst_stride)
{
    int32_t dc_val;
    v16i8 dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7;
    v8i16 dst0_r, dst1_r, dst2_r, dst3_r, dst4_r, dst5_r, dst6_r, dst7_r;
    v8i16 dc;
    v16i8 zeros = { 0 };

    dc_val = (src[0] + 32) >> 6;
    dc = __msa_fill_h(dc_val);

    src[0] = 0;

    LD_SB8(dst, dst_stride, dst0, dst1, dst2, dst3, dst4, dst5, dst6, dst7);
    ILVR_B4_SH(zeros, dst0, zeros, dst1, zeros, dst2, zeros, dst3,
               dst0_r, dst1_r, dst2_r, dst3_r);
    ILVR_B4_SH(zeros, dst4, zeros, dst5, zeros, dst6, zeros, dst7,
               dst4_r, dst5_r, dst6_r, dst7_r);
    ADD4(dst0_r, dc, dst1_r, dc, dst2_r, dc, dst3_r, dc,
         dst0_r, dst1_r, dst2_r, dst3_r);
    ADD4(dst4_r, dc, dst5_r, dc, dst6_r, dc, dst7_r, dc,
         dst4_r, dst5_r, dst6_r, dst7_r);
    CLIP_SH4_0_255(dst0_r, dst1_r, dst2_r, dst3_r);
    CLIP_SH4_0_255(dst4_r, dst5_r, dst6_r, dst7_r);
    PCKEV_B4_SB(dst1_r, dst0_r, dst3_r, dst2_r, dst5_r, dst4_r, dst7_r, dst6_r,
                dst0, dst1, dst2, dst3);
    ST8x4_UB(dst0, dst1, dst, dst_stride);
    dst += (4 * dst_stride);
    ST8x4_UB(dst2, dst3, dst, dst_stride);
}