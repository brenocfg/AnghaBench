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
struct TYPE_2__ {int pc; int cause; int hi; int lo; int fp_control_status; int fp_implementation_revision; } ;

/* Variables and functions */
 int CAUSE ; 
 int FP0_REGNUM ; 
 int FPC_CSR ; 
 int FPC_EIR ; 
 int FPR_BASE ; 
 int GPR_BASE ; 
 int MMHI ; 
 int MMLO ; 
 int PC ; 
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
register_ptrace_addr (int regno)
{
  return (regno < 32 ? GPR_BASE + regno
	  : regno == mips_regnum (current_gdbarch)->pc ? PC
	  : regno == mips_regnum (current_gdbarch)->cause ? CAUSE
	  : regno == mips_regnum (current_gdbarch)->hi ? MMHI
	  : regno == mips_regnum (current_gdbarch)->lo ? MMLO
	  : regno == mips_regnum (current_gdbarch)->fp_control_status ? FPC_CSR
	  : regno == mips_regnum (current_gdbarch)->fp_implementation_revision ? FPC_EIR
	  : regno >= FP0_REGNUM ? FPR_BASE + (regno - FP0_REGNUM)
	  : 0);
}