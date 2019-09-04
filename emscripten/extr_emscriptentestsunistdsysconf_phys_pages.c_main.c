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
 int /*<<< orphan*/  _SC_PHYS_PAGES ; 
 int errno ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int sysconf (int /*<<< orphan*/ ) ; 

int main() {
  printf("%ld, ", sysconf(_SC_PHYS_PAGES));
  printf("errno: %d\n", errno);
  return 0;
}