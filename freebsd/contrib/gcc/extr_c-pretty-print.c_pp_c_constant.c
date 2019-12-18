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
 int ENUMERAL_TYPE ; 
#define  INTEGER_CST 130 
#define  REAL_CST 129 
#define  STRING_CST 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  char_type_node ; 
 int /*<<< orphan*/  pp_c_bool_constant (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_character_constant (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_enumeration_constant (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_floating_constant (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_integer_constant (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_string_literal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pp_c_constant (c_pretty_printer *pp, tree e)
{
  const enum tree_code code = TREE_CODE (e);

  switch (code)
    {
    case INTEGER_CST:
      {
	tree type = TREE_TYPE (e);
	if (type == boolean_type_node)
	  pp_c_bool_constant (pp, e);
	else if (type == char_type_node)
	  pp_c_character_constant (pp, e);
	else if (TREE_CODE (type) == ENUMERAL_TYPE
		 && pp_c_enumeration_constant (pp, e))
	  ;
	else
	  pp_c_integer_constant (pp, e);
      }
      break;

    case REAL_CST:
      pp_c_floating_constant (pp, e);
      break;

    case STRING_CST:
      pp_c_string_literal (pp, e);
      break;

    default:
      pp_unsupported_tree (pp, e);
      break;
    }
}