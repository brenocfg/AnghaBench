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

/* Variables and functions */
 scalar_t__ DECL_IS_MALLOC (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_IS_NOVOPS (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_IS_PURE (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_IS_RETURNS_TWICE (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 int ECF_CONST ; 
 int ECF_MALLOC ; 
 int ECF_NORETURN ; 
 int ECF_NOTHROW ; 
 int ECF_NOVOPS ; 
 int ECF_PURE ; 
 int ECF_RETURNS_TWICE ; 
 int ECF_SP_DEPRESSED ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_NOTHROW (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_READONLY (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_THIS_VOLATILE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_READONLY (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_RETURNS_STACK_DEPRESSED (int /*<<< orphan*/ ) ; 
 int special_function_p (int /*<<< orphan*/ ,int) ; 

int
flags_from_decl_or_type (tree exp)
{
  int flags = 0;
  tree type = exp;

  if (DECL_P (exp))
    {
      type = TREE_TYPE (exp);

      /* The function exp may have the `malloc' attribute.  */
      if (DECL_IS_MALLOC (exp))
	flags |= ECF_MALLOC;

      /* The function exp may have the `returns_twice' attribute.  */
      if (DECL_IS_RETURNS_TWICE (exp))
	flags |= ECF_RETURNS_TWICE;

      /* The function exp may have the `pure' attribute.  */
      if (DECL_IS_PURE (exp))
	flags |= ECF_PURE;

      if (DECL_IS_NOVOPS (exp))
	flags |= ECF_NOVOPS;

      if (TREE_NOTHROW (exp))
	flags |= ECF_NOTHROW;

      if (TREE_READONLY (exp) && ! TREE_THIS_VOLATILE (exp))
	flags |= ECF_CONST;

      flags = special_function_p (exp, flags);
    }
  else if (TYPE_P (exp) && TYPE_READONLY (exp) && ! TREE_THIS_VOLATILE (exp))
    flags |= ECF_CONST;

  if (TREE_THIS_VOLATILE (exp))
    flags |= ECF_NORETURN;

  /* Mark if the function returns with the stack pointer depressed.   We
     cannot consider it pure or constant in that case.  */
  if (TREE_CODE (type) == FUNCTION_TYPE && TYPE_RETURNS_STACK_DEPRESSED (type))
    {
      flags |= ECF_SP_DEPRESSED;
      flags &= ~(ECF_PURE | ECF_CONST);
    }

  return flags;
}