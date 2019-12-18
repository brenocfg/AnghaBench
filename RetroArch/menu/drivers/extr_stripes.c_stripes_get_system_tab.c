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
struct TYPE_3__ {unsigned int system_tab_end; int* tabs; } ;
typedef  TYPE_1__ stripes_handle_t ;

/* Variables and functions */
 int UINT_MAX ; 

__attribute__((used)) static unsigned stripes_get_system_tab(stripes_handle_t *stripes, unsigned i)
{
   if (i <= stripes->system_tab_end)
   {
      return stripes->tabs[i];
   }
   return UINT_MAX;
}