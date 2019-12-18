#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dwarf2_debug {int dummy; } ;
struct comp_unit {int error; scalar_t__ first_child_die_ptr; scalar_t__ end_ptr; scalar_t__ line_table; int /*<<< orphan*/  stmtlist; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_1__ asymbol ;

/* Variables and functions */
 int BSF_FUNCTION ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ decode_line_info (struct comp_unit*,struct dwarf2_debug*) ; 
 int /*<<< orphan*/  lookup_symbol_in_function_table (struct comp_unit*,TYPE_1__*,int /*<<< orphan*/ ,char const**,unsigned int*) ; 
 int /*<<< orphan*/  lookup_symbol_in_variable_table (struct comp_unit*,TYPE_1__*,int /*<<< orphan*/ ,char const**,unsigned int*) ; 
 int /*<<< orphan*/  scan_unit_for_symbols (struct comp_unit*) ; 

__attribute__((used)) static bfd_boolean
comp_unit_find_line (struct comp_unit *unit,
		     asymbol *sym,
		     bfd_vma addr,
		     const char **filename_ptr,
		     unsigned int *linenumber_ptr,
		     struct dwarf2_debug *stash)
{
  if (unit->error)
    return FALSE;

  if (! unit->line_table)
    {
      if (! unit->stmtlist)
	{
	  unit->error = 1;
	  return FALSE;
	}

      unit->line_table = decode_line_info (unit, stash);

      if (! unit->line_table)
	{
	  unit->error = 1;
	  return FALSE;
	}

      if (unit->first_child_die_ptr < unit->end_ptr
	  && ! scan_unit_for_symbols (unit))
	{
	  unit->error = 1;
	  return FALSE;
	}
    }

  if (sym->flags & BSF_FUNCTION)
    return lookup_symbol_in_function_table (unit, sym, addr,
					    filename_ptr,
					    linenumber_ptr);
  else
    return lookup_symbol_in_variable_table (unit, sym, addr,
					    filename_ptr,
					    linenumber_ptr);
}