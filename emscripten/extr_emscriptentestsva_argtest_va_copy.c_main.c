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
 int /*<<< orphan*/  vary (int,int,...) ; 

int main() {
  int x = 1;
  int y = 2;
  int z = 3;

  vary(3, x, y, z);
  vary(2, x, z);
  vary(1, x);
  return 0;
}