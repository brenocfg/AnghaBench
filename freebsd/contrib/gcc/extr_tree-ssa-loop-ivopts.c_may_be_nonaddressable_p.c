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
 int /*<<< orphan*/  AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
#define  ARRAY_RANGE_REF 131 
#define  ARRAY_REF 130 
#define  COMPONENT_REF 129 
 int /*<<< orphan*/  DECL_NONADDRESSABLE_P (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  VIEW_CONVERT_EXPR 128 

__attribute__((used)) static bool
may_be_nonaddressable_p (tree expr)
{
  switch (TREE_CODE (expr))
    {
    case COMPONENT_REF:
      return DECL_NONADDRESSABLE_P (TREE_OPERAND (expr, 1))
	     || may_be_nonaddressable_p (TREE_OPERAND (expr, 0));

    case ARRAY_REF:
    case ARRAY_RANGE_REF:
      return may_be_nonaddressable_p (TREE_OPERAND (expr, 0));

    case VIEW_CONVERT_EXPR:
      /* This kind of view-conversions may wrap non-addressable objects
	 and make them look addressable.  After some processing the
	 non-addressability may be uncovered again, causing ADDR_EXPRs
	 of inappropriate objects to be built.  */
      return AGGREGATE_TYPE_P (TREE_TYPE (expr))
	     && !AGGREGATE_TYPE_P (TREE_TYPE (TREE_OPERAND (expr, 0)));

    default:
      break;
    }

  return false;
}