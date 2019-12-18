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
#define  BOOLEAN_TYPE 137 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
#define  ENUMERAL_TYPE 136 
#define  ERROR_MARK 135 
#define  IDENTIFIER_NODE 134 
#define  INTEGER_TYPE 133 
#define  REAL_TYPE 132 
#define  RECORD_TYPE 131 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
#define  TYPE_DECL 130 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_NAME (int /*<<< orphan*/ ) ; 
 int TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 129 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  c_common_type_for_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  pp_c_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_c_tree_decl_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_decimal_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pp_id_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pp_c_type_specifier (c_pretty_printer *pp, tree t)
{
  const enum tree_code code = TREE_CODE (t);
  switch (code)
    {
    case ERROR_MARK:
      pp_c_identifier (pp, "<type-error>");
      break;

    case IDENTIFIER_NODE:
      pp_c_tree_decl_identifier (pp, t);
      break;

    case VOID_TYPE:
    case BOOLEAN_TYPE:
    case INTEGER_TYPE:
    case REAL_TYPE:
      if (TYPE_NAME (t))
	{
	  t = TYPE_NAME (t);
	  pp_c_type_specifier (pp, t);
	}
      else
	{
	  int prec = TYPE_PRECISION (t);
	  t = c_common_type_for_mode (TYPE_MODE (t), TYPE_UNSIGNED (t));
	  if (TYPE_NAME (t))
	    {
	      pp_c_type_specifier (pp, t);
	      if (TYPE_PRECISION (t) != prec)
		{
		  pp_string (pp, ":");
		  pp_decimal_int (pp, prec);
		}
	    }
	  else
	    {
	      switch (code)
		{
		case INTEGER_TYPE:
		  pp_string (pp, (TYPE_UNSIGNED (t)
				  ? "<unnamed-unsigned:"
				  : "<unnamed-signed:"));
		  break;
		case REAL_TYPE:
		  pp_string (pp, "<unnamed-float:");
		  break;
		default:
		  gcc_unreachable ();
		}
	      pp_decimal_int (pp, prec);
	      pp_string (pp, ">");
	    }
	}
      break;

    case TYPE_DECL:
      if (DECL_NAME (t))
	pp_id_expression (pp, t);
      else
	pp_c_identifier (pp, "<typedef-error>");
      break;

    case UNION_TYPE:
    case RECORD_TYPE:
    case ENUMERAL_TYPE:
      if (code == UNION_TYPE)
	pp_c_identifier (pp, "union");
      else if (code == RECORD_TYPE)
	pp_c_identifier (pp, "struct");
      else if (code == ENUMERAL_TYPE)
	pp_c_identifier (pp, "enum");
      else
	pp_c_identifier (pp, "<tag-error>");

      if (TYPE_NAME (t))
	pp_id_expression (pp, TYPE_NAME (t));
      else
	pp_c_identifier (pp, "<anonymous>");
      break;

    default:
      pp_unsupported_tree (pp, t);
      break;
    }
}