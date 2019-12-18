#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 float pow (double,int) ; 
 double sqrt (double) ; 

__attribute__((used)) static void set_params(float sigma, int steps, float *postscale, float *boundaryscale, float *nu)
{
    double dnu, lambda;

    lambda = (sigma * sigma) / (2.0 * steps);
    dnu = (1.0 + 2.0 * lambda - sqrt(1.0 + 4.0 * lambda)) / (2.0 * lambda);
    *postscale = pow(dnu / lambda, steps);
    *boundaryscale = 1.0 / (1.0 - dnu);
    *nu = (float)dnu;
}