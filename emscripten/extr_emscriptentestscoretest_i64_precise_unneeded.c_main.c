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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int) ; 

int main(int argc, char **argv) {
  uint64_t x = 2125299906845564, y = 1225891506842664;
  if (argc == 12) {
    x = x >> 1;
    y = y >> 1;
  }
  x = x & 12ULL;
  y = y | 12ULL;
  x = x ^ y;
  x <<= 2;
  y >>= 3;
  printf("*%llu, %llu*\n", x, y);
}