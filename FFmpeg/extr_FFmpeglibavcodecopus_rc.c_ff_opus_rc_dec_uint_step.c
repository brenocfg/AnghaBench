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

uint32_t ff_opus_rc_dec_uint_step(OpusRangeCoder *rc, int k0)
{
    /* Use a probability of 3 up to itheta=8192 and then use 1 after */
    uint32_t k, scale, symbol, total = (k0+1)*3 + k0;
    scale  = rc->range / total;
    symbol = rc->value / scale + 1;
    symbol = total - FFMIN(symbol, total);

    k = (symbol < (k0+1)*3) ? symbol/3 : symbol - (k0+1)*2;

    opus_rc_dec_update(rc, scale, (k <= k0) ? 3*(k+0) : (k-1-k0) + 3*(k0+1),
                       (k <= k0) ? 3*(k+1) : (k-0-k0) + 3*(k0+1), total);
    return k;
}