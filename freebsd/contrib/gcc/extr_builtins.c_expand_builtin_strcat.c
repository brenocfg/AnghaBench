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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 size_t BUILT_IN_STRLEN ; 
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PLUS_EXPR ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 scalar_t__ build_function_call_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ build_tree_list (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ builtin_save_expr (scalar_t__) ; 
 char* c_getstr (scalar_t__) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  expand_builtin_strcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  expand_expr (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  get_insns () ; 
 scalar_t__* implicit_built_in_decls ; 
 int /*<<< orphan*/  optimize_size ; 
 int /*<<< orphan*/  start_sequence () ; 
 scalar_t__ tree_cons (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_strcat (tree fndecl, tree arglist, rtx target, enum machine_mode mode)
{
  if (!validate_arglist (arglist, POINTER_TYPE, POINTER_TYPE, VOID_TYPE))
    return 0;
  else
    {
      tree dst = TREE_VALUE (arglist),
      src = TREE_VALUE (TREE_CHAIN (arglist));
      const char *p = c_getstr (src);

      /* If the string length is zero, return the dst parameter.  */
      if (p && *p == '\0')
	return expand_expr (dst, target, mode, EXPAND_NORMAL);

      if (!optimize_size)
	{
	  /* See if we can store by pieces into (dst + strlen(dst)).  */
	  tree newsrc, newdst,
	    strlen_fn = implicit_built_in_decls[BUILT_IN_STRLEN];
	  rtx insns;

	  /* Stabilize the argument list.  */
	  newsrc = builtin_save_expr (src);
	  if (newsrc != src)
	    arglist = build_tree_list (NULL_TREE, newsrc);
	  else
	    arglist = TREE_CHAIN (arglist); /* Reusing arglist if safe.  */

	  dst = builtin_save_expr (dst);

	  start_sequence ();

	  /* Create strlen (dst).  */
	  newdst =
	    build_function_call_expr (strlen_fn,
				      build_tree_list (NULL_TREE, dst));
	  /* Create (dst + (cast) strlen (dst)).  */
	  newdst = fold_convert (TREE_TYPE (dst), newdst);
	  newdst = fold_build2 (PLUS_EXPR, TREE_TYPE (dst), dst, newdst);

	  newdst = builtin_save_expr (newdst);
	  arglist = tree_cons (NULL_TREE, newdst, arglist);

	  if (!expand_builtin_strcpy (fndecl, arglist, target, mode))
	    {
	      end_sequence (); /* Stop sequence.  */
	      return 0;
	    }

	  /* Output the entire sequence.  */
	  insns = get_insns ();
	  end_sequence ();
	  emit_insn (insns);

	  return expand_expr (dst, target, mode, EXPAND_NORMAL);
	}

      return 0;
    }
}