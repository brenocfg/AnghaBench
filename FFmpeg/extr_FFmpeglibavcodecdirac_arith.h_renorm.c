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
struct TYPE_3__ {int range; int low; int /*<<< orphan*/  counter; } ;
typedef  TYPE_1__ DiracArith ;

/* Variables and functions */

__attribute__((used)) static inline void renorm(DiracArith *c)
{
#if HAVE_FAST_CLZ
    int shift = 14 - av_log2_16bit(c->range-1) + ((c->range-1)>>15);

    c->low    <<= shift;
    c->range  <<= shift;
    c->counter += shift;
#else
    while (c->range <= 0x4000) {
        c->low   <<= 1;
        c->range <<= 1;
        c->counter++;
    }
#endif
}