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
 unsigned int MAX (unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned vulkan_num_miplevels(unsigned width, unsigned height)
{
   unsigned size = MAX(width, height);
   unsigned levels = 0;
   while (size)
   {
      levels++;
      size >>= 1;
   }
   return levels;
}