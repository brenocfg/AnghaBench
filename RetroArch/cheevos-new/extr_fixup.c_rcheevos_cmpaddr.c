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
struct TYPE_2__ {scalar_t__ address; } ;
typedef  TYPE_1__ rcheevos_fixup_t ;

/* Variables and functions */

__attribute__((used)) static int rcheevos_cmpaddr(const void* e1, const void* e2)
{
   const rcheevos_fixup_t* f1 = (const rcheevos_fixup_t*)e1;
   const rcheevos_fixup_t* f2 = (const rcheevos_fixup_t*)e2;

   if (f1->address < f2->address)
   {
      return -1;
   }
   else if (f1->address > f2->address)
   {
      return 1;
   }
   else
   {
      return 0;
   }
}