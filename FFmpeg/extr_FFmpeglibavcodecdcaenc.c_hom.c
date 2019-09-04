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
 double exp (double) ; 
 double pow (double,double) ; 

__attribute__((used)) static double hom(double f)
{
    double f1 = f / 1000;

    return -3.64 * pow(f1, -0.8)
           + 6.8 * exp(-0.6 * (f1 - 3.4) * (f1 - 3.4))
           - 6.0 * exp(-0.15 * (f1 - 8.7) * (f1 - 8.7))
           - 0.0006 * (f1 * f1) * (f1 * f1);
}