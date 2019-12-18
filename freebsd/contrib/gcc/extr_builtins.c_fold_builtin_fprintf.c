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
typedef  enum built_in_function { ____Placeholder_built_in_function } built_in_function ;

/* Variables and functions */
 int BUILT_IN_FPRINTF_CHK ; 
 int BUILT_IN_FPRINTF_UNLOCKED ; 
 size_t BUILT_IN_FPUTC ; 
 size_t BUILT_IN_FPUTC_UNLOCKED ; 
 size_t BUILT_IN_FPUTS ; 
 size_t BUILT_IN_FPUTS_UNLOCKED ; 
 int BUILT_IN_VFPRINTF ; 
 int BUILT_IN_VFPRINTF_CHK ; 
 scalar_t__ INTEGER_TYPE ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_SIDE_EFFECTS (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ build_function_call_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ build_int_cst (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ build_tree_list (scalar_t__,scalar_t__) ; 
 scalar_t__* built_in_decls ; 
 char* c_getstr (scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__* implicit_built_in_decls ; 
 int /*<<< orphan*/  init_target_chars () ; 
 int /*<<< orphan*/ * strchr (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_percent ; 
 int /*<<< orphan*/  target_percent_c ; 
 int /*<<< orphan*/  target_percent_s ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
fold_builtin_fprintf (tree fndecl, tree arglist, bool ignore,
		      enum built_in_function fcode)
{
  tree fp, fmt, fn = NULL_TREE, fn_fputc, fn_fputs, arg, call;
  const char *fmt_str = NULL;

  /* If the return value is used, don't do the transformation.  */
  if (! ignore)
    return 0;

  /* Verify the required arguments in the original call.  */
  if (! arglist)
    return 0;
  fp = TREE_VALUE (arglist);
  if (! POINTER_TYPE_P (TREE_TYPE (fp)))
    return 0;
  arglist = TREE_CHAIN (arglist);

  if (fcode == BUILT_IN_FPRINTF_CHK || fcode == BUILT_IN_VFPRINTF_CHK)
    {
      tree flag;

      if (! arglist)
	return 0;
      flag = TREE_VALUE (arglist);
      if (TREE_CODE (TREE_TYPE (flag)) != INTEGER_TYPE
	  || TREE_SIDE_EFFECTS (flag))
	return 0;
      arglist = TREE_CHAIN (arglist);
    }

  if (! arglist)
    return 0;
  fmt = TREE_VALUE (arglist);
  if (! POINTER_TYPE_P (TREE_TYPE (fmt)))
    return 0;
  arglist = TREE_CHAIN (arglist);

  /* Check whether the format is a literal string constant.  */
  fmt_str = c_getstr (fmt);
  if (fmt_str == NULL)
    return NULL_TREE;

  if (fcode == BUILT_IN_FPRINTF_UNLOCKED)
    {
      /* If we're using an unlocked function, assume the other
	 unlocked functions exist explicitly.  */
      fn_fputc = built_in_decls[BUILT_IN_FPUTC_UNLOCKED];
      fn_fputs = built_in_decls[BUILT_IN_FPUTS_UNLOCKED];
    }
  else
    {
      fn_fputc = implicit_built_in_decls[BUILT_IN_FPUTC];
      fn_fputs = implicit_built_in_decls[BUILT_IN_FPUTS];
    }

  if (!init_target_chars())
    return 0;

  /* If the format doesn't contain % args or %%, use strcpy.  */
  if (strchr (fmt_str, target_percent) == NULL)
    {
      if (fcode != BUILT_IN_VFPRINTF && fcode != BUILT_IN_VFPRINTF_CHK
	  && arglist)
	return 0;

      /* If the format specifier was "", fprintf does nothing.  */
      if (fmt_str[0] == '\0')
	{
	  /* If FP has side-effects, just wait until gimplification is
	     done.  */
	  if (TREE_SIDE_EFFECTS (fp))
	    return 0;

	  return build_int_cst (TREE_TYPE (TREE_TYPE (fndecl)), 0);
	}

      /* When "string" doesn't contain %, replace all cases of
	 fprintf (fp, string) with fputs (string, fp).  The fputs
	 builtin will take care of special cases like length == 1.  */
      arglist = build_tree_list (NULL_TREE, fp);
      arglist = tree_cons (NULL_TREE, fmt, arglist);
      fn = fn_fputs;
    }

  /* The other optimizations can be done only on the non-va_list variants.  */
  else if (fcode == BUILT_IN_VFPRINTF || fcode == BUILT_IN_VFPRINTF_CHK)
    return 0;

  /* If the format specifier was "%s", call __builtin_fputs (arg, fp).  */
  else if (strcmp (fmt_str, target_percent_s) == 0)
    {
      if (! arglist
	  || ! POINTER_TYPE_P (TREE_TYPE (TREE_VALUE (arglist)))
	  || TREE_CHAIN (arglist))
	return 0;
      arg = TREE_VALUE (arglist);
      arglist = build_tree_list (NULL_TREE, fp);
      arglist = tree_cons (NULL_TREE, arg, arglist);
      fn = fn_fputs;
    }

  /* If the format specifier was "%c", call __builtin_fputc (arg, fp).  */
  else if (strcmp (fmt_str, target_percent_c) == 0)
    {
      if (! arglist
	  || TREE_CODE (TREE_TYPE (TREE_VALUE (arglist))) != INTEGER_TYPE
	  || TREE_CHAIN (arglist))
	return 0;
      arg = TREE_VALUE (arglist);
      arglist = build_tree_list (NULL_TREE, fp);
      arglist = tree_cons (NULL_TREE, arg, arglist);
      fn = fn_fputc;
    }

  if (!fn)
    return 0;

  call = build_function_call_expr (fn, arglist);
  return fold_convert (TREE_TYPE (TREE_TYPE (fndecl)), call);
}