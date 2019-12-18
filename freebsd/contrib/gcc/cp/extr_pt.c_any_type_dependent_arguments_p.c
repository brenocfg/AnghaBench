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
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ type_dependent_expression_p (scalar_t__) ; 

bool
any_type_dependent_arguments_p (tree args)
{
  while (args)
    {
      tree arg = TREE_VALUE (args);

      if (type_dependent_expression_p (arg))
	return true;
      args = TREE_CHAIN (args);
    }
  return false;
}