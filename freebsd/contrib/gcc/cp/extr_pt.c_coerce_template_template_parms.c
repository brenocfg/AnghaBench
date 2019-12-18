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
typedef  int /*<<< orphan*/  tsubst_flags_t ;
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ DECL_INNERMOST_TEMPLATE_PARMS (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
#define  PARM_DECL 130 
#define  TEMPLATE_DECL 129 
 int TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int TREE_VEC ; 
 scalar_t__ TREE_VEC_ELT (scalar_t__,int) ; 
 int TREE_VEC_LENGTH (scalar_t__) ; 
#define  TYPE_DECL 128 
 int /*<<< orphan*/  dependent_type_p (int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsubst (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
coerce_template_template_parms (tree parm_parms,
				tree arg_parms,
				tsubst_flags_t complain,
				tree in_decl,
				tree outer_args)
{
  int nparms, nargs, i;
  tree parm, arg;

  gcc_assert (TREE_CODE (parm_parms) == TREE_VEC);
  gcc_assert (TREE_CODE (arg_parms) == TREE_VEC);

  nparms = TREE_VEC_LENGTH (parm_parms);
  nargs = TREE_VEC_LENGTH (arg_parms);

  if (nargs != nparms)
    return 0;

  for (i = 0; i < nparms; ++i)
    {
      if (TREE_VEC_ELT (parm_parms, i) == error_mark_node
          || TREE_VEC_ELT (arg_parms, i) == error_mark_node)
        continue;

      parm = TREE_VALUE (TREE_VEC_ELT (parm_parms, i));
      arg = TREE_VALUE (TREE_VEC_ELT (arg_parms, i));

      if (arg == NULL_TREE || arg == error_mark_node
	  || parm == NULL_TREE || parm == error_mark_node)
	return 0;

      if (TREE_CODE (arg) != TREE_CODE (parm))
	return 0;

      switch (TREE_CODE (parm))
	{
	case TYPE_DECL:
	  break;

	case TEMPLATE_DECL:
	  /* We encounter instantiations of templates like
	       template <template <template <class> class> class TT>
	       class C;  */
	  {
	    tree parmparm = DECL_INNERMOST_TEMPLATE_PARMS (parm);
	    tree argparm = DECL_INNERMOST_TEMPLATE_PARMS (arg);

	    if (!coerce_template_template_parms
		(parmparm, argparm, complain, in_decl, outer_args))
	      return 0;
	  }
	  break;

	case PARM_DECL:
	  /* The tsubst call is used to handle cases such as

	       template <int> class C {};
	       template <class T, template <T> class TT> class D {};
	       D<int, C> d;

	     i.e. the parameter list of TT depends on earlier parameters.  */
	  if (!dependent_type_p (TREE_TYPE (arg))
	      && !same_type_p
		    (tsubst (TREE_TYPE (parm), outer_args, complain, in_decl),
			     TREE_TYPE (arg)))
	    return 0;
	  break;

	default:
	  gcc_unreachable ();
	}
    }
  return 1;
}