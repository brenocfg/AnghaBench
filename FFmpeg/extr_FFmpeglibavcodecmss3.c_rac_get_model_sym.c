#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int num_syms; unsigned int* freqs; } ;
struct TYPE_7__ {unsigned int range; unsigned int low; } ;
typedef  TYPE_1__ RangeCoder ;
typedef  TYPE_2__ Model ;

/* Variables and functions */
 int MODEL_SCALE ; 
 scalar_t__ RAC_BOTTOM ; 
 int /*<<< orphan*/  model_update (TYPE_2__*,int) ; 
 int /*<<< orphan*/  rac_normalise (TYPE_1__*) ; 

__attribute__((used)) static int rac_get_model_sym(RangeCoder *c, Model *m)
{
    int val;
    int end, end2;
    unsigned prob, prob2, helper;

    prob       = 0;
    prob2      = c->range;
    c->range >>= MODEL_SCALE;
    val        = 0;
    end        = m->num_syms >> 1;
    end2       = m->num_syms;
    do {
        helper = m->freqs[end] * c->range;
        if (helper <= c->low) {
            val   = end;
            prob  = helper;
        } else {
            end2  = end;
            prob2 = helper;
        }
        end = (end2 + val) >> 1;
    } while (end != val);
    c->low  -= prob;
    c->range = prob2 - prob;
    if (c->range < RAC_BOTTOM)
        rac_normalise(c);

    model_update(m, val);

    return val;
}