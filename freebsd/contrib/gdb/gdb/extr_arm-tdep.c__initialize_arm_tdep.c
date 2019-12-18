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
struct ui_file {int dummy; } ;
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_OSABI_ARM_APCS ; 
 int /*<<< orphan*/  GDB_OSABI_ARM_EABI_V1 ; 
 int /*<<< orphan*/  GDB_OSABI_ARM_EABI_V2 ; 
 struct cmd_list_element* add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cmd_list_element* add_set_enum_cmd (char*,int /*<<< orphan*/ ,char const**,char const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_setshow_boolean_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_setshow_cmd_full (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cmd_list_element**,struct cmd_list_element**) ; 
 struct cmd_list_element* add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arm_apcs_32 ; 
 int /*<<< orphan*/  arm_debug ; 
 int /*<<< orphan*/  arm_dump_tdep ; 
 int /*<<< orphan*/  arm_elf_osabi_sniffer ; 
 int /*<<< orphan*/  arm_gdbarch_init ; 
 int /*<<< orphan*/  arm_init_abi_apcs ; 
 int /*<<< orphan*/  arm_init_abi_eabi_v1 ; 
 int /*<<< orphan*/  arm_init_abi_eabi_v2 ; 
 int /*<<< orphan*/  arm_othernames ; 
 char** arm_register_names ; 
 int /*<<< orphan*/  bfd_arch_arm ; 
 int /*<<< orphan*/  bfd_target_elf_flavour ; 
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  class_obscure ; 
 char const* current_fp_model ; 
 int current_option ; 
 int /*<<< orphan*/  deprecate_cmd (struct cmd_list_element*,char*) ; 
 char const* disassembly_style ; 
 char const** fp_model_strings ; 
 int /*<<< orphan*/  fprintf_unfiltered (struct ui_file*,char*,...) ; 
 int /*<<< orphan*/  gdbarch_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdbarch_register_osabi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdbarch_register_osabi_sniffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int get_arm_regname_num_options () ; 
 int get_arm_regnames (int,char const**,char const**,char const***) ; 
 struct ui_file* mem_fileopen () ; 
 int /*<<< orphan*/  no_class ; 
 int num_disassembly_options ; 
 int /*<<< orphan*/  parse_arm_disassembler_option (char*) ; 
 int /*<<< orphan*/  set_arm_command ; 
 int /*<<< orphan*/  set_arm_regname_option (int) ; 
 int /*<<< orphan*/  set_cmd_sfunc (struct cmd_list_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_disassembly_style_sfunc ; 
 int /*<<< orphan*/  set_fp_model_sfunc ; 
 int /*<<< orphan*/  setarmcmdlist ; 
 int /*<<< orphan*/  setdebuglist ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  show_arm_command ; 
 int /*<<< orphan*/  show_fp_model ; 
 int /*<<< orphan*/  showarmcmdlist ; 
 int /*<<< orphan*/  showdebuglist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  ui_file_delete (struct ui_file*) ; 
 char* ui_file_xstrdup (struct ui_file*,long*) ; 
 char const** valid_disassembly_styles ; 
 int /*<<< orphan*/  var_boolean ; 
 char** xmalloc (int) ; 

void
_initialize_arm_tdep (void)
{
  struct ui_file *stb;
  long length;
  struct cmd_list_element *new_set, *new_show;
  const char *setname;
  const char *setdesc;
  const char **regnames;
  int numregs, i, j;
  static char *helptext;

  gdbarch_register (bfd_arch_arm, arm_gdbarch_init, arm_dump_tdep);

  /* Register an ELF OS ABI sniffer for ARM binaries.  */
  gdbarch_register_osabi_sniffer (bfd_arch_arm,
				  bfd_target_elf_flavour,
				  arm_elf_osabi_sniffer);

  /* Register some ABI variants for embedded systems.  */
  gdbarch_register_osabi (bfd_arch_arm, 0, GDB_OSABI_ARM_EABI_V1,
                          arm_init_abi_eabi_v1);
  gdbarch_register_osabi (bfd_arch_arm, 0, GDB_OSABI_ARM_EABI_V2,
                          arm_init_abi_eabi_v2);
  gdbarch_register_osabi (bfd_arch_arm, 0, GDB_OSABI_ARM_APCS,
                          arm_init_abi_apcs);

  /* Get the number of possible sets of register names defined in opcodes.  */
  num_disassembly_options = get_arm_regname_num_options ();

  /* Add root prefix command for all "set arm"/"show arm" commands.  */
  add_prefix_cmd ("arm", no_class, set_arm_command,
		  "Various ARM-specific commands.",
		  &setarmcmdlist, "set arm ", 0, &setlist);

  add_prefix_cmd ("arm", no_class, show_arm_command,
		  "Various ARM-specific commands.",
		  &showarmcmdlist, "show arm ", 0, &showlist);

  /* Sync the opcode insn printer with our register viewer.  */
  parse_arm_disassembler_option ("reg-names-std");

  /* Begin creating the help text.  */
  stb = mem_fileopen ();
  fprintf_unfiltered (stb, "Set the disassembly style.\n"
		      "The valid values are:\n");

  /* Initialize the array that will be passed to add_set_enum_cmd().  */
  valid_disassembly_styles
    = xmalloc ((num_disassembly_options + 1) * sizeof (char *));
  for (i = 0; i < num_disassembly_options; i++)
    {
      numregs = get_arm_regnames (i, &setname, &setdesc, &regnames);
      valid_disassembly_styles[i] = setname;
      fprintf_unfiltered (stb, "%s - %s\n", setname,
			  setdesc);
      /* Copy the default names (if found) and synchronize disassembler.  */
      if (!strcmp (setname, "std"))
	{
          disassembly_style = setname;
          current_option = i;
	  for (j = 0; j < numregs; j++)
            arm_register_names[j] = (char *) regnames[j];
          set_arm_regname_option (i);
	}
    }
  /* Mark the end of valid options.  */
  valid_disassembly_styles[num_disassembly_options] = NULL;

  /* Finish the creation of the help text.  */
  fprintf_unfiltered (stb, "The default is \"std\".");
  helptext = ui_file_xstrdup (stb, &length);
  ui_file_delete (stb);

  /* Add the deprecated disassembly-flavor command.  */
  new_set = add_set_enum_cmd ("disassembly-flavor", no_class,
			      valid_disassembly_styles,
			      &disassembly_style,
			      helptext,
			      &setlist);
  set_cmd_sfunc (new_set, set_disassembly_style_sfunc);
  deprecate_cmd (new_set, "set arm disassembly");
  deprecate_cmd (add_show_from_set (new_set, &showlist),
		 "show arm disassembly");

  /* And now add the new interface.  */
  new_set = add_set_enum_cmd ("disassembler", no_class,
			      valid_disassembly_styles, &disassembly_style,
			      helptext, &setarmcmdlist);

  set_cmd_sfunc (new_set, set_disassembly_style_sfunc);
  add_show_from_set (new_set, &showarmcmdlist);

  add_setshow_cmd_full ("apcs32", no_class,
			var_boolean, (char *) &arm_apcs_32,
			"Set usage of ARM 32-bit mode.",
			"Show usage of ARM 32-bit mode.",
			NULL, NULL,
			&setlist, &showlist, &new_set, &new_show);
  deprecate_cmd (new_set, "set arm apcs32");
  deprecate_cmd (new_show, "show arm apcs32");

  add_setshow_boolean_cmd ("apcs32", no_class, &arm_apcs_32,
			   "Set usage of ARM 32-bit mode.  "
			   "When off, a 26-bit PC will be used.",
			   "Show usage of ARM 32-bit mode.  "
			   "When off, a 26-bit PC will be used.",
			   NULL, NULL,
			   &setarmcmdlist, &showarmcmdlist);

  /* Add a command to allow the user to force the FPU model.  */
  new_set = add_set_enum_cmd
    ("fpu", no_class, fp_model_strings, &current_fp_model,
     "Set the floating point type.\n"
     "auto - Determine the FP typefrom the OS-ABI.\n"
     "softfpa - Software FP, mixed-endian doubles on little-endian ARMs.\n"
     "fpa - FPA co-processor (GCC compiled).\n"
     "softvfp - Software FP with pure-endian doubles.\n"
     "vfp - VFP co-processor.",
     &setarmcmdlist);
  set_cmd_sfunc (new_set, set_fp_model_sfunc);
  set_cmd_sfunc (add_show_from_set (new_set, &showarmcmdlist), show_fp_model);

  /* Add the deprecated "othernames" command.  */
  deprecate_cmd (add_com ("othernames", class_obscure, arm_othernames,
			  "Switch to the next set of register names."),
		 "set arm disassembly");

  /* Debugging flag.  */
  add_setshow_boolean_cmd ("arm", class_maintenance, &arm_debug,
			   "Set ARM debugging.  "
			   "When on, arm-specific debugging is enabled.",
			   "Show ARM debugging.  "
			   "When on, arm-specific debugging is enabled.",
			   NULL, NULL,
			   &setdebuglist, &showdebuglist);
}