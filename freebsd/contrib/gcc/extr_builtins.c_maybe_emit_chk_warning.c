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
#define  BUILT_IN_SNPRINTF_CHK 133 
#define  BUILT_IN_STPCPY_CHK 132 
#define  BUILT_IN_STRCAT_CHK 131 
#define  BUILT_IN_STRCPY_CHK 130 
#define  BUILT_IN_STRNCPY_CHK 129 
#define  BUILT_IN_VSNPRINTF_CHK 128 
 int /*<<< orphan*/  EXPR_LOCATION (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ c_strlen (scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_callee_fndecl (scalar_t__) ; 
 int /*<<< orphan*/  host_integerp (scalar_t__,int) ; 
 scalar_t__ integer_all_onesp (scalar_t__) ; 
 scalar_t__ tree_int_cst_lt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
maybe_emit_chk_warning (tree exp, enum built_in_function fcode)
{
  int arg_mask, is_strlen = 0;
  tree arglist = TREE_OPERAND (exp, 1), a;
  tree len, size;
  location_t locus;

  switch (fcode)
    {
    case BUILT_IN_STRCPY_CHK:
    case BUILT_IN_STPCPY_CHK:
    /* For __strcat_chk the warning will be emitted only if overflowing
       by at least strlen (dest) + 1 bytes.  */
    case BUILT_IN_STRCAT_CHK:
      arg_mask = 6;
      is_strlen = 1;
      break;
    case BUILT_IN_STRNCPY_CHK:
      arg_mask = 12;
      break;
    case BUILT_IN_SNPRINTF_CHK:
    case BUILT_IN_VSNPRINTF_CHK:
      arg_mask = 10;
      break;
    default:
      gcc_unreachable ();
    }

  len = NULL_TREE;
  size = NULL_TREE;
  for (a = arglist; a && arg_mask; a = TREE_CHAIN (a), arg_mask >>= 1)
    if (arg_mask & 1)
      {
	if (len)
	  size = a;
	else
	  len = a;
      }

  if (!len || !size)
    return;

  len = TREE_VALUE (len);
  size = TREE_VALUE (size);

  if (! host_integerp (size, 1) || integer_all_onesp (size))
    return;

  if (is_strlen)
    {
      len = c_strlen (len, 1);
      if (! len || ! host_integerp (len, 1) || tree_int_cst_lt (len, size))
	return;
    }
  else if (! host_integerp (len, 1) || ! tree_int_cst_lt (size, len))
    return;

  locus = EXPR_LOCATION (exp);
  warning (0, "%Hcall to %D will always overflow destination buffer",
	   &locus, get_callee_fndecl (exp));
}