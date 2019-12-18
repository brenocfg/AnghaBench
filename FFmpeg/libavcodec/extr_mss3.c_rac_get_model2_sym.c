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
struct TYPE_8__ {int zero_freq; } ;
struct TYPE_7__ {int range; int low; } ;
typedef  TYPE_1__ RangeCoder ;
typedef  TYPE_2__ Model2 ;

/* Variables and functions */
 int MODEL2_SCALE ; 
 scalar_t__ RAC_BOTTOM ; 
 int /*<<< orphan*/  model2_update (TYPE_2__*,int) ; 
 int /*<<< orphan*/  rac_normalise (TYPE_1__*) ; 

__attribute__((used)) static int rac_get_model2_sym(RangeCoder *c, Model2 *m)
{
    int bit, helper;

    helper = m->zero_freq * (c->range >> MODEL2_SCALE);
    bit    = (c->low >= helper);
    if (bit) {
        c->low   -= helper;
        c->range -= helper;
    } else {
        c->range  = helper;
    }

    if (c->range < RAC_BOTTOM)
        rac_normalise(c);

    model2_update(m, bit);

    return bit;
}