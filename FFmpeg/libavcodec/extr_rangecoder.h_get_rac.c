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
typedef  int uint8_t ;
struct TYPE_4__ {int range; int low; int* zero_state; int* one_state; } ;
typedef  TYPE_1__ RangeCoder ;

/* Variables and functions */
 int /*<<< orphan*/  refill (TYPE_1__*) ; 

__attribute__((used)) static inline int get_rac(RangeCoder *c, uint8_t *const state)
{
    int range1 = (c->range * (*state)) >> 8;

    c->range -= range1;
    if (c->low < c->range) {
        *state = c->zero_state[*state];
        refill(c);
        return 0;
    } else {
        c->low  -= c->range;
        *state   = c->one_state[*state];
        c->range = range1;
        refill(c);
        return 1;
    }
}