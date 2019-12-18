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
struct TYPE_3__ {int mmal_mode; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ XREF_T ;

/* Variables and functions */
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 

int raspicli_map_xref(const char *str, const XREF_T *map, int num_refs)
{
   int i;

   for (i=0; i<num_refs; i++)
   {
      if (!strcasecmp(str, map[i].mode))
      {
         return map[i].mmal_mode;
      }
   }
   return -1;
}