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
struct TYPE_3__ {int const mmal_mode; char const* mode; } ;
typedef  TYPE_1__ XREF_T ;

/* Variables and functions */

const char *raspicli_unmap_xref(const int en, XREF_T *map, int num_refs)
{
   int i;

   for (i=0; i<num_refs; i++)
   {
      if (en == map[i].mmal_mode)
      {
         return map[i].mode;
      }
   }
   return NULL;
}