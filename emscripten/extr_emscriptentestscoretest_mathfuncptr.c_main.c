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
 float erff (float) ; 
 float fabsf (float) ; 
 int /*<<< orphan*/  printf (char*,int,float,float) ; 
 float sqrtf (float) ; 

int main(int argc, char **argv) {
  float (*fn)(float) = argc != 12 ? &sqrtf : &fabsf;
  float (*fn2)(float) = argc != 13 ? &fabsf : &sqrtf;
  float (*fn3)(float) = argc != 14 ? &erff : &fabsf;
  printf("fn2(-5) = %d, fn(10) = %.2f, erf(10) = %.2f\n", (int)fn2(-5), fn(10),
         fn3(10));
  return 0;
}