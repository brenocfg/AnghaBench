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
typedef  int uint32_t ;
struct TYPE_3__ {int range; int code; } ;
typedef  TYPE_1__ RangeCoder ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 

__attribute__((used)) static int get_freq(RangeCoder *rc, uint32_t total_freq, uint32_t *freq)
{
    if (total_freq == 0)
        return AVERROR_INVALIDDATA;

    rc->range = rc->range / total_freq;

    if (rc->range == 0)
        return AVERROR_INVALIDDATA;

    *freq = rc->code / rc->range;

    return 0;
}