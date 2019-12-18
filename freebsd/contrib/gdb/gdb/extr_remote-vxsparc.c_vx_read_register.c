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
struct regcache {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_GETFPREGS ; 
 int /*<<< orphan*/  PTRACE_GETREGS ; 
 int SPARC_FPREG_PLEN ; 
 int SPARC_GREG_PLEN ; 
 struct regcache* current_regcache ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  net_read_registers (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparc32_supply_fpregset (struct regcache*,int,char*) ; 
 int /*<<< orphan*/  sparc32_supply_gregset (int /*<<< orphan*/ *,struct regcache*,int,char*) ; 
 scalar_t__ target_has_fp ; 
 int /*<<< orphan*/  vxsparc_gregset ; 

void
vx_read_register (int regnum)
{
  struct regcache *regcache = current_regcache;
  char gregs[SPARC_GREG_PLEN];
  char fpregs[SPARC_FPREG_PLEN];
  CORE_ADDR sp;

  /* Get the general-purpose registers.  */
  net_read_registers (gregs, SPARC_GREG_PLEN, PTRACE_GETREGS);
  sparc32_supply_gregset (&vxsparc_gregset, regcache, -1, gregs);

  /* If the target has floating-point registers, fetch them.
     Otherwise, zero the floating-point register values in GDB's
     register cache for good measure, even though we might not need
     to.  */
  if (target_has_fp)
    net_read_registers (fpregs, SPARC_FPREG_PLEN, PTRACE_GETFPREGS);
  else
    memset (fpregs, 0, SPARC_FPREG_PLEN);
  sparc32_supply_fpregset (regcache, -1, fpregs);
}