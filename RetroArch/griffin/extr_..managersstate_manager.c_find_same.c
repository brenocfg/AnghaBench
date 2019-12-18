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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */

__attribute__((used)) static size_t find_same(const uint16_t *a, const uint16_t *b)
{
   const uint16_t *a_org = a;
#ifdef NO_UNALIGNED_MEM
   if (((uintptr_t)a & (sizeof(uint32_t) - 1)) && *a != *b)
   {
      a++;
      b++;
   }
   if (*a != *b)
#endif
   {
      /* With this, it's random whether two consecutive identical
       * words are caught.
       *
       * Luckily, compression rate is the same for both cases, and
       * three is always caught.
       *
       * (We prefer to miss two-word blocks, anyways; fewer iterations
       * of the outer loop, as well as in the decompressor.) */
      const uint32_t *a_big = (const uint32_t*)a;
      const uint32_t *b_big = (const uint32_t*)b;

      while (*a_big != *b_big)
      {
         a_big++;
         b_big++;
      }
      a = (const uint16_t*)a_big;
      b = (const uint16_t*)b_big;

      if (a != a_org && a[-1] == b[-1])
      {
         a--;
         b--;
      }
   }
   return a - a_org;
}