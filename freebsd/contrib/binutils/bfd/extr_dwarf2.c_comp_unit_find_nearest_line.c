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
struct funcinfo {scalar_t__ tag; } ;
struct dwarf2_debug {struct funcinfo* inliner_chain; } ;
struct comp_unit {int error; scalar_t__ first_child_die_ptr; scalar_t__ end_ptr; scalar_t__ line_table; int /*<<< orphan*/  stmtlist; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int bfd_boolean ;

/* Variables and functions */
 scalar_t__ DW_TAG_inlined_subroutine ; 
 int FALSE ; 
 scalar_t__ decode_line_info (struct comp_unit*,struct dwarf2_debug*) ; 
 int lookup_address_in_function_table (struct comp_unit*,int /*<<< orphan*/ ,struct funcinfo**,char const**) ; 
 int lookup_address_in_line_info_table (scalar_t__,int /*<<< orphan*/ ,struct funcinfo*,char const**,unsigned int*) ; 
 int /*<<< orphan*/  scan_unit_for_symbols (struct comp_unit*) ; 

__attribute__((used)) static bfd_boolean
comp_unit_find_nearest_line (struct comp_unit *unit,
			     bfd_vma addr,
			     const char **filename_ptr,
			     const char **functionname_ptr,
			     unsigned int *linenumber_ptr,
			     struct dwarf2_debug *stash)
{
  bfd_boolean line_p;
  bfd_boolean func_p;
  struct funcinfo *function;

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

  function = NULL;
  func_p = lookup_address_in_function_table (unit, addr,
					     &function, functionname_ptr);
  if (func_p && (function->tag == DW_TAG_inlined_subroutine))
    stash->inliner_chain = function;
  line_p = lookup_address_in_line_info_table (unit->line_table, addr,
					      function, filename_ptr,
					      linenumber_ptr);
  return line_p || func_p;
}