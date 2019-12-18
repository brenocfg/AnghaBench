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
#define  ARRAY_TYPE 131 
#define  FUNCTION_TYPE 130 
#define  RECORD_TYPE 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 128 
 int /*<<< orphan*/  c_common_truthvalue_conversion (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

tree
c_objc_common_truthvalue_conversion (tree expr)
{
  switch (TREE_CODE (TREE_TYPE (expr)))
    {
    case ARRAY_TYPE:
      error ("used array that cannot be converted to pointer where scalar is required");
      return error_mark_node;

    case RECORD_TYPE:
      error ("used struct type value where scalar is required");
      return error_mark_node;

    case UNION_TYPE:
      error ("used union type value where scalar is required");
      return error_mark_node;

    case FUNCTION_TYPE:
      gcc_unreachable ();

    default:
      break;
    }

  /* ??? Should we also give an error for void and vectors rather than
     leaving those to give errors later?  */
  return c_common_truthvalue_conversion (expr);
}