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
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_DOMAIN (scalar_t__) ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_MIN_VALUE (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ integer_zerop (scalar_t__) ; 

tree
array_type_nelts (tree type)
{
  tree index_type, min, max;

  /* If they did it with unspecified bounds, then we should have already
     given an error about it before we got here.  */
  if (! TYPE_DOMAIN (type))
    return error_mark_node;

  index_type = TYPE_DOMAIN (type);
  min = TYPE_MIN_VALUE (index_type);
  max = TYPE_MAX_VALUE (index_type);

  return (integer_zerop (min)
	  ? max
	  : fold_build2 (MINUS_EXPR, TREE_TYPE (max), max, min));
}