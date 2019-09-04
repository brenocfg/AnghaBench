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
 int /*<<< orphan*/  printf (char*,...) ; 

int main()
{
  long long a = 0x2b00505c10;
  long long b = a >> 29;
  long long c = a >> 32;
  long long d = a >> 34;
  printf("*%lld,%lld,%lld,%lld*\n", a, b, c, d);
  unsigned long long ua = 0x2b00505c10;
  unsigned long long ub = ua >> 29;
  unsigned long long uc = ua >> 32;
  unsigned long long ud = ua >> 34;
  printf("*%lld,%lld,%lld,%lld*\n", ua, ub, uc, ud);

  long long x = 0x0000def123450789ULL; // any bigger than this, and we
  long long y = 0x00020ef123456089ULL; // start to run into the double precision limit!
  printf("*%lld,%lld,%lld,%lld,%lld*\n", x, y, x | y, x & y, x ^ y);

  printf("*");
  long long z = 13;
  int n = 0;
  while (z > 1) {
    printf("%.2f,", (float)z); // these must be integers!
    z = z >> 1;
    n++;
  }
  printf("*%d*\n", n);
  return 0;
}