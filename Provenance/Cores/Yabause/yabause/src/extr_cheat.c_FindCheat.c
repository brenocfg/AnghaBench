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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int type; scalar_t__ addr; scalar_t__ val; } ;

/* Variables and functions */
 TYPE_1__* cheatlist ; 
 int numcheats ; 

__attribute__((used)) static int FindCheat(int type, u32 addr, u32 val)
{
   int i;

   for (i = 0; i < numcheats; i++)
   {
      if (cheatlist[i].type == type &&
          cheatlist[i].addr == addr &&
          cheatlist[i].val == val)
         return i;
   }

   return -1;
}