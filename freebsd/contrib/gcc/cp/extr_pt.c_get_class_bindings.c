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
 int /*<<< orphan*/  INNERMOST_TEMPLATE_ARGS (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  SET_TMPL_ARGS_LEVEL (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  TMPL_ARGS_DEPTH (scalar_t__) ; 
 scalar_t__ TMPL_ARGS_HAVE_MULTIPLE_LEVELS (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VEC_ELT (scalar_t__,int) ; 
 int TREE_VEC_LENGTH (scalar_t__) ; 
 int /*<<< orphan*/  UNIFY_ALLOW_NONE ; 
 int /*<<< orphan*/  comp_template_args (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_node (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ make_tree_vec (int) ; 
 int /*<<< orphan*/  tf_none ; 
 scalar_t__ tsubst (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unify (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
get_class_bindings (tree tparms, tree spec_args, tree args)
{
  int i, ntparms = TREE_VEC_LENGTH (tparms);
  tree deduced_args;
  tree innermost_deduced_args;

  innermost_deduced_args = make_tree_vec (ntparms);
  if (TMPL_ARGS_HAVE_MULTIPLE_LEVELS (args))
    {
      deduced_args = copy_node (args);
      SET_TMPL_ARGS_LEVEL (deduced_args,
			   TMPL_ARGS_DEPTH (deduced_args),
			   innermost_deduced_args);
    }
  else
    deduced_args = innermost_deduced_args;

  if (unify (tparms, deduced_args,
	     INNERMOST_TEMPLATE_ARGS (spec_args),
	     INNERMOST_TEMPLATE_ARGS (args),
	     UNIFY_ALLOW_NONE))
    return NULL_TREE;

  for (i =  0; i < ntparms; ++i)
    if (! TREE_VEC_ELT (innermost_deduced_args, i))
      return NULL_TREE;

  /* Verify that nondeduced template arguments agree with the type
     obtained from argument deduction.

     For example:

       struct A { typedef int X; };
       template <class T, class U> struct C {};
       template <class T> struct C<T, typename T::X> {};

     Then with the instantiation `C<A, int>', we can deduce that
     `T' is `A' but unify () does not check whether `typename T::X'
     is `int'.  */
  spec_args = tsubst (spec_args, deduced_args, tf_none, NULL_TREE);
  if (spec_args == error_mark_node
      /* We only need to check the innermost arguments; the other
	 arguments will always agree.  */
      || !comp_template_args (INNERMOST_TEMPLATE_ARGS (spec_args),
			      INNERMOST_TEMPLATE_ARGS (args)))
    return NULL_TREE;

  return deduced_args;
}