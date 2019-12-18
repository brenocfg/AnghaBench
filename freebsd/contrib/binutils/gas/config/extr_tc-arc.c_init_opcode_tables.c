#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  valueT ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  arc_get_opcode_mach (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc_opcode_init_tables (int /*<<< orphan*/ ) ; 
 TYPE_2__* arc_reg_names ; 
 int arc_reg_names_count ; 
 int /*<<< orphan*/ * arc_suffix_hash ; 
 TYPE_1__* arc_suffixes ; 
 int arc_suffixes_count ; 
 int /*<<< orphan*/  as_fatal (char*) ; 
 int /*<<< orphan*/  as_warn (char*) ; 
 int /*<<< orphan*/  bfd_arch_arc ; 
 int /*<<< orphan*/  bfd_set_arch_mach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int cpu_tables_init_p ; 
 int /*<<< orphan*/  hash_insert (int /*<<< orphan*/ *,char*,void*) ; 
 int /*<<< orphan*/ * hash_new () ; 
 int /*<<< orphan*/  reg_section ; 
 int /*<<< orphan*/  stdoutput ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  symbol_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ symbol_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_table_insert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_big_endian ; 
 int /*<<< orphan*/  zero_address_frag ; 

__attribute__((used)) static void
init_opcode_tables (int mach)
{
  int i;
  char *last;

  if ((arc_suffix_hash = hash_new ()) == NULL)
    as_fatal ("virtual memory exhausted");

  if (!bfd_set_arch_mach (stdoutput, bfd_arch_arc, mach))
    as_warn ("could not set architecture and machine");

  /* This initializes a few things in arc-opc.c that we need.
     This must be called before the various arc_xxx_supported fns.  */
  arc_opcode_init_tables (arc_get_opcode_mach (mach, target_big_endian));

  /* Only put the first entry of each equivalently named suffix in the
     table.  */
  last = "";
  for (i = 0; i < arc_suffixes_count; i++)
    {
      if (strcmp (arc_suffixes[i].name, last) != 0)
	hash_insert (arc_suffix_hash, arc_suffixes[i].name, (void *) (arc_suffixes + i));
      last = arc_suffixes[i].name;
    }

  /* Since registers don't have a prefix, we put them in the symbol table so
     they can't be used as symbols.  This also simplifies argument parsing as
     we can let gas parse registers for us.  The recorded register number is
     the address of the register's entry in arc_reg_names.

     If the register name is already in the table, then the existing
     definition is assumed to be from an .ExtCoreRegister pseudo-op.  */

  for (i = 0; i < arc_reg_names_count; i++)
    {
      if (symbol_find (arc_reg_names[i].name))
	continue;
      /* Use symbol_create here instead of symbol_new so we don't try to
	 output registers into the object file's symbol table.  */
      symbol_table_insert (symbol_create (arc_reg_names[i].name,
					  reg_section,
					  (valueT) &arc_reg_names[i],
					  &zero_address_frag));
    }

  /* Tell `.option' it's too late.  */
  cpu_tables_init_p = 1;
}