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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  OpusRangeCoder ;

/* Variables and functions */
 int FFABS (int) ; 
 void* FFMIN (int,int) ; 
 int const FFSIGN (int) ; 
 int /*<<< orphan*/  opus_rc_enc_update (int /*<<< orphan*/ *,int,int,int,int) ; 

void ff_opus_rc_enc_laplace(OpusRangeCoder *rc, int *value, uint32_t symbol, int decay)
{
    uint32_t low = symbol;
    int i = 1, val = FFABS(*value), pos = *value > 0;
    if (!val) {
        opus_rc_enc_update(rc, 0, symbol, 1 << 15, 1);
        return;
    }
    symbol = ((32768 - 32 - symbol)*(16384 - decay)) >> 15;
    for (; i < val && symbol; i++) {
        low   += (symbol << 1) + 2;
        symbol = (symbol*decay) >> 14;
    }
    if (symbol) {
        low += (++symbol)*pos;
    } else {
        const int distance = FFMIN(val - i, (((32768 - low) - !pos) >> 1) - 1);
        low   += pos + (distance << 1);
        symbol = FFMIN(1, 32768 - low);
        *value = FFSIGN(*value)*(distance + i);
    }
    opus_rc_enc_update(rc, low, low + symbol, 1 << 15, 1);
}