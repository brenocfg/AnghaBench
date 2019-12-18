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
typedef  int /*<<< orphan*/  c_pretty_printer ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
#define  ARRAY_TYPE 142 
#define  BLOCK_POINTER_TYPE 141 
#define  ENUMERAL_TYPE 140 
#define  FIELD_DECL 139 
#define  FUNCTION_DECL 138 
#define  FUNCTION_TYPE 137 
#define  INTEGER_TYPE 136 
#define  LABEL_DECL 135 
#define  PARM_DECL 134 
#define  POINTER_TYPE 133 
#define  REAL_TYPE 132 
#define  RECORD_TYPE 131 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  TYPE_DECL 130 
#define  UNION_TYPE 129 
#define  VAR_DECL 128 
 int /*<<< orphan*/  pp_abstract_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* pp_c_base (int /*<<< orphan*/ *) ; 
 int pp_c_flag_abstract ; 
 int /*<<< orphan*/  pp_c_space_for_pointer_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_tree_decl_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_parameter_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pp_c_direct_declarator (c_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
    case VAR_DECL:
    case PARM_DECL:
    case TYPE_DECL:
    case FIELD_DECL:
    case LABEL_DECL:
      pp_c_space_for_pointer_operator (pp, TREE_TYPE (t));
      pp_c_tree_decl_identifier (pp, t);
      break;

    case ARRAY_TYPE:
    case POINTER_TYPE:
    /* APPLE LOCAL blocks */
    case BLOCK_POINTER_TYPE:
      pp_abstract_declarator (pp, TREE_TYPE (t));
      break;

    case FUNCTION_TYPE:
      pp_parameter_list (pp, t);
      pp_abstract_declarator (pp, TREE_TYPE (t));
      break;

    case FUNCTION_DECL:
      pp_c_space_for_pointer_operator (pp, TREE_TYPE (TREE_TYPE (t)));
      pp_c_tree_decl_identifier (pp, t);
      if (pp_c_base (pp)->flags & pp_c_flag_abstract)
	pp_abstract_declarator (pp, TREE_TYPE (t));
      else
	{
	  pp_parameter_list (pp, t);
	  pp_abstract_declarator (pp, TREE_TYPE (TREE_TYPE (t)));
	}
      break;

    case INTEGER_TYPE:
    case REAL_TYPE:
    case ENUMERAL_TYPE:
    case UNION_TYPE:
    case RECORD_TYPE:
      break;

    default:
      pp_unsupported_tree (pp, t);
      break;
    }
}