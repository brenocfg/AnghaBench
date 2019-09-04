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
 double erf (double) ; 
 double erfc (double) ; 
 int /*<<< orphan*/  printf (char*,double,double,double,double,double,double) ; 

int main() {
  printf("%1.6f, %1.6f, %1.6f, %1.6f, %1.6f, %1.6f\n", erf(1.0), erf(3.0),
         erf(-1.0), erfc(1.0), erfc(3.0), erfc(-1.5));
  return 0;
}