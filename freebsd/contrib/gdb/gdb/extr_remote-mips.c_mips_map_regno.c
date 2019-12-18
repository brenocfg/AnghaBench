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
struct TYPE_2__ {int fp0; int pc; int cause; int hi; int lo; int fp_control_status; int fp_implementation_revision; } ;

/* Variables and functions */
 int REGNO_OFFSET ; 
 int /*<<< orphan*/  current_gdbarch ; 
 TYPE_1__* mips_regnum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mips_map_regno (int regno)
{
  if (regno < 32)
    return regno;
  if (regno >= mips_regnum (current_gdbarch)->fp0
      && regno < mips_regnum (current_gdbarch)->fp0 + 32)
    return regno - mips_regnum (current_gdbarch)->fp0 + 32;
  else if (regno == mips_regnum (current_gdbarch)->pc)
    return REGNO_OFFSET + 0;
  else if (regno == mips_regnum (current_gdbarch)->cause)
    return REGNO_OFFSET + 1;
  else if (regno == mips_regnum (current_gdbarch)->hi)
    return REGNO_OFFSET + 2;
  else if (regno == mips_regnum (current_gdbarch)->lo)
    return REGNO_OFFSET + 3;
  else if (regno == mips_regnum (current_gdbarch)->fp_control_status)
    return REGNO_OFFSET + 4;
  else if (regno == mips_regnum (current_gdbarch)->fp_implementation_revision)
    return REGNO_OFFSET + 5;
  else
    /* FIXME: Is there a way to get the status register?  */
    return 0;
}