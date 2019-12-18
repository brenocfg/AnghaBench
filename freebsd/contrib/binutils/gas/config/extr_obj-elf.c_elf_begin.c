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
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_SECTION_NAME ; 
 int /*<<< orphan*/  DATA_SECTION_NAME ; 
 int /*<<< orphan*/  TEXT_SECTION_NAME ; 
 int /*<<< orphan*/  bfd_com_section_ptr ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elf_com_section_ptr ; 
 int /*<<< orphan*/  section_symbol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdoutput ; 
 int /*<<< orphan*/  symbol_table_insert (int /*<<< orphan*/ ) ; 

void
elf_begin (void)
{
  asection *s;

  /* Add symbols for the known sections to the symbol table.  */
  s = bfd_get_section_by_name (stdoutput, TEXT_SECTION_NAME);
  symbol_table_insert (section_symbol (s));
  s = bfd_get_section_by_name (stdoutput, DATA_SECTION_NAME);
  symbol_table_insert (section_symbol (s));
  s = bfd_get_section_by_name (stdoutput, BSS_SECTION_NAME);
  symbol_table_insert (section_symbol (s));
  elf_com_section_ptr = bfd_com_section_ptr;
}