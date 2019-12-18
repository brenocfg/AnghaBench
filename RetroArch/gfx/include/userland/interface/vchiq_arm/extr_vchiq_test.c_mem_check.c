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
 scalar_t__ memcmp (void const*,void const*,int) ; 
 int /*<<< orphan*/  printf (char*,unsigned int,int,...) ; 

__attribute__((used)) static int mem_check(const void *expected, const void *actual, int size)
{
   if (memcmp(expected, actual, size) != 0)
   {
      int i;
      for (i = 0; i < size; i++)
      {
         int ce = ((const char *)expected)[i];
         int ca = ((const char *)actual)[i];
         if (ca != ce)
            printf("%08x,%x: %02x <-> %02x\n", i + (unsigned int)actual, i, ce, ca);
      }
      printf("mem_check failed - buffer %x, size %d\n", (unsigned int)actual, size);
      return 1;
   }
   return 0;
}