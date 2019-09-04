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
typedef  unsigned long long uint64_t ;
typedef  long long int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,long long,long long,long long,long long,long long,long long,long long,long long,long long) ; 

int main() {
  uint64_t x = 0, y = 0;
  for (int i = 0; i < 64; i++) {
    x += 1ULL << i;
    y += x;
    x /= 3;
    y *= 5;
    printf("unsigned %d: %llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu,%llu\n", i, x, y, x+y, x-y, x*y, y ? x/y : 0, x ? y/x : 0, y ? x%y : 0, x ? y%x : 0);
  }
  int64_t x2 = 0, y2 = 0;
  for (int i = 0; i < 64; i++) {
    x2 += 1LL << i;
    y2 += x2;
    x2 /= 3 * (i % 7 ? -1 : 1);
    y2 *= 5 * (i % 2 ? -1 : 1);
    printf("signed %d: %lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld\n", i, x2, y2, x2+y2, x2-y2, x2*y2, y2 ? x2/y2 : 0, x2 ? y2/x2 : 0, y2 ? x2%y2 : 0, x2 ? y2%x2 : 0);
  }
  return 0;
}