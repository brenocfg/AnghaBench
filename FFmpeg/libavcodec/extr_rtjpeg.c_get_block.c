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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int8_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  PUT_COEFF (int) ; 
 int get_bits (int /*<<< orphan*/ *,int) ; 
 int get_bits_left (int /*<<< orphan*/ *) ; 
 int get_sbits (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int get_block(GetBitContext *gb, int16_t *block, const uint8_t *scan,
                            const uint32_t *quant) {
    int coeff, i, n;
    int8_t ac;
    uint8_t dc = get_bits(gb, 8);

    // block not coded
    if (dc == 255)
       return 0;

    // number of non-zero coefficients
    coeff = get_bits(gb, 6);
    if (get_bits_left(gb) < (coeff << 1))
        return AVERROR_INVALIDDATA;

    // normally we would only need to clear the (63 - coeff) last values,
    // but since we do not know where they are we just clear the whole block
    memset(block, 0, 64 * sizeof(int16_t));

    // 2 bits per coefficient
    while (coeff) {
        ac = get_sbits(gb, 2);
        if (ac == -2)
            break; // continue with more bits
        PUT_COEFF(ac);
    }

    // 4 bits per coefficient
    ALIGN(4);
    if (get_bits_left(gb) < (coeff << 2))
        return AVERROR_INVALIDDATA;
    while (coeff) {
        ac = get_sbits(gb, 4);
        if (ac == -8)
            break; // continue with more bits
        PUT_COEFF(ac);
    }

    // 8 bits per coefficient
    ALIGN(8);
    if (get_bits_left(gb) < (coeff << 3))
        return AVERROR_INVALIDDATA;
    while (coeff) {
        ac = get_sbits(gb, 8);
        PUT_COEFF(ac);
    }

    PUT_COEFF(dc);
    return 1;
}