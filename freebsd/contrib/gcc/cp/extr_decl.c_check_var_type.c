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
 scalar_t__ IDENTIFIER_NODE ; 
 int /*<<< orphan*/  IDENTIFIER_OPNAME_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

tree
check_var_type (tree identifier, tree type)
{
  if (VOID_TYPE_P (type))
    {
      if (!identifier)
	error ("unnamed variable or field declared void");
      else if (TREE_CODE (identifier) == IDENTIFIER_NODE)
	{
	  gcc_assert (!IDENTIFIER_OPNAME_P (identifier));
	  error ("variable or field %qE declared void", identifier);
	}
      else
	error ("variable or field declared void");
      type = error_mark_node;
    }

  return type;
}