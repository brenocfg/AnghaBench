#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* var_ann_t ;
typedef  scalar_t__ tree ;
struct TYPE_3__ {scalar_t__ symbol_mem_tag; unsigned int escape_mask; scalar_t__ is_aliased; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DECL_UID (scalar_t__) ; 
 unsigned int ESCAPE_BAD_CAST ; 
 unsigned int ESCAPE_IS_GLOBAL ; 
 unsigned int ESCAPE_IS_PARM ; 
 unsigned int ESCAPE_STORED_IN_GLOBAL ; 
 unsigned int ESCAPE_TO_ASM ; 
 unsigned int ESCAPE_TO_CALL ; 
 unsigned int ESCAPE_TO_PURE_CONST ; 
 unsigned int ESCAPE_TO_RETURN ; 
 unsigned int ESCAPE_UNKNOWN ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ SSA_NAME_VAR (scalar_t__) ; 
 int TDF_DETAILS ; 
 scalar_t__ TREE_ADDRESSABLE (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_THIS_VOLATILE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ default_def (scalar_t__) ; 
 int dump_flags ; 
 int /*<<< orphan*/  dump_may_aliases_for (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dump_points_to_info_for (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dump_subvars_for (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ get_subvars_for_var (scalar_t__) ; 
 scalar_t__ is_call_clobbered (scalar_t__) ; 
 scalar_t__ is_global_var (scalar_t__) ; 
 scalar_t__ may_aliases (scalar_t__) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,scalar_t__,int) ; 
 TYPE_1__* var_ann (scalar_t__) ; 

void
dump_variable (FILE *file, tree var)
{
  var_ann_t ann;

  if (TREE_CODE (var) == SSA_NAME)
    {
      if (POINTER_TYPE_P (TREE_TYPE (var)))
	dump_points_to_info_for (file, var);
      var = SSA_NAME_VAR (var);
    }

  if (var == NULL_TREE)
    {
      fprintf (file, "<nil>");
      return;
    }

  print_generic_expr (file, var, dump_flags);

  ann = var_ann (var);

  fprintf (file, ", UID %u", (unsigned) DECL_UID (var));

  fprintf (file, ", ");
  print_generic_expr (file, TREE_TYPE (var), dump_flags);

  if (ann && ann->symbol_mem_tag)
    {
      fprintf (file, ", symbol memory tag: ");
      print_generic_expr (file, ann->symbol_mem_tag, dump_flags);
    }

  if (ann && ann->is_aliased)
    fprintf (file, ", is aliased");

  if (TREE_ADDRESSABLE (var))
    fprintf (file, ", is addressable");
  
  if (is_global_var (var))
    fprintf (file, ", is global");

  if (TREE_THIS_VOLATILE (var))
    fprintf (file, ", is volatile");

  if (is_call_clobbered (var))
    {
      fprintf (file, ", call clobbered");
      if (dump_flags & TDF_DETAILS)
	{
	  var_ann_t va = var_ann (var);
	  unsigned int escape_mask = va->escape_mask;
	  
	  fprintf (file, " (");
	  if (escape_mask & ESCAPE_STORED_IN_GLOBAL)
	    fprintf (file, ", stored in global");
	  if (escape_mask & ESCAPE_TO_ASM)
	    fprintf (file, ", goes through ASM");
	  if (escape_mask & ESCAPE_TO_CALL)
	    fprintf (file, ", passed to call");
	  if (escape_mask & ESCAPE_BAD_CAST)
	    fprintf (file, ", bad cast");
	  if (escape_mask & ESCAPE_TO_RETURN)
	    fprintf (file, ", returned from func");
	  if (escape_mask & ESCAPE_TO_PURE_CONST)
	    fprintf (file, ", passed to pure/const");
	  if (escape_mask & ESCAPE_IS_GLOBAL)
	    fprintf (file, ", is global var");
	  if (escape_mask & ESCAPE_IS_PARM)
	    fprintf (file, ", is incoming pointer");
	  if (escape_mask & ESCAPE_UNKNOWN)
	    fprintf (file, ", unknown escape");
	  fprintf (file, " )");
	}
    }

  if (default_def (var))
    {
      fprintf (file, ", default def: ");
      print_generic_expr (file, default_def (var), dump_flags);
    }

  if (may_aliases (var))
    {
      fprintf (file, ", may aliases: ");
      dump_may_aliases_for (file, var);
    }

  if (get_subvars_for_var (var))
    {
      fprintf (file, ", sub-vars: ");
      dump_subvars_for (file, var);
    }

  fprintf (file, "\n");
}