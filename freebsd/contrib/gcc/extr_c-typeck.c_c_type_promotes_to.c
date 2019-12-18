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
 scalar_t__ TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 scalar_t__ c_promoting_integer_type_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_type_node ; 
 scalar_t__ float_type_node ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  unsigned_type_node ; 

tree
c_type_promotes_to (tree type)
{
  if (TYPE_MAIN_VARIANT (type) == float_type_node)
    return double_type_node;

  if (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      if (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_node)))
	return unsigned_type_node;
      return integer_type_node;
    }

  return type;
}