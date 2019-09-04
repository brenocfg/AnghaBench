#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {scalar_t__ c; scalar_t__ d; } ;

/* Variables and functions */
 TYPE_1__* iub ; 
 int /*<<< orphan*/  modifier1 (scalar_t__) ; 
 int /*<<< orphan*/  modifier2 (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  returner1 () ; 
 int /*<<< orphan*/  returner2 (int) ; 
 scalar_t__ truthy () ; 

int main(int argc, char **argv)
{
  int64_t x1 = 0x1234def123450789ULL;
  int64_t x2 = 0x1234def123450788ULL;
  int64_t x3 = 0x1234def123450789ULL;
  printf("*%lld\n%d,%d,%d,%d,%d\n%d,%d,%d,%d,%d*\n", x1, x1==x2, x1<x2, x1<=x2, x1>x2, x1>=x2, // note: some rounding in the printing!
                                                        x1==x3, x1<x3, x1<=x3, x1>x3, x1>=x3);
  printf("*%lld*\n", returner1());
  printf("*%lld*\n", returner2(30));

  uint64_t maxx = -1ULL;
  printf("*%llu*\n*%llu*\n", maxx, maxx >> 5);

  // Make sure params are not modified if they shouldn't be
  int64_t t = 123;
  modifier1(t);
  printf("*%lld*\n", t);
  modifier2(t);
  printf("*%lld*\n", t);

  // global structs with i64s
  printf("*%d,%lld*\n*%d,%lld*\n", iub[0].c, iub[0].d, iub[1].c, iub[1].d);

  // Bitshifts
  {
    int64_t a = -1;
    int64_t b = a >> 29;
    int64_t c = a >> 32;
    int64_t d = a >> 34;
    printf("*%lld,%lld,%lld,%lld*\n", a, b, c, d);
    uint64_t ua = -1;
    int64_t ub = ua >> 29;
    int64_t uc = ua >> 32;
    int64_t ud = ua >> 34;
    printf("*%lld,%lld,%lld,%lld*\n", ua, ub, uc, ud);
  }

  // Nonconstant bitshifts
  {
    int64_t a = -1;
    int64_t b = a >> (29 - argc + 1);
    int64_t c = a >> (32 - argc + 1);
    int64_t d = a >> (34 - argc + 1);
    printf("*%lld,%lld,%lld,%lld*\n", a, b, c, d);
    uint64_t ua = -1;
    int64_t ub = ua >> (29 - argc + 1);
    int64_t uc = ua >> (32 - argc + 1);
    int64_t ud = ua >> (34 - argc + 1);
    printf("*%lld,%lld,%lld,%lld*\n", ua, ub, uc, ud);
  }

  // Math mixtures with doubles
  {
    uint64_t a = 5;
    double b = 6.8;
    uint64_t c = a * b;
    if (truthy()) printf("*%d,%d,%d*\n", (int)&a, (int)&b, (int)&c); // printing addresses prevents optimizations
    printf("*prod:%llu*\n", c);
  }

  // Basic (rounded, for now) math. Just check compilation.
  int64_t a = 0x1234def123450789ULL;
  a--; if (truthy()) a--; // confuse optimizer
  int64_t b = 0x1234000000450789ULL;
  b++; if (truthy()) b--; // confuse optimizer
  printf("*%lld,%lld,%lld,%lld*\n",   (a+b)/5000, (a-b)/5000, (a*3)/5000, (a/5)/5000);

  a -= 17; if (truthy()) a += 5; // confuse optimizer
  b -= 17; if (truthy()) b += 121; // confuse optimizer
  printf("*%llx,%llx,%llx,%llx*\n", b - a, b - a/2, b/2 - a, b - 20);

  if (truthy()) a += 5/b; // confuse optimizer
  if (truthy()) b += 121*(3+a/b); // confuse optimizer
  printf("*%llx,%llx,%llx,%llx*\n", a - b, a - b/2, a/2 - b, a - 20);

  return 0;
}