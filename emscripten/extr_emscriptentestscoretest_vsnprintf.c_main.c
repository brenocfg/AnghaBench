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
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  printy (char*,int,int) ; 

int main(int argc, char **argv) {
  int64_t x = argc - 1;
  int64_t y = argc - 1 + 0x400000;
  if (x % 3 == 2) y *= 2;

  printy("0x%llx_0x%llx", x, y);
  printy("0x%llx_0x%llx", x, x);
  printy("0x%llx_0x%llx", y, x);
  printy("0x%llx_0x%llx", y, y);

  {
    uint64_t A = 0x800000;
    uint64_t B = 0x800000000000ULL;
    printy("0x%llx_0x%llx", A, B);
  }
  {
    uint64_t A = 0x800;
    uint64_t B = 0x12340000000000ULL;
    printy("0x%llx_0x%llx", A, B);
  }
  {
    uint64_t A = 0x000009182746756;
    uint64_t B = 0x192837465631ACBDULL;
    printy("0x%llx_0x%llx", A, B);
  }

  return 0;
}