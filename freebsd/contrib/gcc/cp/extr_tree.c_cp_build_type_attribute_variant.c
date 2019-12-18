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
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_RAISES_EXCEPTIONS (scalar_t__) ; 
 scalar_t__ build_exception_variant (scalar_t__,scalar_t__) ; 
 scalar_t__ build_type_attribute_variant (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

tree
cp_build_type_attribute_variant (tree type, tree attributes)
{
  tree new_type;

  new_type = build_type_attribute_variant (type, attributes);
  if (TREE_CODE (new_type) == FUNCTION_TYPE
      && (TYPE_RAISES_EXCEPTIONS (new_type)
	  != TYPE_RAISES_EXCEPTIONS (type)))
    new_type = build_exception_variant (new_type,
					TYPE_RAISES_EXCEPTIONS (type));

  /* Making a new main variant of a class type is broken.  */
  gcc_assert (!CLASS_TYPE_P (type) || new_type == type);
    
  return new_type;
}