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
 scalar_t__ DECL_TEMPLATE_PARMS (scalar_t__) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_RESULT (scalar_t__) ; 
 scalar_t__ DECL_TEMPLATE_TEMPLATE_PARM_P (scalar_t__) ; 
#define  FUNCTION_TYPE 129 
 scalar_t__ INNERMOST_TEMPLATE_PARMS (scalar_t__) ; 
#define  METHOD_TYPE 128 
 int NEXT_CODE (scalar_t__) ; 
 int TFF_CLASS_KEY_OR_ENUM ; 
 int TFF_DECL_SPECIFIERS ; 
 int TFF_TEMPLATE_HEADER ; 
 int TFF_TEMPLATE_NAME ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VEC_ELT (scalar_t__,int) ; 
 int TREE_VEC_LENGTH (scalar_t__) ; 
 scalar_t__ TYPE_DECL ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_decl (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_function_decl (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_template_parameter (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ nreverse (scalar_t__) ; 
 int /*<<< orphan*/  pp_cxx_begin_template_argument_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_end_template_argument_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pp_cxx_whitespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_separate_with_comma (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_template_decl (tree t, int flags)
{
  tree orig_parms = DECL_TEMPLATE_PARMS (t);
  tree parms;
  int i;

  if (flags & TFF_TEMPLATE_HEADER)
    {
      for (parms = orig_parms = nreverse (orig_parms);
	   parms;
	   parms = TREE_CHAIN (parms))
	{
	  tree inner_parms = INNERMOST_TEMPLATE_PARMS (parms);
	  int len = TREE_VEC_LENGTH (inner_parms);

	  pp_cxx_identifier (cxx_pp, "template");
	  pp_cxx_begin_template_argument_list (cxx_pp);

	  /* If we've shown the template prefix, we'd better show the
	     parameters' and decl's type too.  */
	    flags |= TFF_DECL_SPECIFIERS;

	  for (i = 0; i < len; i++)
	    {
	      if (i)
		pp_separate_with_comma (cxx_pp);
	      dump_template_parameter (TREE_VEC_ELT (inner_parms, i), flags);
	    }
	  pp_cxx_end_template_argument_list (cxx_pp);
	  pp_cxx_whitespace (cxx_pp);
	}
      nreverse(orig_parms);

      if (DECL_TEMPLATE_TEMPLATE_PARM_P (t))
	/* Say `template<arg> class TT' not just `template<arg> TT'.  */
	pp_cxx_identifier (cxx_pp, "class");
    }

  if (TREE_CODE (DECL_TEMPLATE_RESULT (t)) == TYPE_DECL)
    dump_type (TREE_TYPE (t),
	       ((flags & ~TFF_CLASS_KEY_OR_ENUM) | TFF_TEMPLATE_NAME
		| (flags & TFF_DECL_SPECIFIERS ? TFF_CLASS_KEY_OR_ENUM : 0)));
  else if (TREE_CODE (DECL_TEMPLATE_RESULT (t)) == VAR_DECL)
    dump_decl (DECL_TEMPLATE_RESULT (t), flags | TFF_TEMPLATE_NAME);
  else
    {
      gcc_assert (TREE_TYPE (t));
      switch (NEXT_CODE (t))
	{
	case METHOD_TYPE:
	case FUNCTION_TYPE:
	  dump_function_decl (t, flags | TFF_TEMPLATE_NAME);
	  break;
	default:
	  /* This case can occur with some invalid code.  */
	  dump_type (TREE_TYPE (t),
		     (flags & ~TFF_CLASS_KEY_OR_ENUM) | TFF_TEMPLATE_NAME
		     | (flags & TFF_DECL_SPECIFIERS
			? TFF_CLASS_KEY_OR_ENUM : 0));
	}
    }
}