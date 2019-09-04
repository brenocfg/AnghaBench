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
 int /*<<< orphan*/  printResult (int*,int*,int) ; 

int main() {
  int a[] = {-2, -1, 0, 6, 7, 9};
  int b[] = {0, 1};

  /* Find all keys that exist. */
  for (int i = 0; i < 6; i++) {
    int val = a[i];

    printResult(&val, a, 6);
  }

  /* Keys that are covered by the range of the array but aren't in
   * the array cannot be found.
   */
  int v1 = 3;
  int v2 = 8;
  printResult(&v1, a, 6);
  printResult(&v2, a, 6);

  /* Keys outside the range of the array cannot be found. */
  int v3 = -1;
  int v4 = 2;

  printResult(&v3, b, 2);
  printResult(&v4, b, 2);

  return 0;
}