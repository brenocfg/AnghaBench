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
struct TYPE_3__ {scalar_t__* bits; } ;
typedef  TYPE_1__ format_list ;

/* Variables and functions */
 int FORMAT_SET_COUNT ; 

__attribute__((used)) static int format_is_initial(format_list *pf)
{
   int i;
   for (i=0; i<FORMAT_SET_COUNT; ++i)
      if (pf->bits[i] != 0)
         return 0;

   return 1;
}