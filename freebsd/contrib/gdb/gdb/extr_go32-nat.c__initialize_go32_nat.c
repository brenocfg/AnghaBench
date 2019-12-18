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
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_info ; 
 int /*<<< orphan*/  go32_info_dos_command ; 
 int /*<<< orphan*/  go32_ops ; 
 int /*<<< orphan*/  go32_pde ; 
 int /*<<< orphan*/  go32_pte ; 
 int /*<<< orphan*/  go32_pte_for_address ; 
 int /*<<< orphan*/  go32_sgdt ; 
 int /*<<< orphan*/  go32_sidt ; 
 int /*<<< orphan*/  go32_sldt ; 
 int /*<<< orphan*/  go32_sysinfo ; 
 int /*<<< orphan*/  info_dos_cmdlist ; 
 int /*<<< orphan*/  infolist ; 
 int /*<<< orphan*/  init_go32_ops () ; 

void
_initialize_go32_nat (void)
{
  init_go32_ops ();
  add_target (&go32_ops);

  add_prefix_cmd ("dos", class_info, go32_info_dos_command,
		  "Print information specific to DJGPP (aka MS-DOS) debugging.",
		  &info_dos_cmdlist, "info dos ", 0, &infolist);

  add_cmd ("sysinfo", class_info, go32_sysinfo,
	    "Display information about the target system, including CPU, OS, DPMI, etc.",
	   &info_dos_cmdlist);
  add_cmd ("ldt", class_info, go32_sldt,
	   "Display entries in the LDT (Local Descriptor Table).\n"
	   "Entry number (an expression) as an argument means display only that entry.",
	   &info_dos_cmdlist);
  add_cmd ("gdt", class_info, go32_sgdt,
	   "Display entries in the GDT (Global Descriptor Table).\n"
	   "Entry number (an expression) as an argument means display only that entry.",
	   &info_dos_cmdlist);
  add_cmd ("idt", class_info, go32_sidt,
	   "Display entries in the IDT (Interrupt Descriptor Table).\n"
	   "Entry number (an expression) as an argument means display only that entry.",
	   &info_dos_cmdlist);
  add_cmd ("pde", class_info, go32_pde,
	   "Display entries in the Page Directory.\n"
	   "Entry number (an expression) as an argument means display only that entry.",
	   &info_dos_cmdlist);
  add_cmd ("pte", class_info, go32_pte,
	   "Display entries in Page Tables.\n"
	   "Entry number (an expression) as an argument means display only entries\n"
	   "from the Page Table pointed to by the specified Page Directory entry.",
	   &info_dos_cmdlist);
  add_cmd ("address-pte", class_info, go32_pte_for_address,
	   "Display a Page Table entry for a linear address.\n"
	   "The address argument must be a linear address, after adding to\n"
	   "it the base address of the appropriate segment.\n"
	   "The base address of variables and functions in the debuggee's data\n"
	   "or code segment is stored in the variable __djgpp_base_address,\n"
	   "so use `__djgpp_base_address + (char *)&var' as the argument.\n"
	   "For other segments, look up their base address in the output of\n"
	   "the `info dos ldt' command.",
	   &info_dos_cmdlist);
}