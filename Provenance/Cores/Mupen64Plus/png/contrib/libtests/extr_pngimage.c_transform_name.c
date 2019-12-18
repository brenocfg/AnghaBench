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
struct TYPE_2__ {char const* name; int transform; } ;

/* Variables and functions */
 unsigned int TTABLE_SIZE ; 
 TYPE_1__* transform_info ; 

__attribute__((used)) static const char *
transform_name(int t)
   /* The name, if 't' has multiple bits set the name of the lowest set bit is
    * returned.
    */
{
   unsigned int i;

   t &= -t; /* first set bit */

   for (i=0; i<TTABLE_SIZE; ++i) if (transform_info[i].name != NULL)
   {
      if ((transform_info[i].transform & t) != 0)
         return transform_info[i].name;
   }

   return "invalid transform";
}