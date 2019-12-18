#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int range; int value; } ;
typedef  TYPE_1__ OpusRangeCoder ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int /*<<< orphan*/  opus_rc_dec_update (TYPE_1__*,int,int,int,int) ; 

int ff_opus_rc_dec_laplace(OpusRangeCoder *rc, uint32_t symbol, int decay)
{
    /* extends the range coder to model a Laplace distribution */
    int value = 0;
    uint32_t scale, low = 0, center;

    scale  = rc->range >> 15;
    center = rc->value / scale + 1;
    center = (1 << 15) - FFMIN(center, 1 << 15);

    if (center >= symbol) {
        value++;
        low = symbol;
        symbol = 1 + ((32768 - 32 - symbol) * (16384-decay) >> 15);

        while (symbol > 1 && center >= low + 2 * symbol) {
            value++;
            symbol *= 2;
            low    += symbol;
            symbol  = (((symbol - 2) * decay) >> 15) + 1;
        }

        if (symbol <= 1) {
            int distance = (center - low) >> 1;
            value += distance;
            low   += 2 * distance;
        }

        if (center < low + symbol)
            value *= -1;
        else
            low += symbol;
    }

    opus_rc_dec_update(rc, scale, low, FFMIN(low + symbol, 32768), 32768);

    return value;
}