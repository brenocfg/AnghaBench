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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  GetBitContext ;

/* Variables and functions */
 unsigned int FIRST_QTR ; 
 unsigned int FREQ_BITS ; 
 unsigned int HALF ; 
 unsigned int LUT_BITS ; 
 unsigned int LUT_SIZE ; 
 unsigned int THIRD_QTR ; 
 int* bgmc_lut_getp (int*,int*,int) ; 
 unsigned int** cf_table ; 
 int get_bits1 (int /*<<< orphan*/ *) ; 

void ff_bgmc_decode(GetBitContext *gb, unsigned int num, int32_t *dst,
                    int delta, unsigned int sx,
                    unsigned int *h, unsigned int *l, unsigned int *v,
                    uint8_t *cf_lut, int *cf_lut_status)
{
    unsigned int i;
    uint8_t *lut = bgmc_lut_getp(cf_lut, cf_lut_status, delta);

    // read current state
    unsigned int high  = *h;
    unsigned int low   = *l;
    unsigned int value = *v;

    lut += sx * LUT_SIZE;

    // decode num samples
    for (i = 0; i < num; i++) {
        unsigned int range  = high - low + 1;
        unsigned int target = (((value - low + 1) << FREQ_BITS) - 1) / range;
        unsigned int symbol = lut[target >> (FREQ_BITS - LUT_BITS)] << delta;

        while (cf_table[sx][symbol] > target)
            symbol += 1 << delta;

        symbol = (symbol >> delta) - 1;

        high = low + ((range * cf_table[sx][(symbol)     << delta] - (1 << FREQ_BITS)) >> FREQ_BITS);
        low  = low + ((range * cf_table[sx][(symbol + 1) << delta])                    >> FREQ_BITS);

        while (1) {
            if (high >= HALF) {
                if (low >= HALF) {
                    value -= HALF;
                    low   -= HALF;
                    high  -= HALF;
                } else if (low >= FIRST_QTR && high < THIRD_QTR) {
                    value -= FIRST_QTR;
                    low   -= FIRST_QTR;
                    high  -= FIRST_QTR;
                } else
                    break;
            }

            low  *= 2;
            high  = 2 * high + 1;
            value = 2 * value + get_bits1(gb);
        }

        *dst++ = symbol;
    }

    // save current state
    *h = high;
    *l = low;
    *v = value;
}