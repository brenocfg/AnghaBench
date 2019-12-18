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
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 int get_bits1 (int /*<<< orphan*/ *) ; 
 unsigned int get_bits_long (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int lag_decode_prob(GetBitContext *gb, uint32_t *value)
{
    static const uint8_t series[] = { 1, 2, 3, 5, 8, 13, 21 };
    int i;
    int bit     = 0;
    int bits    = 0;
    int prevbit = 0;
    unsigned val;

    for (i = 0; i < 7; i++) {
        if (prevbit && bit)
            break;
        prevbit = bit;
        bit = get_bits1(gb);
        if (bit && !prevbit)
            bits += series[i];
    }
    bits--;
    if (bits < 0 || bits > 31) {
        *value = 0;
        return -1;
    } else if (bits == 0) {
        *value = 0;
        return 0;
    }

    val  = get_bits_long(gb, bits);
    val |= 1U << bits;

    *value = val - 1;

    return 0;
}