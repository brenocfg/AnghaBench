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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 size_t UINT16_MAX ; 
 size_t UINT32_MAX ; 
 size_t find_change (scalar_t__ const*,scalar_t__ const*) ; 
 size_t find_same (scalar_t__ const*,scalar_t__ const*) ; 

__attribute__((used)) static size_t state_manager_raw_compress(const void *src,
      const void *dst, size_t len, void *patch)
{
   const uint16_t  *old16 = (const uint16_t*)src;
   const uint16_t  *new16 = (const uint16_t*)dst;
   uint16_t *compressed16 = (uint16_t*)patch;
   size_t          num16s = (len + sizeof(uint16_t) - 1)
      / sizeof(uint16_t);

   while (num16s)
   {
      size_t i, changed;
      size_t skip = find_change(old16, new16);

      if (skip >= num16s)
         break;

      old16  += skip;
      new16  += skip;
      num16s -= skip;

      if (skip > UINT16_MAX)
      {
         if (skip > UINT32_MAX)
         {
            /* This will make it scan the entire thing again,
             * but it only hits on 8GB unchanged data anyways,
             * and if you're doing that, you've got bigger problems. */
            skip = UINT32_MAX;
         }
         *compressed16++ = 0;
         *compressed16++ = skip;
         *compressed16++ = skip >> 16;
         continue;
      }

      changed = find_same(old16, new16);
      if (changed > UINT16_MAX)
         changed = UINT16_MAX;

      *compressed16++ = changed;
      *compressed16++ = skip;

      for (i = 0; i < changed; i++)
         compressed16[i] = old16[i];

      old16 += changed;
      new16 += changed;
      num16s -= changed;
      compressed16 += changed;
   }

   compressed16[0] = 0;
   compressed16[1] = 0;
   compressed16[2] = 0;

   return (uint8_t*)(compressed16+3) - (uint8_t*)patch;
}