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
typedef  TYPE_1__ RotContext ;

/* Variables and functions */
 double FFMAX (int /*<<< orphan*/ ,double) ; 
 size_t VAR_IN_H ; 
 size_t VAR_IN_W ; 
 float cos (double) ; 
 float sin (double) ; 

__attribute__((used)) static double get_rotated_h(void *opaque, double angle)
{
    RotContext *rot = opaque;
    double inw = rot->var_values[VAR_IN_W];
    double inh = rot->var_values[VAR_IN_H];
    float sinx = sin(angle);
    float cosx = cos(angle);

    return FFMAX(0, -inh * cosx) + FFMAX(0, -inw * sinx) +
           FFMAX(0,  inh * cosx) + FFMAX(0,  inw * sinx);
}