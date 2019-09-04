#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {float (* get ) () ;} ;
struct TYPE_3__ {float (* get ) () ;} ;
typedef  TYPE_1__ Random ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,...) ; 
 TYPE_2__ rng1 ; 
 float stub1 () ; 
 float stub2 () ; 

int main() {
  Random rng2;
  int count = 0;
  for (int i = 0; i < 100; i++) {
    float x1 = rng1.get();
    float x2 = rng2.get();
    printf("%f, %f\n", x1, x2);
    if (x1 != x2) count += 1;
  }
  printf("*%d*\n", count);
  return 0;
}