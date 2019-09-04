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
 int /*<<< orphan*/  printf (char*,double,double,double,...) ; 

int main() {
  printf("%f %f %f %f %f\n", 0.0, 0.5, 1.0, 1.75, 802.0);
  printf("%f %f %f %f %f\n", 0.01, 1.23, 14.783, 123.4567, 12345678910.0);
  printf("%f %f %f\n", 0.99, 0.8080808, 0.01020304);
  printf("%.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
  return 0;
}