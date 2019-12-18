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
typedef  int uint32_t ;
struct TYPE_5__ {int range; int value; } ;
typedef  TYPE_1__ OpusRangeCoder ;

/* Variables and functions */
 int FFMIN (int,int) ; 
 int ff_opus_rc_get_raw (TYPE_1__*,int) ; 
 int opus_ilog (int) ; 
 int /*<<< orphan*/  opus_rc_dec_update (TYPE_1__*,int,int,int,int) ; 

uint32_t ff_opus_rc_dec_uint(OpusRangeCoder *rc, uint32_t size)
{
    uint32_t bits, k, scale, total;

    bits  = opus_ilog(size - 1);
    total = (bits > 8) ? ((size - 1) >> (bits - 8)) + 1 : size;

    scale  = rc->range / total;
    k      = rc->value / scale + 1;
    k      = total - FFMIN(k, total);
    opus_rc_dec_update(rc, scale, k, k + 1, total);

    if (bits > 8) {
        k = k << (bits - 8) | ff_opus_rc_get_raw(rc, bits - 8);
        return FFMIN(k, size - 1);
    } else
        return k;
}