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
 int /*<<< orphan*/  printf (char*,int) ; 
 int test (int,int) ; 

int main(void) {
  printf(",%d,", test(0, 0));
  printf(",%d,", test(1, 1));
  printf(",%d,", test(65535, 1));
  printf(",%d,", test(1, 65535));
  printf(",%d,", test(32768, 32767));
  printf(",%d,", test(32768, 32768));
  return 0;
}