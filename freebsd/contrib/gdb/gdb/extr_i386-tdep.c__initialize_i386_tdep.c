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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_OSABI_GO32 ; 
 int /*<<< orphan*/  GDB_OSABI_NETWARE ; 
 int /*<<< orphan*/  GDB_OSABI_SVR4 ; 
 struct cmd_list_element* add_set_enum_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_show_from_set (struct cmd_list_element*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_arch_i386 ; 
 int /*<<< orphan*/  bfd_target_coff_flavour ; 
 int /*<<< orphan*/  bfd_target_nlm_flavour ; 
 int /*<<< orphan*/  disassembly_flavor ; 
 int /*<<< orphan*/  gdbarch_register_osabi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdbarch_register_osabi_sniffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i386_coff_osabi_sniffer ; 
 int /*<<< orphan*/  i386_gdbarch_init ; 
 int /*<<< orphan*/  i386_go32_init_abi ; 
 int /*<<< orphan*/  i386_init_reggroups () ; 
 int /*<<< orphan*/  i386_nlm_osabi_sniffer ; 
 int /*<<< orphan*/  i386_nw_init_abi ; 
 int /*<<< orphan*/  i386_svr4_init_abi ; 
 int /*<<< orphan*/  no_class ; 
 int /*<<< orphan*/  register_gdbarch_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlist ; 
 int /*<<< orphan*/  showlist ; 
 int /*<<< orphan*/  struct_convention ; 
 int /*<<< orphan*/  valid_conventions ; 
 int /*<<< orphan*/  valid_flavors ; 

void
_initialize_i386_tdep (void)
{
  register_gdbarch_init (bfd_arch_i386, i386_gdbarch_init);

  /* Add the variable that controls the disassembly flavor.  */
  {
    struct cmd_list_element *new_cmd;

    new_cmd = add_set_enum_cmd ("disassembly-flavor", no_class,
				valid_flavors,
				&disassembly_flavor,
				"\
Set the disassembly flavor, the valid values are \"att\" and \"intel\", \
and the default value is \"att\".",
				&setlist);
    add_show_from_set (new_cmd, &showlist);
  }

  /* Add the variable that controls the convention for returning
     structs.  */
  {
    struct cmd_list_element *new_cmd;

    new_cmd = add_set_enum_cmd ("struct-convention", no_class,
				valid_conventions,
				&struct_convention, "\
Set the convention for returning small structs, valid values \
are \"default\", \"pcc\" and \"reg\", and the default value is \"default\".",
                                &setlist);
    add_show_from_set (new_cmd, &showlist);
  }

  gdbarch_register_osabi_sniffer (bfd_arch_i386, bfd_target_coff_flavour,
				  i386_coff_osabi_sniffer);
  gdbarch_register_osabi_sniffer (bfd_arch_i386, bfd_target_nlm_flavour,
				  i386_nlm_osabi_sniffer);

  gdbarch_register_osabi (bfd_arch_i386, 0, GDB_OSABI_SVR4,
			  i386_svr4_init_abi);
  gdbarch_register_osabi (bfd_arch_i386, 0, GDB_OSABI_GO32,
			  i386_go32_init_abi);
  gdbarch_register_osabi (bfd_arch_i386, 0, GDB_OSABI_NETWARE,
			  i386_nw_init_abi);

  /* Initialize the i386 specific register groups.  */
  i386_init_reggroups ();
}