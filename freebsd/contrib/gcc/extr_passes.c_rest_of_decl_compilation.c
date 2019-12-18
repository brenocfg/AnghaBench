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
typedef  scalar_t__ tree ;
struct TYPE_2__ {int /*<<< orphan*/  (* type_decl ) (scalar_t__,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_FINISH_DECLARE_OBJECT (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 scalar_t__ DECL_ASSEMBLER_NAME_SET_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_ATTRIBUTES (scalar_t__) ; 
 int /*<<< orphan*/  DECL_DEFER_OUTPUT (scalar_t__) ; 
 scalar_t__ DECL_EXTERNAL (scalar_t__) ; 
 scalar_t__ DECL_INITIAL (scalar_t__) ; 
 scalar_t__ DECL_REGISTER (scalar_t__) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_STATIC (scalar_t__) ; 
 int /*<<< orphan*/  TREE_STRING_POINTER (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TV_SYMOUT ; 
 int /*<<< orphan*/  TV_VARCONST ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  asm_out_file ; 
 int /*<<< orphan*/  assemble_alias (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assemble_variable (scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgraph_varpool_finalize_decl (scalar_t__) ; 
 int /*<<< orphan*/  cgraph_varpool_node (scalar_t__) ; 
 TYPE_1__* debug_hooks ; 
 scalar_t__ errorcount ; 
 scalar_t__ get_identifier (int /*<<< orphan*/ ) ; 
 scalar_t__ last_assemble_variable_decl ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_decl_rtl (scalar_t__) ; 
 scalar_t__ sorrycount ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int) ; 
 int /*<<< orphan*/  timevar_pop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

void
rest_of_decl_compilation (tree decl,
			  int top_level,
			  int at_end)
{
  /* We deferred calling assemble_alias so that we could collect
     other attributes such as visibility.  Emit the alias now.  */
  {
    tree alias;
    alias = lookup_attribute ("alias", DECL_ATTRIBUTES (decl));
    if (alias)
      {
	alias = TREE_VALUE (TREE_VALUE (alias));
	alias = get_identifier (TREE_STRING_POINTER (alias));
	assemble_alias (decl, alias);
      }
  }

  /* Can't defer this, because it needs to happen before any
     later function definitions are processed.  */
  if (DECL_ASSEMBLER_NAME_SET_P (decl) && DECL_REGISTER (decl))
    make_decl_rtl (decl);

  /* Forward declarations for nested functions are not "external",
     but we need to treat them as if they were.  */
  if (TREE_STATIC (decl) || DECL_EXTERNAL (decl)
      || TREE_CODE (decl) == FUNCTION_DECL)
    {
      timevar_push (TV_VARCONST);

      /* Don't output anything when a tentative file-scope definition
	 is seen.  But at end of compilation, do output code for them.

	 We do output all variables when unit-at-a-time is active and rely on
	 callgraph code to defer them except for forward declarations
	 (see gcc.c-torture/compile/920624-1.c) */
      if ((at_end
	   || !DECL_DEFER_OUTPUT (decl)
	   || DECL_INITIAL (decl))
	  && !DECL_EXTERNAL (decl))
	{
	  if (TREE_CODE (decl) != FUNCTION_DECL)
	    cgraph_varpool_finalize_decl (decl);
	  else
	    assemble_variable (decl, top_level, at_end, 0);
	}

#ifdef ASM_FINISH_DECLARE_OBJECT
      if (decl == last_assemble_variable_decl)
	{
	  ASM_FINISH_DECLARE_OBJECT (asm_out_file, decl,
				     top_level, at_end);
	}
#endif

      timevar_pop (TV_VARCONST);
    }
  else if (TREE_CODE (decl) == TYPE_DECL
	   /* Like in rest_of_type_compilation, avoid confusing the debug
	      information machinery when there are errors.  */
	   && !(sorrycount || errorcount))
    {
      timevar_push (TV_SYMOUT);
      debug_hooks->type_decl (decl, !top_level);
      timevar_pop (TV_SYMOUT);
    }

  /* Let cgraph know about the existence of variables.  */
  if (TREE_CODE (decl) == VAR_DECL && !DECL_EXTERNAL (decl))
    cgraph_varpool_node (decl);
}