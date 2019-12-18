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
struct TYPE_3__ {double sum; double window_size; scalar_t__* window_current; } ;
typedef  TYPE_1__ SilenceRemoveContext ;

/* Variables and functions */
 scalar_t__ fabs (double) ; 

__attribute__((used)) static double compute_peak(SilenceRemoveContext *s, double sample)
{
    double new_sum;

    new_sum  = s->sum;
    new_sum -= *s->window_current;
    new_sum += fabs(sample);

    return new_sum / s->window_size;
}