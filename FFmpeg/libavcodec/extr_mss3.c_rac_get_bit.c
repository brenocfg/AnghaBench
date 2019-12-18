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
struct TYPE_4__ {int range; int low; } ;
typedef  TYPE_1__ RangeCoder ;

/* Variables and functions */
 scalar_t__ RAC_BOTTOM ; 
 int /*<<< orphan*/  rac_normalise (TYPE_1__*) ; 

__attribute__((used)) static int rac_get_bit(RangeCoder *c)
{
    int bit;

    c->range >>= 1;

    bit = (c->range <= c->low);
    if (bit)
        c->low -= c->range;

    if (c->range < RAC_BOTTOM)
        rac_normalise(c);

    return bit;
}