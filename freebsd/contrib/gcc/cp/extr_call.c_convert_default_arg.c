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
typedef  char* tree ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTANT_CLASS_P (char*) ; 
 scalar_t__ CONSTRUCTOR ; 
 scalar_t__ DECL_TEMPLATE_INFO (char*) ; 
 scalar_t__ DEFAULT_ARG ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 scalar_t__ TREE_CODE (char*) ; 
 char* break_out_target_exprs (char*) ; 
 char* convert_for_arg_passing (char*,char*) ; 
 char* convert_for_initialization (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,char*,int) ; 
 char* digest_init (char*,char*) ; 
 int /*<<< orphan*/  error (char*,int,char*) ; 
 char* error_mark_node ; 
 char* tsubst_default_argument (char*,char*,char*) ; 
 char* unshare_expr (char*) ; 

tree
convert_default_arg (tree type, tree arg, tree fn, int parmnum)
{
  /* If the ARG is an unparsed default argument expression, the
     conversion cannot be performed.  */
  if (TREE_CODE (arg) == DEFAULT_ARG)
    {
      error ("the default argument for parameter %d of %qD has "
	     "not yet been parsed",
	     parmnum, fn);
      return error_mark_node;
    }

  if (fn && DECL_TEMPLATE_INFO (fn))
    arg = tsubst_default_argument (fn, type, arg);

  arg = break_out_target_exprs (arg);

  if (TREE_CODE (arg) == CONSTRUCTOR)
    {
      arg = digest_init (type, arg);
      arg = convert_for_initialization (0, type, arg, LOOKUP_NORMAL,
					"default argument", fn, parmnum);
    }
  else
    {
      /* We must make a copy of ARG, in case subsequent processing
	 alters any part of it.  For example, during gimplification a
	 cast of the form (T) &X::f (where "f" is a member function)
	 will lead to replacing the PTRMEM_CST for &X::f with a
	 VAR_DECL.  We can avoid the copy for constants, since they
	 are never modified in place.  */
      if (!CONSTANT_CLASS_P (arg))
	arg = unshare_expr (arg);
      arg = convert_for_initialization (0, type, arg, LOOKUP_NORMAL,
					"default argument", fn, parmnum);
      arg = convert_for_arg_passing (type, arg);
    }

  return arg;
}