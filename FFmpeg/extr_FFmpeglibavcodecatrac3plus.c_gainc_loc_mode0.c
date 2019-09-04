#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* loc_code; } ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_1__ AtracGainInfo ;
typedef  int /*<<< orphan*/  Atrac3pChanUnitCtx ;

/* Variables and functions */
 int av_log2 (int) ; 
 void* get_bits (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void gainc_loc_mode0(GetBitContext *gb, Atrac3pChanUnitCtx *ctx,
                                   AtracGainInfo *dst, int pos)
{
    int delta_bits;

    if (!pos || dst->loc_code[pos - 1] < 15)
        dst->loc_code[pos] = get_bits(gb, 5);
    else if (dst->loc_code[pos - 1] >= 30)
        dst->loc_code[pos] = 31;
    else {
        delta_bits         = av_log2(30 - dst->loc_code[pos - 1]) + 1;
        dst->loc_code[pos] = dst->loc_code[pos - 1] +
                             get_bits(gb, delta_bits) + 1;
    }
}