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
 double __builtin_copysign (double,double) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int __attribute__((noinline))
copysign_bug (double x)
{
  if (x != 0.0 && (x * 0.5 == x)) {
    printf("1\n");
    return 1;
  }
  printf("f: %f\n", x);
  if (__builtin_copysign(1.0, x) < 0.0) {
    printf("2\n");
    return 2;
  } else {
    printf("3\n");
    return 3;
  }
}