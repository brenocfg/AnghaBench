#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* insn_mo; } ;
struct TYPE_6__ {int /*<<< orphan*/  noreorder; } ;
struct TYPE_5__ {unsigned long pinfo; } ;

/* Variables and functions */
 unsigned int EXTRACT_OPERAND (int /*<<< orphan*/ ,TYPE_3__) ; 
 unsigned long INSN_LOAD_COPROC_DELAY ; 
 unsigned long INSN_LOAD_MEMORY_DELAY ; 
 unsigned long INSN_WRITE_GPR_T ; 
 int /*<<< orphan*/  RT ; 
 int /*<<< orphan*/  cop_interlocks ; 
 int /*<<< orphan*/  gpr_interlocks ; 
 TYPE_3__* history ; 
 int /*<<< orphan*/  know (unsigned long) ; 
 TYPE_2__ mips_opts ; 

__attribute__((used)) static int
reg_needs_delay (unsigned int reg)
{
  unsigned long prev_pinfo;

  prev_pinfo = history[0].insn_mo->pinfo;
  if (! mips_opts.noreorder
      && (((prev_pinfo & INSN_LOAD_MEMORY_DELAY)
	   && ! gpr_interlocks)
	  || ((prev_pinfo & INSN_LOAD_COPROC_DELAY)
	      && ! cop_interlocks)))
    {
      /* A load from a coprocessor or from memory.  All load delays
	 delay the use of general register rt for one instruction.  */
      /* Itbl support may require additional care here.  */
      know (prev_pinfo & INSN_WRITE_GPR_T);
      if (reg == EXTRACT_OPERAND (RT, history[0]))
	return 1;
    }

  return 0;
}