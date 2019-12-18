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
struct TYPE_2__ {int ppc_mq_regnum; int ppc_fpscr_regnum; } ;

/* Variables and functions */
 int BDM_NUM_REGS ; 
 scalar_t__ DEPRECATED_REGISTER_BYTE (int) ; 
 int FP0_REGNUM ; 
 int FPLAST_REGNUM ; 
 int NUM_REGS ; 
 int* bdm_regmap ; 
 int /*<<< orphan*/  current_gdbarch ; 
 scalar_t__ deprecated_registers ; 
 TYPE_1__* gdbarch_tdep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocd_write_bdm_registers (int,scalar_t__,int) ; 

__attribute__((used)) static void
bdm_ppc_store_registers (int regno)
{
  int i;
  int first_regno, last_regno;
  int first_bdm_regno, last_bdm_regno;

  if (regno == -1)
    {
      first_regno = 0;
      last_regno = NUM_REGS - 1;

      first_bdm_regno = 0;
      last_bdm_regno = BDM_NUM_REGS - 1;
    }
  else
    {
      first_regno = regno;
      last_regno = regno;

      first_bdm_regno = bdm_regmap[regno];
      last_bdm_regno = bdm_regmap[regno];
    }

  if (first_bdm_regno == -1)
    return;			/* Unsupported register */

  for (i = first_regno; i <= last_regno; i++)
    {
      int bdm_regno;

      bdm_regno = bdm_regmap[i];

      /* only attempt to write if it's a valid ppc 8xx register */
      /* (need to avoid FP regs and MQ reg) */
      if ((i != gdbarch_tdep (current_gdbarch)->ppc_mq_regnum) 
          && (i != gdbarch_tdep (current_gdbarch)->ppc_fpscr_regnum) 
          && ((i < FP0_REGNUM) || (i > FPLAST_REGNUM)))
	{
/*          printf("write valid reg %d\n", bdm_regno); */
	  ocd_write_bdm_registers (bdm_regno, deprecated_registers + DEPRECATED_REGISTER_BYTE (i), 4);
	}
/*
   else if (i == gdbarch_tdep (current_gdbarch)->ppc_mq_regnum)
   printf("don't write invalid reg %d (PPC_MQ_REGNUM)\n", bdm_regno);
   else
   printf("don't write invalid reg %d\n", bdm_regno);
 */
    }
}