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
 int /*<<< orphan*/  CLASSTYPE_TEMPLATE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLASSTYPE_TI_ARGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLASSTYPE_TI_TEMPLATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_VEC_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIFY_ALLOW_NONE ; 
 int /*<<< orphan*/  make_tree_vec (int /*<<< orphan*/ ) ; 
 scalar_t__ most_general_template (int /*<<< orphan*/ ) ; 
 scalar_t__ unify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
try_class_unification (tree tparms, tree targs, tree parm, tree arg)
{
  tree copy_of_targs;

  if (!CLASSTYPE_TEMPLATE_INFO (arg)
      || (most_general_template (CLASSTYPE_TI_TEMPLATE (arg))
	  != most_general_template (CLASSTYPE_TI_TEMPLATE (parm))))
    return NULL_TREE;

  /* We need to make a new template argument vector for the call to
     unify.  If we used TARGS, we'd clutter it up with the result of
     the attempted unification, even if this class didn't work out.
     We also don't want to commit ourselves to all the unifications
     we've already done, since unification is supposed to be done on
     an argument-by-argument basis.  In other words, consider the
     following pathological case:

       template <int I, int J, int K>
       struct S {};

       template <int I, int J>
       struct S<I, J, 2> : public S<I, I, I>, S<J, J, J> {};

       template <int I, int J, int K>
       void f(S<I, J, K>, S<I, I, I>);

       void g() {
	 S<0, 0, 0> s0;
	 S<0, 1, 2> s2;

	 f(s0, s2);
       }

     Now, by the time we consider the unification involving `s2', we
     already know that we must have `f<0, 0, 0>'.  But, even though
     `S<0, 1, 2>' is derived from `S<0, 0, 0>', the code is invalid
     because there are two ways to unify base classes of S<0, 1, 2>
     with S<I, I, I>.  If we kept the already deduced knowledge, we
     would reject the possibility I=1.  */
  copy_of_targs = make_tree_vec (TREE_VEC_LENGTH (targs));

  /* If unification failed, we're done.  */
  if (unify (tparms, copy_of_targs, CLASSTYPE_TI_ARGS (parm),
	     CLASSTYPE_TI_ARGS (arg), UNIFY_ALLOW_NONE))
    return NULL_TREE;

  return arg;
}