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
struct TYPE_4__ {double clock_period; double feedback2_factor; double feedback3_factor; } ;
typedef  TYPE_1__ TimeFilter ;

/* Variables and functions */
 int M_PI ; 
 double M_SQRT2 ; 
 TYPE_1__* av_mallocz (int) ; 
 double qexpneg (double) ; 

TimeFilter *ff_timefilter_new(double time_base,
                              double period,
                              double bandwidth)
{
    TimeFilter *self       = av_mallocz(sizeof(TimeFilter));
    double o               = 2 * M_PI * bandwidth * period * time_base;

    if (!self)
        return NULL;

    self->clock_period     = time_base;
    self->feedback2_factor = qexpneg(M_SQRT2 * o);
    self->feedback3_factor = qexpneg(o * o) / period;
    return self;
}