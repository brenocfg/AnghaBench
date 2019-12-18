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

/* Variables and functions */
 size_t BUILT_IN_SPRINTF ; 
 size_t BUILT_IN_STRCPY ; 
 int /*<<< orphan*/  COMPOUND_EXPR ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_function_call_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ build_int_cst (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_tree_list (scalar_t__,scalar_t__) ; 
 char* c_getstr (scalar_t__) ; 
 scalar_t__ c_strlen (scalar_t__,int) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__* implicit_built_in_decls ; 
 int /*<<< orphan*/  init_target_chars () ; 
 int /*<<< orphan*/ * strchr (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  target_percent ; 
 int /*<<< orphan*/  target_percent_s ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static tree
fold_builtin_sprintf (tree arglist, int ignored)
{
  tree call, retval, dest, fmt;
  const char *fmt_str = NULL;

  /* Verify the required arguments in the original call.  We deal with two
     types of sprintf() calls: 'sprintf (str, fmt)' and
     'sprintf (dest, "%s", orig)'.  */
  if (!validate_arglist (arglist, POINTER_TYPE, POINTER_TYPE, VOID_TYPE)
      && !validate_arglist (arglist, POINTER_TYPE, POINTER_TYPE, POINTER_TYPE,
			    VOID_TYPE))
    return NULL_TREE;

  /* Get the destination string and the format specifier.  */
  dest = TREE_VALUE (arglist);
  fmt = TREE_VALUE (TREE_CHAIN (arglist));
  arglist = TREE_CHAIN (TREE_CHAIN (arglist));

  /* Check whether the format is a literal string constant.  */
  fmt_str = c_getstr (fmt);
  if (fmt_str == NULL)
    return NULL_TREE;

  call = NULL_TREE;
  retval = NULL_TREE;

  if (!init_target_chars())
    return 0;

  /* If the format doesn't contain % args or %%, use strcpy.  */
  if (strchr (fmt_str, target_percent) == NULL)
    {
      tree fn = implicit_built_in_decls[BUILT_IN_STRCPY];

      if (!fn)
	return NULL_TREE;

      /* Don't optimize sprintf (buf, "abc", ptr++).  */
      if (arglist)
	return NULL_TREE;

      /* Convert sprintf (str, fmt) into strcpy (str, fmt) when
	 'format' is known to contain no % formats.  */
      arglist = build_tree_list (NULL_TREE, fmt);
      arglist = tree_cons (NULL_TREE, dest, arglist);
      call = build_function_call_expr (fn, arglist);
      if (!ignored)
	retval = build_int_cst (NULL_TREE, strlen (fmt_str));
    }

  /* If the format is "%s", use strcpy if the result isn't used.  */
  else if (fmt_str && strcmp (fmt_str, target_percent_s) == 0)
    {
      tree fn, orig;
      fn = implicit_built_in_decls[BUILT_IN_STRCPY];

      if (!fn)
	return NULL_TREE;

      /* Don't crash on sprintf (str1, "%s").  */
      if (!arglist)
	return NULL_TREE;

      /* Convert sprintf (str1, "%s", str2) into strcpy (str1, str2).  */
      orig = TREE_VALUE (arglist);
      arglist = build_tree_list (NULL_TREE, orig);
      arglist = tree_cons (NULL_TREE, dest, arglist);
      if (!ignored)
	{
	  retval = c_strlen (orig, 1);
	  if (!retval || TREE_CODE (retval) != INTEGER_CST)
	    return NULL_TREE;
	}
      call = build_function_call_expr (fn, arglist);
    }

  if (call && retval)
    {
      retval = fold_convert
	(TREE_TYPE (TREE_TYPE (implicit_built_in_decls[BUILT_IN_SPRINTF])),
	 retval);
      return build2 (COMPOUND_EXPR, TREE_TYPE (retval), call, retval);
    }
  else
    return call;
}