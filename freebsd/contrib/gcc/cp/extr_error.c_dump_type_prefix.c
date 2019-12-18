#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {void* padding; } ;

/* Variables and functions */
#define  ARRAY_TYPE 154 
#define  BLOCK_POINTER_TYPE 153 
#define  BOOLEAN_TYPE 152 
#define  BOUND_TEMPLATE_TEMPLATE_PARM 151 
#define  COMPLEX_TYPE 150 
#define  ENUMERAL_TYPE 149 
#define  ERROR_MARK 148 
#define  FUNCTION_TYPE 147 
#define  IDENTIFIER_NODE 146 
#define  INTEGER_TYPE 145 
#define  METHOD_TYPE 144 
#define  OFFSET_TYPE 143 
#define  POINTER_TYPE 142 
#define  REAL_TYPE 141 
#define  RECORD_TYPE 140 
#define  REFERENCE_TYPE 139 
#define  TEMPLATE_TEMPLATE_PARM 138 
#define  TEMPLATE_TYPE_PARM 137 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
#define  TREE_LIST 136 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  TREE_VEC 135 
#define  TYPENAME_TYPE 134 
#define  TYPEOF_TYPE 133 
#define  TYPE_DECL 132 
 int /*<<< orphan*/  TYPE_METHOD_BASETYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_OFFSET_BASETYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_FN_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 131 
#define  UNKNOWN_TYPE 130 
#define  VECTOR_TYPE 129 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_aggr_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_type (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* pp_base (int /*<<< orphan*/ ) ; 
 void* pp_before ; 
 int /*<<< orphan*/  pp_character (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  pp_cxx_colon_colon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_cv_qualifier_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_left_paren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_star (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_whitespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_identifier (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pp_maybe_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_type_prefix (tree t, int flags)
{
  if (TYPE_PTRMEMFUNC_P (t))
    {
      t = TYPE_PTRMEMFUNC_FN_TYPE (t);
      goto offset_type;
    }

  switch (TREE_CODE (t))
    {
    case POINTER_TYPE:
      /* APPLE LOCAL blocks 6040305 */
    case BLOCK_POINTER_TYPE:
    case REFERENCE_TYPE:
      {
	tree sub = TREE_TYPE (t);

	dump_type_prefix (sub, flags);
	if (TREE_CODE (sub) == ARRAY_TYPE)
	  {
	    pp_cxx_whitespace (cxx_pp);
	    pp_cxx_left_paren (cxx_pp);
	  }
	/* APPLE LOCAL begin blocks 6040305 */
	pp_character (cxx_pp, "&*^"[(TREE_CODE (t) == POINTER_TYPE)
				    + (TREE_CODE (t) == BLOCK_POINTER_TYPE)*2]);
	/* APPLE LOCAL end blocks 6040305 */
	pp_base (cxx_pp)->padding = pp_before;
	pp_cxx_cv_qualifier_seq (cxx_pp, t);
      }
      break;

    case OFFSET_TYPE:
    offset_type:
      dump_type_prefix (TREE_TYPE (t), flags);
      if (TREE_CODE (t) == OFFSET_TYPE)	/* pmfs deal with this in d_t_p */
	{
	  pp_maybe_space (cxx_pp);
	  if (TREE_CODE (TREE_TYPE (t)) == ARRAY_TYPE)
	     pp_cxx_left_paren (cxx_pp);
	  dump_type (TYPE_OFFSET_BASETYPE (t), flags);
	  pp_cxx_colon_colon (cxx_pp);
	}
      pp_cxx_star (cxx_pp);
      pp_cxx_cv_qualifier_seq (cxx_pp, t);
      pp_base (cxx_pp)->padding = pp_before;
      break;

      /* Can only be reached through function pointer -- this would not be
	 correct if FUNCTION_DECLs used it.  */
    case FUNCTION_TYPE:
      dump_type_prefix (TREE_TYPE (t), flags);
      pp_maybe_space (cxx_pp);
      pp_cxx_left_paren (cxx_pp);
      break;

    case METHOD_TYPE:
      dump_type_prefix (TREE_TYPE (t), flags);
      pp_maybe_space (cxx_pp);
      pp_cxx_left_paren (cxx_pp);
      dump_aggr_type (TYPE_METHOD_BASETYPE (t), flags);
      pp_cxx_colon_colon (cxx_pp);
      break;

    case ARRAY_TYPE:
      dump_type_prefix (TREE_TYPE (t), flags);
      break;

    case ENUMERAL_TYPE:
    case IDENTIFIER_NODE:
    case INTEGER_TYPE:
    case BOOLEAN_TYPE:
    case REAL_TYPE:
    case RECORD_TYPE:
    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_TEMPLATE_PARM:
    case BOUND_TEMPLATE_TEMPLATE_PARM:
    case TREE_LIST:
    case TYPE_DECL:
    case TREE_VEC:
    case UNION_TYPE:
    case UNKNOWN_TYPE:
    case VOID_TYPE:
    case TYPENAME_TYPE:
    case COMPLEX_TYPE:
    case VECTOR_TYPE:
    case TYPEOF_TYPE:
      dump_type (t, flags);
      pp_base (cxx_pp)->padding = pp_before;
      break;

    default:
      pp_unsupported_tree (cxx_pp, t);
      /* fall through.  */
    case ERROR_MARK:
      pp_identifier (cxx_pp, "<typeprefixerror>");
      break;
    }
}