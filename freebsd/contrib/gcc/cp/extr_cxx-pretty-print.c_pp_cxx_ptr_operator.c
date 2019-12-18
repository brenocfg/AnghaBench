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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
 int const ARRAY_TYPE ; 
#define  OFFSET_TYPE 131 
#define  POINTER_TYPE 130 
#define  RECORD_TYPE 129 
#define  REFERENCE_TYPE 128 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int const TYPE_DECL ; 
 int /*<<< orphan*/  TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_OBJECT_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_CLASS_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTR_TO_MEMBER_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_ampersand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_cv_qualifier_seq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_nested_name_specifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_star (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_cxx_ptr_operator (cxx_pretty_printer *pp, tree t)
{
  if (!TYPE_P (t) && TREE_CODE (t) != TYPE_DECL)
    t = TREE_TYPE (t);
  switch (TREE_CODE (t))
    {
    case REFERENCE_TYPE:
    case POINTER_TYPE:
      if (TREE_CODE (TREE_TYPE (t)) == POINTER_TYPE
	  || TYPE_PTR_TO_MEMBER_P (TREE_TYPE (t)))
	pp_cxx_ptr_operator (pp, TREE_TYPE (t));
      if (TREE_CODE (t) == POINTER_TYPE)
	{
	  pp_star (pp);
	  pp_cxx_cv_qualifier_seq (pp, t);
	}
      else
	pp_ampersand (pp);
      break;

    case RECORD_TYPE:
      if (TYPE_PTRMEMFUNC_P (t))
	{
	  pp_cxx_left_paren (pp);
	  pp_cxx_nested_name_specifier (pp, TYPE_PTRMEMFUNC_OBJECT_TYPE (t));
	  pp_star (pp);
	  break;
	}
    case OFFSET_TYPE:
      if (TYPE_PTR_TO_MEMBER_P (t))
	{
	  if (TREE_CODE (TREE_TYPE (t)) == ARRAY_TYPE)
	    pp_cxx_left_paren (pp);
	  pp_cxx_nested_name_specifier (pp, TYPE_PTRMEM_CLASS_TYPE (t));
	  pp_star (pp);
	  pp_cxx_cv_qualifier_seq (pp, t);
	  break;
	}
      /* else fall through.  */

    default:
      pp_unsupported_tree (pp, t);
      break;
    }
}