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
 float MAX (float,float) ; 
 float fabs (float const) ; 
 int /*<<< orphan*/  printf (char*,float) ; 

__attribute__((used)) static int
check_output (const float * data_in, unsigned len, float allowable)
{
  float max_abs = 0.0 ;
  unsigned k ;

  for (k = 0 ; k < len ; k++) {
    float temp = fabs (data_in [k]);
    max_abs = MAX (max_abs, temp);
  }

  if (max_abs < 0.95-allowable) {
    printf ("Error : max_abs (%f) too small.\n", max_abs);
    return 1 ;
  } else if (max_abs > .95+allowable) {
    printf ("Error : max_abs (%f) too big.\n", max_abs);
    return 1 ;
  }

  return 0 ;
}