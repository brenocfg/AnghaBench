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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  ALPHA_SHIFT_16_TO_10 (int) ; 
 int /*<<< orphan*/  ALPHA_SHIFT_16_TO_12 (int) ; 
 int /*<<< orphan*/  ALPHA_SHIFT_8_TO_10 (int) ; 
 int /*<<< orphan*/  ALPHA_SHIFT_8_TO_12 (int) ; 
 int get_bits (int /*<<< orphan*/ *,int const) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 scalar_t__ get_bits_left (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inline unpack_alpha(GetBitContext *gb, uint16_t *dst, int num_coeffs,
                                const int num_bits, const int decode_precision) {
    const int mask = (1 << num_bits) - 1;
    int i, idx, val, alpha_val;

    idx       = 0;
    alpha_val = mask;
    do {
        do {
            if (get_bits1(gb)) {
                val = get_bits(gb, num_bits);
            } else {
                int sign;
                val  = get_bits(gb, num_bits == 16 ? 7 : 4);
                sign = val & 1;
                val  = (val + 2) >> 1;
                if (sign)
                    val = -val;
            }
            alpha_val = (alpha_val + val) & mask;
            if (num_bits == 16) {
                if (decode_precision == 10) {
                    dst[idx++] = ALPHA_SHIFT_16_TO_10(alpha_val);
                } else { /* 12b */
                    dst[idx++] = ALPHA_SHIFT_16_TO_12(alpha_val);
                }
            } else {
                if (decode_precision == 10) {
                    dst[idx++] = ALPHA_SHIFT_8_TO_10(alpha_val);
                } else { /* 12b */
                    dst[idx++] = ALPHA_SHIFT_8_TO_12(alpha_val);
                }
            }
            if (idx >= num_coeffs)
                break;
        } while (get_bits_left(gb)>0 && get_bits1(gb));
        val = get_bits(gb, 4);
        if (!val)
            val = get_bits(gb, 11);
        if (idx + val > num_coeffs)
            val = num_coeffs - idx;
        if (num_bits == 16) {
            for (i = 0; i < val; i++) {
                if (decode_precision == 10) {
                    dst[idx++] = ALPHA_SHIFT_16_TO_10(alpha_val);
                } else { /* 12b */
                    dst[idx++] = ALPHA_SHIFT_16_TO_12(alpha_val);
                }
            }
        } else {
            for (i = 0; i < val; i++) {
                if (decode_precision == 10) {
                    dst[idx++] = ALPHA_SHIFT_8_TO_10(alpha_val);
                } else { /* 12b */
                    dst[idx++] = ALPHA_SHIFT_8_TO_12(alpha_val);
                }
            }
        }
    } while (idx < num_coeffs);
}