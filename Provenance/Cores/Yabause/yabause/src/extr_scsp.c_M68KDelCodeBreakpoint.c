#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  Exec; } ;
struct TYPE_5__ {int numcodebreakpoints; TYPE_1__* codebreakpoint; } ;
struct TYPE_4__ {int addr; } ;

/* Variables and functions */
 TYPE_3__* M68K ; 
 int /*<<< orphan*/  M68KSortCodeBreakpoints () ; 
 TYPE_2__* ScspInternalVars ; 
 int /*<<< orphan*/  m68kexecptr ; 

int
M68KDelCodeBreakpoint (u32 addr)
{
  int i;
  if (ScspInternalVars->numcodebreakpoints > 0)
    {
      for (i = 0; i < ScspInternalVars->numcodebreakpoints; i++)
        {
          if (ScspInternalVars->codebreakpoint[i].addr == addr)
            {
              ScspInternalVars->codebreakpoint[i].addr = 0xFFFFFFFF;
              M68KSortCodeBreakpoints ();
              ScspInternalVars->numcodebreakpoints--;
              if (ScspInternalVars->numcodebreakpoints == 0)
                m68kexecptr = M68K->Exec;
              return 0;
            }
        }
    }

  return -1;
}