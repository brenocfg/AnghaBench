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
 int getloadavg (double*,int) ; 
 int /*<<< orphan*/  printf (char*,double) ; 

int main() {
  double load[5] = {42.13, 42.13, 42.13, 42.13, 42.13};
  printf("ret: %d\n", getloadavg(load, 5));
  printf("load[0]: %.3lf\n", load[0]);
  printf("load[1]: %.3lf\n", load[1]);
  printf("load[2]: %.3lf\n", load[2]);
  printf("load[3]: %.3lf\n", load[3]);
  printf("load[4]: %.3lf\n", load[4]);
  return 0;
}