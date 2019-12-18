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
struct TYPE_2__ {int fp0; int hi; int lo; } ;

/* Variables and functions */
 int NUM_PSEUDO_REGS ; 
 int NUM_REGS ; 
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mips_dwarf_dwarf2_ecoff_reg_to_regnum (int num)
{
  int regnum;
  if (num >= 0 && num < 32)
    regnum = num;
  else if (num >= 32 && num < 64)
    regnum = num + mips_regnum (current_gdbarch)->fp0 - 32;
  else if (num == 64)
    regnum = mips_regnum (current_gdbarch)->hi;
  else if (num == 65)
    regnum = mips_regnum (current_gdbarch)->lo;
  else
    /* This will hopefully (eventually) provoke a warning.  Should we
       be calling complaint() here?  */
    return NUM_REGS + NUM_PSEUDO_REGS;
  return NUM_REGS + regnum;
}