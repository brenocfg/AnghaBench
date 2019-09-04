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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADDBLK_ST4x4_UB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ROUND_POWER_OF_TWO (int,int) ; 
 int VP9_DCT_CONST_BITS ; 
 int /*<<< orphan*/  __msa_fill_h (int) ; 
 int cospi_16_64 ; 

__attribute__((used)) static void vp9_idct4x4_1_add_msa(int16_t *input, uint8_t *dst,
                                  int32_t dst_stride)
{
    int16_t out;
    v8i16 vec;

    out = ROUND_POWER_OF_TWO((input[0] * cospi_16_64), VP9_DCT_CONST_BITS);
    out = ROUND_POWER_OF_TWO((out * cospi_16_64), VP9_DCT_CONST_BITS);
    out = ROUND_POWER_OF_TWO(out, 4);
    vec = __msa_fill_h(out);
    input[0] = 0;

    ADDBLK_ST4x4_UB(vec, vec, vec, vec, dst, dst_stride);
}