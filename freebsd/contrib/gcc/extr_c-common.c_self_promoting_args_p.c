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
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ c_promoting_integer_type_p (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ float_type_node ; 
 scalar_t__ void_type_node ; 

int
self_promoting_args_p (tree parms)
{
  tree t;
  for (t = parms; t; t = TREE_CHAIN (t))
    {
      tree type = TREE_VALUE (t);

      if (type == error_mark_node)
	continue;

      if (TREE_CHAIN (t) == 0 && type != void_type_node)
	return 0;

      if (type == 0)
	return 0;

      if (TYPE_MAIN_VARIANT (type) == float_type_node)
	return 0;

      if (c_promoting_integer_type_p (type))
	return 0;
    }
  return 1;
}