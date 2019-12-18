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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int SIZEOF_STRUCT_REG ; 
 int /*<<< orphan*/  mipsnbsd_supply_fpreg (char*,int) ; 
 int /*<<< orphan*/  mipsnbsd_supply_reg (char*,int) ; 

__attribute__((used)) static void
fetch_core_registers (char *core_reg_sect, unsigned core_reg_size, int which,
                      CORE_ADDR ignore)
{
  char *regs, *fpregs;

  /* We get everything from one section.  */
  if (which != 0)
    return;

  regs = core_reg_sect;
  fpregs = core_reg_sect + SIZEOF_STRUCT_REG;

  /* Integer registers.  */
  mipsnbsd_supply_reg (regs, -1);

  /* Floating point registers.  */
  mipsnbsd_supply_fpreg (fpregs, -1);
}