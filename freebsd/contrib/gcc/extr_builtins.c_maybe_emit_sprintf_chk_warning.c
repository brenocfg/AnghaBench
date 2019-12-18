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
typedef  int /*<<< orphan*/  location_t ;
typedef  enum built_in_function { ____Placeholder_built_in_function } built_in_function ;

/* Variables and functions */
 int BUILT_IN_SPRINTF_CHK ; 
 int /*<<< orphan*/  EXPR_LOCATION (scalar_t__) ; 
 int /*<<< orphan*/  POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ build_int_cstu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* c_getstr (scalar_t__) ; 
 scalar_t__ c_strlen (scalar_t__,int) ; 
 int /*<<< orphan*/  get_callee_fndecl (scalar_t__) ; 
 int /*<<< orphan*/  host_integerp (scalar_t__,int) ; 
 int /*<<< orphan*/  init_target_chars () ; 
 scalar_t__ integer_all_onesp (scalar_t__) ; 
 int /*<<< orphan*/  size_type_node ; 
 scalar_t__ strchr (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  target_percent ; 
 int /*<<< orphan*/  target_percent_s ; 
 int /*<<< orphan*/  tree_int_cst_lt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
maybe_emit_sprintf_chk_warning (tree exp, enum built_in_function fcode)
{
  tree arglist = TREE_OPERAND (exp, 1);
  tree dest, size, len, fmt, flag;
  const char *fmt_str;

  /* Verify the required arguments in the original call.  */
  if (! arglist)
    return;
  dest = TREE_VALUE (arglist);
  arglist = TREE_CHAIN (arglist);
  if (! arglist)
    return;
  flag = TREE_VALUE (arglist);
  arglist = TREE_CHAIN (arglist);
  if (! arglist)
    return;
  size = TREE_VALUE (arglist);
  arglist = TREE_CHAIN (arglist);
  if (! arglist)
    return;
  fmt = TREE_VALUE (arglist);
  arglist = TREE_CHAIN (arglist);

  if (! host_integerp (size, 1) || integer_all_onesp (size))
    return;

  /* Check whether the format is a literal string constant.  */
  fmt_str = c_getstr (fmt);
  if (fmt_str == NULL)
    return;

  if (!init_target_chars())
    return;

  /* If the format doesn't contain % args or %%, we know its size.  */
  if (strchr (fmt_str, target_percent) == 0)
    len = build_int_cstu (size_type_node, strlen (fmt_str));
  /* If the format is "%s" and first ... argument is a string literal,
     we know it too.  */
  else if (fcode == BUILT_IN_SPRINTF_CHK && strcmp (fmt_str, target_percent_s) == 0)
    {
      tree arg;

      if (! arglist)
	return;
      arg = TREE_VALUE (arglist);
      if (! POINTER_TYPE_P (TREE_TYPE (arg)))
	return;

      len = c_strlen (arg, 1);
      if (!len || ! host_integerp (len, 1))
	return;
    }
  else
    return;

  if (! tree_int_cst_lt (len, size))
    {
      location_t locus = EXPR_LOCATION (exp);
      warning (0, "%Hcall to %D will always overflow destination buffer",
	       &locus, get_callee_fndecl (exp));
    }
}