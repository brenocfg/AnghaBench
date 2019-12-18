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
struct TYPE_4__ {int high; int low; int value; } ;
typedef  TYPE_1__ ArithCoder ;

/* Variables and functions */
 int /*<<< orphan*/  arith_normalise (TYPE_1__*) ; 

__attribute__((used)) static int arith_get_number(ArithCoder *c, int mod_val)
{
    int range = c->high - c->low + 1;
    int val   = ((c->value - c->low + 1) * mod_val - 1) / range;
    int prob  = range * val;

    c->high   = (prob + range) / mod_val + c->low - 1;
    c->low   += prob / mod_val;

    arith_normalise(c);

    return val;
}