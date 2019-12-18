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
 scalar_t__ DEFAULT_ARG ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 char* TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  can_convert_arg (scalar_t__,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  local_variable_p_walkfn ; 
 scalar_t__ walk_tree_without_duplicates (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

tree
check_default_argument (tree decl, tree arg)
{
  tree var;
  tree decl_type;

  if (TREE_CODE (arg) == DEFAULT_ARG)
    /* We get a DEFAULT_ARG when looking at an in-class declaration
       with a default argument.  Ignore the argument for now; we'll
       deal with it after the class is complete.  */
    return arg;

  if (TYPE_P (decl))
    {
      decl_type = decl;
      decl = NULL_TREE;
    }
  else
    decl_type = TREE_TYPE (decl);

  if (arg == error_mark_node
      || decl == error_mark_node
      || TREE_TYPE (arg) == error_mark_node
      || decl_type == error_mark_node)
    /* Something already went wrong.  There's no need to check
       further.  */
    return error_mark_node;

  /* [dcl.fct.default]

     A default argument expression is implicitly converted to the
     parameter type.  */
  if (!TREE_TYPE (arg)
      || !can_convert_arg (decl_type, TREE_TYPE (arg), arg, LOOKUP_NORMAL))
    {
      if (decl)
	error ("default argument for %q#D has type %qT",
	       decl, TREE_TYPE (arg));
      else
	error ("default argument for parameter of type %qT has type %qT",
	       decl_type, TREE_TYPE (arg));

      return error_mark_node;
    }

  /* [dcl.fct.default]

     Local variables shall not be used in default argument
     expressions.

     The keyword `this' shall not be used in a default argument of a
     member function.  */
  var = walk_tree_without_duplicates (&arg, local_variable_p_walkfn,
				      NULL);
  if (var)
    {
      error ("default argument %qE uses local variable %qD", arg, var);
      return error_mark_node;
    }

  /* All is well.  */
  return arg;
}