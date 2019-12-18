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
 scalar_t__ COMPLETE_TYPE_P (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  c_incomplete_type_error (scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 

tree
require_complete_type (tree value)
{
  tree type = TREE_TYPE (value);

  if (value == error_mark_node || type == error_mark_node)
    return error_mark_node;

  /* First, detect a valid value with a complete type.  */
  if (COMPLETE_TYPE_P (type))
    return value;

  c_incomplete_type_error (value, type);
  return error_mark_node;
}