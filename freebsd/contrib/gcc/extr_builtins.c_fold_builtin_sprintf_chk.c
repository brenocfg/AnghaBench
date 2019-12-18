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
 size_t BUILT_IN_SPRINTF ; 
 int BUILT_IN_SPRINTF_CHK ; 
 size_t BUILT_IN_VSPRINTF ; 
 int BUILT_IN_VSPRINTF_CHK ; 
 scalar_t__ INTEGER_TYPE ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ build_function_call_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ build_int_cstu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__* built_in_decls ; 
 char* c_getstr (scalar_t__) ; 
 scalar_t__ c_strlen (scalar_t__,int) ; 
 int /*<<< orphan*/  host_integerp (scalar_t__,int) ; 
 int /*<<< orphan*/  init_target_chars () ; 
 int /*<<< orphan*/  integer_all_onesp (scalar_t__) ; 
 int /*<<< orphan*/  integer_zerop (scalar_t__) ; 
 int /*<<< orphan*/  size_type_node ; 
 int /*<<< orphan*/ * strchr (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  target_percent ; 
 int /*<<< orphan*/  target_percent_s ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tree_int_cst_lt (scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
fold_builtin_sprintf_chk (tree arglist, enum built_in_function fcode)
{
  tree dest, size, len, fn, fmt, flag;
  const char *fmt_str;

  /* Verify the required arguments in the original call.  */
  if (! arglist)
    return 0;
  dest = TREE_VALUE (arglist);
  if (! POINTER_TYPE_P (TREE_TYPE (dest)))
    return 0;
  arglist = TREE_CHAIN (arglist);
  if (! arglist)
    return 0;
  flag = TREE_VALUE (arglist);
  if (TREE_CODE (TREE_TYPE (flag)) != INTEGER_TYPE)
    return 0;
  arglist = TREE_CHAIN (arglist);
  if (! arglist)
    return 0;
  size = TREE_VALUE (arglist);
  if (TREE_CODE (TREE_TYPE (size)) != INTEGER_TYPE)
    return 0;
  arglist = TREE_CHAIN (arglist);
  if (! arglist)
    return 0;
  fmt = TREE_VALUE (arglist);
  if (! POINTER_TYPE_P (TREE_TYPE (fmt)))
    return 0;
  arglist = TREE_CHAIN (arglist);

  if (! host_integerp (size, 1))
    return 0;

  len = NULL_TREE;

  if (!init_target_chars())
    return 0;

  /* Check whether the format is a literal string constant.  */
  fmt_str = c_getstr (fmt);
  if (fmt_str != NULL)
    {
      /* If the format doesn't contain % args or %%, we know the size.  */
      if (strchr (fmt_str, target_percent) == 0)
	{
	  if (fcode != BUILT_IN_SPRINTF_CHK || arglist == NULL_TREE)
	    len = build_int_cstu (size_type_node, strlen (fmt_str));
	}
      /* If the format is "%s" and first ... argument is a string literal,
	 we know the size too.  */
      else if (fcode == BUILT_IN_SPRINTF_CHK && strcmp (fmt_str, target_percent_s) == 0)
	{
	  tree arg;

	  if (arglist && !TREE_CHAIN (arglist))
	    {
	      arg = TREE_VALUE (arglist);
	      if (POINTER_TYPE_P (TREE_TYPE (arg)))
		{
		  len = c_strlen (arg, 1);
		  if (! len || ! host_integerp (len, 1))
		    len = NULL_TREE;
		}
	    }
	}
    }

  if (! integer_all_onesp (size))
    {
      if (! len || ! tree_int_cst_lt (len, size))
	return 0;
    }

  /* Only convert __{,v}sprintf_chk to {,v}sprintf if flag is 0
     or if format doesn't contain % chars or is "%s".  */
  if (! integer_zerop (flag))
    {
      if (fmt_str == NULL)
	return 0;
      if (strchr (fmt_str, target_percent) != NULL && strcmp (fmt_str, target_percent_s))
	return 0;
    }

  arglist = tree_cons (NULL_TREE, fmt, arglist);
  arglist = tree_cons (NULL_TREE, dest, arglist);

  /* If __builtin_{,v}sprintf_chk is used, assume {,v}sprintf is available.  */
  fn = built_in_decls[fcode == BUILT_IN_VSPRINTF_CHK
		      ? BUILT_IN_VSPRINTF : BUILT_IN_SPRINTF];
  if (!fn)
    return 0;

  return build_function_call_expr (fn, arglist);
}