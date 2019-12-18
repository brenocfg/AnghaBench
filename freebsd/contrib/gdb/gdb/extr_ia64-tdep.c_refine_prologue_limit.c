#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct symtab_and_line {scalar_t__ line; scalar_t__ end; scalar_t__ symtab; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 struct symtab_and_line find_pc_line (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ get_pc_function_start (scalar_t__) ; 
 int max_skip_non_prologue_insns ; 

__attribute__((used)) static CORE_ADDR
refine_prologue_limit (CORE_ADDR pc, CORE_ADDR lim_pc, int *trust_limit)
{
  struct symtab_and_line prologue_sal;
  CORE_ADDR start_pc = pc;

  /* Start off not trusting the limit.  */
  *trust_limit = 0;

  prologue_sal = find_pc_line (pc, 0);
  if (prologue_sal.line != 0)
    {
      int i;
      CORE_ADDR addr = prologue_sal.end;

      /* Handle the case in which compiler's optimizer/scheduler
         has moved instructions into the prologue.  We scan ahead
	 in the function looking for address ranges whose corresponding
	 line number is less than or equal to the first one that we
	 found for the function.  (It can be less than when the
	 scheduler puts a body instruction before the first prologue
	 instruction.)  */
      for (i = 2 * max_skip_non_prologue_insns; 
           i > 0 && (lim_pc == 0 || addr < lim_pc);
	   i--)
        {
	  struct symtab_and_line sal;

	  sal = find_pc_line (addr, 0);
	  if (sal.line == 0)
	    break;
	  if (sal.line <= prologue_sal.line 
	      && sal.symtab == prologue_sal.symtab)
	    {
	      prologue_sal = sal;
	    }
	  addr = sal.end;
	}

      if (lim_pc == 0 || prologue_sal.end < lim_pc)
	{
	  lim_pc = prologue_sal.end;
	  if (start_pc == get_pc_function_start (lim_pc))
	    *trust_limit = 1;
	}
    }
  return lim_pc;
}