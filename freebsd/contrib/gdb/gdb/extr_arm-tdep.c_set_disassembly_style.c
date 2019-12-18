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

/* Variables and functions */
 size_t ARM_FPS_REGNUM ; 
 size_t ARM_PC_REGNUM ; 
 size_t ARM_PS_REGNUM ; 
 char** arm_register_names ; 
 int current_option ; 
 char const* disassembly_style ; 
 int get_arm_regnames (int,char const**,char const**,char const***) ; 
 scalar_t__ isupper (char const) ; 
 int num_disassembly_options ; 
 int /*<<< orphan*/  set_arm_regname_option (int) ; 

__attribute__((used)) static void
set_disassembly_style (void)
{
  const char *setname, *setdesc, **regnames;
  int numregs, j;

  /* Find the style that the user wants in the opcodes table.  */
  int current = 0;
  numregs = get_arm_regnames (current, &setname, &setdesc, &regnames);
  while ((disassembly_style != setname)
	 && (current < num_disassembly_options))
    get_arm_regnames (++current, &setname, &setdesc, &regnames);
  current_option = current;

  /* Fill our copy.  */
  for (j = 0; j < numregs; j++)
    arm_register_names[j] = (char *) regnames[j];

  /* Adjust case.  */
  if (isupper (*regnames[ARM_PC_REGNUM]))
    {
      arm_register_names[ARM_FPS_REGNUM] = "FPS";
      arm_register_names[ARM_PS_REGNUM] = "CPSR";
    }
  else
    {
      arm_register_names[ARM_FPS_REGNUM] = "fps";
      arm_register_names[ARM_PS_REGNUM] = "cpsr";
    }

  /* Synchronize the disassembler.  */
  set_arm_regname_option (current);
}