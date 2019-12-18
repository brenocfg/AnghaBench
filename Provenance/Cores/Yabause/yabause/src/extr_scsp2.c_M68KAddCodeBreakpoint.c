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
struct TYPE_2__ {scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  M68KExecBP ; 
 int MAX_BREAKPOINTS ; 
 TYPE_1__* m68k_breakpoint ; 
 int /*<<< orphan*/  m68k_execf ; 
 int m68k_num_breakpoints ; 

int M68KAddCodeBreakpoint(u32 address)
{
   int i;

   if (m68k_num_breakpoints >= MAX_BREAKPOINTS)
      return -1;

   // Make sure it isn't already on the list
   for (i = 0; i < m68k_num_breakpoints; i++)
   {
      if (m68k_breakpoint[i].addr == address)
         return -1;
   }

   m68k_breakpoint[m68k_num_breakpoints].addr = address;
   m68k_num_breakpoints++;

   // Switch to the slow exec routine so we can catch the breakpoint
   m68k_execf = M68KExecBP;

   return 0;
}