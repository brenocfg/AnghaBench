#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int numcodebreakpoints; TYPE_1__* codebreakpoint; } ;
struct TYPE_3__ {scalar_t__ addr; } ;

/* Variables and functions */
 int MAX_BREAKPOINTS ; 
 TYPE_2__* ScuBP ; 

int ScuDspAddCodeBreakpoint(u32 addr) {
   int i;

   if (ScuBP->numcodebreakpoints < MAX_BREAKPOINTS) {
      // Make sure it isn't already on the list
      for (i = 0; i < ScuBP->numcodebreakpoints; i++)
      {
         if (addr == ScuBP->codebreakpoint[i].addr)
            return -1;
      }

      ScuBP->codebreakpoint[ScuBP->numcodebreakpoints].addr = addr;
      ScuBP->numcodebreakpoints++;

      return 0;
   }

   return -1;
}