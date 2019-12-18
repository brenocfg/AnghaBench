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
struct TYPE_4__ {int /*<<< orphan*/  Exec; } ;
struct TYPE_3__ {scalar_t__ addr; } ;

/* Variables and functions */
 TYPE_2__* M68K ; 
 TYPE_1__* m68k_breakpoint ; 
 int /*<<< orphan*/  m68k_execf ; 
 int m68k_num_breakpoints ; 

int M68KDelCodeBreakpoint(u32 address)
{
   int i;

   if (m68k_num_breakpoints > 0)
   {
      for (i = 0; i < m68k_num_breakpoints; i++)
      {
         if (m68k_breakpoint[i].addr == address)
         {
            // Swap with the last breakpoint in the table, so there are
            // no holes in the breakpoint list
            m68k_breakpoint[i].addr = m68k_breakpoint[m68k_num_breakpoints-1].addr;
            m68k_breakpoint[m68k_num_breakpoints-1].addr = 0xFFFFFFFF;
            m68k_num_breakpoints--;

            if (m68k_num_breakpoints == 0)
            {
               // Last breakpoint deleted, so go back to the fast exec routine
               m68k_execf = M68K->Exec;
            }

            return 0;
         }
      }
   }

   return -1;
}