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
typedef  int /*<<< orphan*/  tests ;

/* Variables and functions */
 int IsNaN (double) ; 
 int /*<<< orphan*/  printf (char*,int,double,int) ; 

int main() {
  double tests[] = {1.0, 3.333, 1.0 / 0.0,  0.0 / 0.0, -1.0 / 0.0,
                    -0,  0,     -123123123, 12.0E200};
  for (int i = 0; i < sizeof(tests) / sizeof(double); i++)
    printf("%d - %f - %d\n", i, tests[i], IsNaN(tests[i]));
}