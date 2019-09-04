#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_5__ {int error; } ;
typedef  TYPE_1__ APEContext ;

/* Variables and functions */
 int range_decode_culshift (TYPE_1__*,int) ; 
 int /*<<< orphan*/  range_decode_update (TYPE_1__*,int const,int const) ; 

__attribute__((used)) static inline int range_get_symbol(APEContext *ctx,
                                   const uint16_t counts[],
                                   const uint16_t counts_diff[])
{
    int symbol, cf;

    cf = range_decode_culshift(ctx, 16);

    if(cf > 65492){
        symbol= cf - 65535 + 63;
        range_decode_update(ctx, 1, cf);
        if(cf > 65535)
            ctx->error=1;
        return symbol;
    }
    /* figure out the symbol inefficiently; a binary search would be much better */
    for (symbol = 0; counts[symbol + 1] <= cf; symbol++);

    range_decode_update(ctx, counts_diff[symbol], counts[symbol]);

    return symbol;
}