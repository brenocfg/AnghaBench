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
 scalar_t__ CLASSTYPE_NON_POD_P (scalar_t__) ; 
 int /*<<< orphan*/  CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ FLOAT_TYPE_P (scalar_t__) ; 
 scalar_t__ INTEGRAL_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TYPE_PTR_P (scalar_t__) ; 
 scalar_t__ TYPE_PTR_TO_MEMBER_P (scalar_t__) ; 
 scalar_t__ VECTOR_TYPE ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ strip_array_types (scalar_t__) ; 

int
pod_type_p (tree t)
{
  t = strip_array_types (t);

  if (t == error_mark_node)
    return 1;
  if (INTEGRAL_TYPE_P (t))
    return 1;  /* integral, character or enumeral type */
  if (FLOAT_TYPE_P (t))
    return 1;
  if (TYPE_PTR_P (t))
    return 1; /* pointer to non-member */
  if (TYPE_PTR_TO_MEMBER_P (t))
    return 1; /* pointer to member */

  if (TREE_CODE (t) == VECTOR_TYPE)
    return 1; /* vectors are (small) arrays of scalars */

  if (! CLASS_TYPE_P (t))
    return 0; /* other non-class type (reference or function) */
  if (CLASSTYPE_NON_POD_P (t))
    return 0;
  return 1;
}