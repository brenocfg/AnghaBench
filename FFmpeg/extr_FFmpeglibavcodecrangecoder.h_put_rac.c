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
struct TYPE_4__ {int range; int* zero_state; int* one_state; int /*<<< orphan*/  low; } ;
typedef  TYPE_1__ RangeCoder ;

/* Variables and functions */
 int /*<<< orphan*/  av_assert2 (int) ; 
 int /*<<< orphan*/  renorm_encoder (TYPE_1__*) ; 

__attribute__((used)) static inline void put_rac(RangeCoder *c, uint8_t *const state, int bit)
{
    int range1 = (c->range * (*state)) >> 8;

    av_assert2(*state);
    av_assert2(range1 < c->range);
    av_assert2(range1 > 0);
    if (!bit) {
        c->range -= range1;
        *state    = c->zero_state[*state];
    } else {
        c->low  += c->range - range1;
        c->range = range1;
        *state   = c->one_state[*state];
    }

    renorm_encoder(c);
}