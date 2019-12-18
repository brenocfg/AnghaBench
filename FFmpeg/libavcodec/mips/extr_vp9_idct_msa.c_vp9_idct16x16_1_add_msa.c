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
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int uint8_t ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADD4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLIP_SH8_0_255 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LD_UB4 (int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCKEV_B4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ROUND_POWER_OF_TWO (int,int) ; 
 int /*<<< orphan*/  ST_UB4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  UNPCK_UB_SH (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VP9_DCT_CONST_BITS ; 
 int /*<<< orphan*/  __msa_fill_h (int) ; 
 int cospi_16_64 ; 

__attribute__((used)) static void vp9_idct16x16_1_add_msa(int16_t *input, uint8_t *dst,
                                    int32_t dst_stride)
{
    uint8_t i;
    int16_t out;
    v8i16 vec, res0, res1, res2, res3, res4, res5, res6, res7;
    v16u8 dst0, dst1, dst2, dst3, tmp0, tmp1, tmp2, tmp3;

    out = ROUND_POWER_OF_TWO((input[0] * cospi_16_64), VP9_DCT_CONST_BITS);
    out = ROUND_POWER_OF_TWO((out * cospi_16_64), VP9_DCT_CONST_BITS);
    out = ROUND_POWER_OF_TWO(out, 6);
    input[0] = 0;

    vec = __msa_fill_h(out);

    for (i = 4; i--;) {
        LD_UB4(dst, dst_stride, dst0, dst1, dst2, dst3);
        UNPCK_UB_SH(dst0, res0, res4);
        UNPCK_UB_SH(dst1, res1, res5);
        UNPCK_UB_SH(dst2, res2, res6);
        UNPCK_UB_SH(dst3, res3, res7);
        ADD4(res0, vec, res1, vec, res2, vec, res3, vec, res0, res1, res2,
             res3);
        ADD4(res4, vec, res5, vec, res6, vec, res7, vec, res4, res5, res6,
             res7);
        CLIP_SH8_0_255(res0, res1, res2, res3, res4, res5, res6, res7);
        PCKEV_B4_UB(res4, res0, res5, res1, res6, res2, res7, res3,
                    tmp0, tmp1, tmp2, tmp3);
        ST_UB4(tmp0, tmp1, tmp2, tmp3, dst, dst_stride);
        dst += (4 * dst_stride);
    }
}