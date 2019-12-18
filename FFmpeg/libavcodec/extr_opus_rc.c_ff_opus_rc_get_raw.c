#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int cachelen; int cacheval; int* position; scalar_t__ bytes; } ;
struct TYPE_5__ {int total_bits; TYPE_1__ rb; } ;
typedef  TYPE_2__ OpusRangeCoder ;

/* Variables and functions */
 int av_mod_uintp2 (int,int) ; 

uint32_t ff_opus_rc_get_raw(OpusRangeCoder *rc, uint32_t count)
{
    uint32_t value = 0;

    while (rc->rb.bytes && rc->rb.cachelen < count) {
        rc->rb.cacheval |= *--rc->rb.position << rc->rb.cachelen;
        rc->rb.cachelen += 8;
        rc->rb.bytes--;
    }

    value = av_mod_uintp2(rc->rb.cacheval, count);
    rc->rb.cacheval    >>= count;
    rc->rb.cachelen     -= count;
    rc->total_bits      += count;

    return value;
}