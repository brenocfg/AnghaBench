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
 int /*<<< orphan*/  alpha_supply_fp_regs (int,char*,char*) ; 
 int /*<<< orphan*/  alpha_supply_int_regs (int,char*,char*,char*) ; 
 int /*<<< orphan*/  error (char*,unsigned int) ; 

__attribute__((used)) static void
fetch_elf_core_registers (char *core_reg_sect, unsigned core_reg_size,
			  int which, CORE_ADDR reg_addr)
{
  if (core_reg_size < 32 * 8)
    {
      error ("Core file register section too small (%u bytes).", core_reg_size);
      return;
    }

  switch (which)
    {
    case 0: /* integer registers */
      /* PC is in slot 32; UNIQUE is in slot 33, if present.  */
      alpha_supply_int_regs (-1, core_reg_sect, core_reg_sect + 31*8,
			     (core_reg_size >= 33 * 8
			      ? core_reg_sect + 32*8 : NULL));
      break;

    case 2: /* floating-point registers */
      /* FPCR is in slot 32.  */
      alpha_supply_fp_regs (-1, core_reg_sect, core_reg_sect + 31*8);
      break;

    default:
      break;
    }
}