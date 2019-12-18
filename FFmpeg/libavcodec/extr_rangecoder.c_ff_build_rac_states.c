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
typedef  int int64_t ;
struct TYPE_3__ {int* zero_state; int* one_state; } ;
typedef  TYPE_1__ RangeCoder ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

void ff_build_rac_states(RangeCoder *c, int factor, int max_p)
{
    const int64_t one = 1LL << 32;
    int64_t p;
    int last_p8, p8, i;

    memset(c->zero_state, 0, sizeof(c->zero_state));
    memset(c->one_state, 0, sizeof(c->one_state));

    last_p8 = 0;
    p       = one / 2;
    for (i = 0; i < 128; i++) {
        p8 = (256 * p + one / 2) >> 32; // FIXME: try without the one
        if (p8 <= last_p8)
            p8 = last_p8 + 1;
        if (last_p8 && last_p8 < 256 && p8 <= max_p)
            c->one_state[last_p8] = p8;

        p      += ((one - p) * factor + one / 2) >> 32;
        last_p8 = p8;
    }

    for (i = 256 - max_p; i <= max_p; i++) {
        if (c->one_state[i])
            continue;

        p  = (i * one + 128) >> 8;
        p += ((one - p) * factor + one / 2) >> 32;
        p8 = (256 * p + one / 2) >> 32; // FIXME: try without the one
        if (p8 <= i)
            p8 = i + 1;
        if (p8 > max_p)
            p8 = max_p;
        c->one_state[i] = p8;
    }

    for (i = 1; i < 255; i++)
        c->zero_state[i] = 256 - c->one_state[256 - i];
}