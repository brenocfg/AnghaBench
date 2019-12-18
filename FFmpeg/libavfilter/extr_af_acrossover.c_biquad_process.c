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
struct TYPE_3__ {double a0; double i1; double a1; double i2; double a2; double o1; double b1; double o2; double b2; } ;
typedef  TYPE_1__ BiquadContext ;

/* Variables and functions */

__attribute__((used)) static double biquad_process(BiquadContext *b, double in)
{
    double out = in * b->a0 + b->i1 * b->a1 + b->i2 * b->a2 - b->o1 * b->b1 - b->o2 * b->b2;

    b->i2 = b->i1;
    b->o2 = b->o1;
    b->i1 = in;
    b->o1 = out;

    return out;
}