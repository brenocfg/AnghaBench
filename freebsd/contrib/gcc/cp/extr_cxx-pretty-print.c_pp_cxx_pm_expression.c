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
#define  DOTSTAR_EXPR 130 
#define  MEMBER_REF 129 
#define  OFFSET_REF 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_cast_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_dot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_qualified_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_star (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pp_cxx_pm_expression (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
      /* Handle unfortunate OFFESET_REF overloading here.  */
    case OFFSET_REF:
      if (TYPE_P (TREE_OPERAND (t, 0)))
	{
	  pp_cxx_qualified_id (pp, t);
	  break;
	}
      /* Else fall through.  */
    case MEMBER_REF:
    case DOTSTAR_EXPR:
      pp_cxx_pm_expression (pp, TREE_OPERAND (t, 0));
      pp_cxx_dot (pp);
      pp_star(pp);
      pp_cxx_cast_expression (pp, TREE_OPERAND (t, 1));
      break;


    default:
      pp_cxx_cast_expression (pp, t);
      break;
    }
}