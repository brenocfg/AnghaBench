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
 double acos (double) ; 
 double exp2 (double) ; 
 int isnan (double) ; 
 double log10 (double) ; 
 float log10f (double) ; 
 int /*<<< orphan*/  printf (char*,double,double,float,int) ; 

void test_exp_log(double x) {
    double a = exp2(x);
    double b = log10(x);
    float c = log10f(x);
    double d = acos(x);
    printf("%f : %f : %f : %d\n", a, b, c, isnan(d));
}