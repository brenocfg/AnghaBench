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
 double* erb ; 
 double* fc ; 
 int log10 (double) ; 

__attribute__((used)) static double gammafilter(int i, double f)
{
    double h = (f - fc[i]) / erb[i];

    h = 1 + h * h;
    h = 1 / (h * h);
    return 20 * log10(h);
}