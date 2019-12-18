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
 int /*<<< orphan*/  opus_rc_dec_normalize (TYPE_1__*) ; 

uint32_t ff_opus_rc_dec_log(OpusRangeCoder *rc, uint32_t bits)
{
    uint32_t k, scale;
    scale = rc->range >> bits; // in this case, scale = symbol

    if (rc->value >= scale) {
        rc->value -= scale;
        rc->range -= scale;
        k = 0;
    } else {
        rc->range = scale;
        k = 1;
    }
    opus_rc_dec_normalize(rc);
    return k;
}