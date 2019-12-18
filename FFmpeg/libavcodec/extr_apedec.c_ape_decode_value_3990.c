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
struct TYPE_4__ {int ksum; } ;
typedef  TYPE_1__ APERice ;
typedef  int /*<<< orphan*/  APEContext ;

/* Variables and functions */
 int MODEL_ELEMENTS ; 
 int /*<<< orphan*/  counts_3980 ; 
 int /*<<< orphan*/  counts_diff_3980 ; 
 unsigned int range_decode_bits (int /*<<< orphan*/ *,int) ; 
 int range_decode_culfreq (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  range_decode_update (int /*<<< orphan*/ *,int,int) ; 
 unsigned int range_get_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_rice (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static inline int ape_decode_value_3990(APEContext *ctx, APERice *rice)
{
    unsigned int x, overflow;
    int base, pivot;

    pivot = rice->ksum >> 5;
    if (pivot == 0)
        pivot = 1;

    overflow = range_get_symbol(ctx, counts_3980, counts_diff_3980);

    if (overflow == (MODEL_ELEMENTS - 1)) {
        overflow  = (unsigned)range_decode_bits(ctx, 16) << 16;
        overflow |= range_decode_bits(ctx, 16);
    }

    if (pivot < 0x10000) {
        base = range_decode_culfreq(ctx, pivot);
        range_decode_update(ctx, 1, base);
    } else {
        int base_hi = pivot, base_lo;
        int bbits = 0;

        while (base_hi & ~0xFFFF) {
            base_hi >>= 1;
            bbits++;
        }
        base_hi = range_decode_culfreq(ctx, base_hi + 1);
        range_decode_update(ctx, 1, base_hi);
        base_lo = range_decode_culfreq(ctx, 1 << bbits);
        range_decode_update(ctx, 1, base_lo);

        base = (base_hi << bbits) + base_lo;
    }

    x = base + overflow * pivot;

    update_rice(rice, x);

    /* Convert to signed */
    return ((x >> 1) ^ ((x & 1) - 1)) + 1;
}