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
 int /*<<< orphan*/  assert (int) ; 
 int fabs (double) ; 
 double frexp (double,int*) ; 
 double pow (double,int) ; 
 int /*<<< orphan*/  printf (char*,double,double,int) ; 
 int tol ; 

void test_value(double value) {
  int exponent;
  double x = frexp(value, &exponent);
  double expected = x * pow(2.0, exponent);

  printf("%f=%f*2^%d\n", value, x, exponent);

  assert(fabs(expected - value) < tol);
  assert(x == 0 || (fabs(x) >= 5e-1 && fabs(x) < 1));  // x has a magnitude in
                                                       // the interval [1/2, 1)
}