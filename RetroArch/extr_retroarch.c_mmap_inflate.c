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

__attribute__((used)) static size_t mmap_inflate(size_t addr, size_t mask)
{
    while (mask)
   {
      size_t tmp = (mask - 1) & ~mask;

      /* to put in an 1 bit instead, OR in tmp+1 */
      addr       = ((addr & ~tmp) << 1) | (addr & tmp);
      mask       = mask & (mask - 1);
   }

   return addr;
}