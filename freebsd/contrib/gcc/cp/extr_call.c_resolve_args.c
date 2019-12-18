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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ error_operand_p (scalar_t__) ; 
 scalar_t__ invalid_nonstatic_memfn_p (scalar_t__) ; 

__attribute__((used)) static tree
resolve_args (tree args)
{
  tree t;
  for (t = args; t; t = TREE_CHAIN (t))
    {
      tree arg = TREE_VALUE (t);

      if (error_operand_p (arg))
	return error_mark_node;
      else if (VOID_TYPE_P (TREE_TYPE (arg)))
	{
	  error ("invalid use of void expression");
	  return error_mark_node;
	}
      else if (invalid_nonstatic_memfn_p (arg))
	return error_mark_node;
    }
  return args;
}