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
typedef  int v8i16 ;
typedef  int /*<<< orphan*/  v16u8 ;
typedef  int uint8_t ;
typedef  int int8_t ;
typedef  int int32_t ;
typedef  int int16_t ;

/* Variables and functions */
 int LD_SH (int*) ; 
 int /*<<< orphan*/  ST_SH (int,int*) ; 
 scalar_t__ __msa_bmnz_v (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int __msa_ceqi_h (int,int /*<<< orphan*/ ) ; 
 int __msa_clti_s_h (int,int /*<<< orphan*/ ) ; 
 int __msa_fill_h (int) ; 

__attribute__((used)) static void h263_dct_unquantize_msa(int16_t *block, int16_t qmul,
                                    int16_t qadd, int8_t n_coeffs,
                                    uint8_t loop_start)
{
    int16_t *block_dup = block;
    int32_t level, cnt;
    v8i16 block_vec, qmul_vec, qadd_vec, sub;
    v8i16 add, mask, mul, zero_mask;

    qmul_vec = __msa_fill_h(qmul);
    qadd_vec = __msa_fill_h(qadd);
    for (cnt = 0; cnt < (n_coeffs >> 3); cnt++) {
        block_vec = LD_SH(block_dup + loop_start);
        mask = __msa_clti_s_h(block_vec, 0);
        zero_mask = __msa_ceqi_h(block_vec, 0);
        mul = block_vec * qmul_vec;
        sub = mul - qadd_vec;
        add = mul + qadd_vec;
        add = (v8i16) __msa_bmnz_v((v16u8) add, (v16u8) sub, (v16u8) mask);
        block_vec = (v8i16) __msa_bmnz_v((v16u8) add, (v16u8) block_vec,
                                         (v16u8) zero_mask);
        ST_SH(block_vec, block_dup + loop_start);
        block_dup += 8;
    }

    cnt = ((n_coeffs >> 3) * 8) + loop_start;

    for (; cnt <= n_coeffs; cnt++) {
        level = block[cnt];
        if (level) {
            if (level < 0) {
                level = level * qmul - qadd;
            } else {
                level = level * qmul + qadd;
            }
            block[cnt] = level;
        }
    }
}