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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
#define  ARRAY_TYPE 134 
#define  BLOCK_POINTER_TYPE 133 
#define  COMPLEX_TYPE 132 
#define  FUNCTION_TYPE 131 
#define  POINTER_TYPE 130 
#define  REFERENCE_TYPE 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  VECTOR_TYPE 128 
 int /*<<< orphan*/  c_dialect_cxx () ; 
 int /*<<< orphan*/  flag_isoc99 ; 
 int /*<<< orphan*/  pp_c_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_c_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_type_qualifier_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_whitespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_ptr_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_simple_type_specifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_pointer_operator (int /*<<< orphan*/ ) ; 

void
pp_c_specifier_qualifier_list (c_pretty_printer *pp, tree t)
{
  const enum tree_code code = TREE_CODE (t);

  if (TREE_CODE (t) != POINTER_TYPE)
    pp_c_type_qualifier_list (pp, t);
  switch (code)
    {
    case REFERENCE_TYPE:
    case POINTER_TYPE:
    /* APPLE LOCAL blocks */
    case BLOCK_POINTER_TYPE:
      {
	/* Get the types-specifier of this type.  */
	tree pointee = strip_pointer_operator (TREE_TYPE (t));
	pp_c_specifier_qualifier_list (pp, pointee);
	if (TREE_CODE (pointee) == ARRAY_TYPE
	    || TREE_CODE (pointee) == FUNCTION_TYPE)
	  {
	    pp_c_whitespace (pp);
	    pp_c_left_paren (pp);
	  }
	else if (!c_dialect_cxx ())
	  pp_c_whitespace (pp);
	pp_ptr_operator (pp, t);
      }
      break;

    case FUNCTION_TYPE:
    case ARRAY_TYPE:
      pp_c_specifier_qualifier_list (pp, TREE_TYPE (t));
      break;

    case VECTOR_TYPE:
    case COMPLEX_TYPE:
      pp_c_specifier_qualifier_list (pp, TREE_TYPE (t));
      if (code == COMPLEX_TYPE)
	pp_c_identifier (pp, flag_isoc99 ? "_Complex" : "__complex__");
      else if (code == VECTOR_TYPE)
	pp_c_identifier (pp, "__vector__");
      break;

    default:
      pp_simple_type_specifier (pp, t);
      break;
    }
}