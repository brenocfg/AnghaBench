#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {double* var_values; } ;
typedef  TYPE_1__ LutContext ;

/* Variables and functions */
 size_t VAR_CLIPVAL ; 
 size_t VAR_MAXVAL ; 
 size_t VAR_MINVAL ; 
 double pow (double,double) ; 

__attribute__((used)) static double compute_gammaval(void *opaque, double gamma)
{
    LutContext *s = opaque;
    double val    = s->var_values[VAR_CLIPVAL];
    double minval = s->var_values[VAR_MINVAL];
    double maxval = s->var_values[VAR_MAXVAL];

    return pow((val-minval)/(maxval-minval), gamma) * (maxval-minval)+minval;
}