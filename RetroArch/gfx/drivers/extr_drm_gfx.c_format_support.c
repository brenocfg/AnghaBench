#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* drmModePlanePtr ;
struct TYPE_3__ {unsigned int count_formats; scalar_t__* formats; } ;

/* Variables and functions */

__attribute__((used)) static bool format_support(const drmModePlanePtr ovr, uint32_t fmt)
{
   unsigned int i;

   for (i = 0; i < ovr->count_formats; ++i)
   {
      if (ovr->formats[i] == fmt)
         return true;
   }

   return false;
}