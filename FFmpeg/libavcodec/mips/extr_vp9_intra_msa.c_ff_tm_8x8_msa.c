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
typedef  scalar_t__ v8u16 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int /*<<< orphan*/  v16i8 ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int ptrdiff_t ;

/* Variables and functions */
 int /*<<< orphan*/  HADD_UB4_UH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ILVR_B4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPRED_SUBS_UH2_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LD_SB (int /*<<< orphan*/  const*) ; 
 int LW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  PCKEV_B2_SB (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAT_UH4_UH (scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  ST_D4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __msa_fill_b (int) ; 
 scalar_t__ __msa_fill_h (int /*<<< orphan*/ ) ; 

void ff_tm_8x8_msa(uint8_t *dst, ptrdiff_t dst_stride,
                   const uint8_t *src_left, const uint8_t *src_top_ptr)
{
    uint8_t top_left = src_top_ptr[-1];
    uint32_t loop_cnt, left;
    v16i8 src_top, src_left0, src_left1, src_left2, src_left3, tmp0, tmp1;
    v8u16 src_top_left, vec0, vec1, vec2, vec3;
    v16u8 src0, src1, src2, src3;

    src_top = LD_SB(src_top_ptr);
    src_top_left = (v8u16) __msa_fill_h(top_left);

    src_left += 4;
    for (loop_cnt = 2; loop_cnt--;) {
        left = LW(src_left);
        src_left0 = __msa_fill_b(left >> 24);
        src_left1 = __msa_fill_b(left >> 16);
        src_left2 = __msa_fill_b(left >> 8);
        src_left3 = __msa_fill_b(left);
        src_left -= 4;

        ILVR_B4_UB(src_left0, src_top, src_left1, src_top, src_left2, src_top,
                   src_left3, src_top, src0, src1, src2, src3);
        HADD_UB4_UH(src0, src1, src2, src3, vec0, vec1, vec2, vec3);
        IPRED_SUBS_UH2_UH(src_top_left, src_top_left, vec0, vec1);
        IPRED_SUBS_UH2_UH(src_top_left, src_top_left, vec2, vec3);
        SAT_UH4_UH(vec0, vec1, vec2, vec3, 7);
        PCKEV_B2_SB(vec1, vec0, vec3, vec2, tmp0, tmp1);
        ST_D4(tmp0, tmp1, 0, 1, 0, 1, dst, dst_stride);
        dst += (4 * dst_stride);
    }
}