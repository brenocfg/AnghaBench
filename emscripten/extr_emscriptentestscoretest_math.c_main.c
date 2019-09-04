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
struct TYPE_3__ {int quot; int rem; } ;
typedef  TYPE_1__ div_t ;

/* Variables and functions */
 double INFINITY ; 
 double M_PI ; 
 double NAN ; 
 float cosf (double) ; 
 TYPE_1__ div (int,int) ; 
 scalar_t__ isfinite (double) ; 
 scalar_t__ isinf (double) ; 
 double modf (double,double*) ; 
 float modff (double,float*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sincos (double,double*,double*) ; 
 int /*<<< orphan*/  sincosf (double,float*,float*) ; 
 float sinf (double) ; 

int main(int argc, char **argv) {
  printf("*%.2f,%.2f,%d", M_PI, -M_PI, (1 / 0.0) > 1e300);  // could end up as
                                                            // infinity, or just
                                                            // a very very big
                                                            // number
  printf(",%d", isfinite(NAN) != 0);
  printf(",%d", isfinite(INFINITY) != 0);
  printf(",%d", isfinite(-INFINITY) != 0);
  printf(",%d", isfinite(12.3) != 0);
  printf(",%d", isinf(NAN) != 0);
  printf(",%d", isinf(INFINITY) != 0);
  printf(",%d", isinf(-INFINITY) != 0);
  printf(",%d", isinf(12.3) != 0);

  div_t div_result = div(23, 10);
  printf(",%d", div_result.quot);
  printf(",%d", div_result.rem);

  div_result = div(-5, 3); // see div manpage :)
  printf(",%d", div_result.quot); // -1
  printf(",%d", div_result.rem); // -2

  div_result = div(5, -3);
  printf(",%d", div_result.quot);
  printf(",%d", div_result.rem);

  div_result = div(-5, -3);
  printf(",%d", div_result.quot);
  printf(",%d", div_result.rem);



  {
    double x,y;
    x = modf(3.2, &y);
    printf(",%1.1lf", x);
    printf(",%1.1lf", y);
    x = modf(-3.2, &y);
    printf(",%1.1lf", x);
    printf(",%1.1lf", y);
  }

  {
    float x,y;
    x = modff(3.2, &y);
    printf(",%1.1f", x);
    printf(",%1.1f", y);
    x = modff(-3.2, &y);
    printf(",%1.1f", x);
    printf(",%1.1f", y);
  }

  double sine = -1.0, cosine = -1.0;
  sincos(0.0, &sine, &cosine);
  printf(",%1.1lf", sine);
  printf(",%1.1lf", cosine);
  float fsine = -1.0f, fcosine = -1.0f;
  sincosf(0.0, &fsine, &fcosine);
  printf(",%1.1f", fsine);
  printf(",%1.1f", fcosine);
  fsine = sinf(1.1 + argc - 1);
  fcosine = cosf(1.1 + argc - 1);
  printf(",%1.1f", fsine);
  printf(",%1.1f", fcosine);
  printf("*\n");
  return 0;
}