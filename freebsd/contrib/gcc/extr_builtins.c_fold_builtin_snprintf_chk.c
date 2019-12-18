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
typedef  int /*<<< orphan*/  tree ;
typedef  enum built_in_function { ____Placeholder_built_in_function } built_in_function ;

/* Variables and functions */
 size_t BUILT_IN_SNPRINTF ; 
 size_t BUILT_IN_VSNPRINTF ; 
 int BUILT_IN_VSNPRINTF_CHK ; 
 scalar_t__ INTEGER_TYPE ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * built_in_decls ; 
 char* c_getstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_integerp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  init_target_chars () ; 
 int /*<<< orphan*/  integer_all_onesp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_percent ; 
 int /*<<< orphan*/  target_percent_s ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_int_cst_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
fold_builtin_snprintf_chk (tree arglist, tree maxlen,
			   enum built_in_function fcode)
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
  len = TREE_VALUE (arglist);
  if (TREE_CODE (TREE_TYPE (len)) != INTEGER_TYPE)
    return 0;
  arglist = TREE_CHAIN (arglist);
  if (! arglist)
    return 0;
  flag = TREE_VALUE (arglist);
  if (TREE_CODE (TREE_TYPE (len)) != INTEGER_TYPE)
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

  if (! integer_all_onesp (size))
    {
      if (! host_integerp (len, 1))
	{
	  /* If LEN is not constant, try MAXLEN too.
	     For MAXLEN only allow optimizing into non-_ocs function
	     if SIZE is >= MAXLEN, never convert to __ocs_fail ().  */
	  if (maxlen == NULL_TREE || ! host_integerp (maxlen, 1))
	    return 0;
	}
      else
	maxlen = len;

      if (tree_int_cst_lt (size, maxlen))
	return 0;
    }

  if (!init_target_chars())
    return 0;

  /* Only convert __{,v}snprintf_chk to {,v}snprintf if flag is 0
     or if format doesn't contain % chars or is "%s".  */
  if (! integer_zerop (flag))
    {
      fmt_str = c_getstr (fmt);
      if (fmt_str == NULL)
	return 0;
      if (strchr (fmt_str, target_percent) != NULL && strcmp (fmt_str, target_percent_s))
	return 0;
    }

  arglist = tree_cons (NULL_TREE, fmt, arglist);
  arglist = tree_cons (NULL_TREE, len, arglist);
  arglist = tree_cons (NULL_TREE, dest, arglist);

  /* If __builtin_{,v}snprintf_chk is used, assume {,v}snprintf is
     available.  */
  fn = built_in_decls[fcode == BUILT_IN_VSNPRINTF_CHK
		      ? BUILT_IN_VSNPRINTF : BUILT_IN_SNPRINTF];
  if (!fn)
    return 0;

  return build_function_call_expr (fn, arglist);
}