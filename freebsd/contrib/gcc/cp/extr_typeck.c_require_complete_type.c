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
 scalar_t__ OVERLOAD ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ complete_type_or_else (scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ processing_template_decl ; 
 scalar_t__ unknown_type_node ; 

tree
require_complete_type (tree value)
{
  tree type;

  if (processing_template_decl || value == error_mark_node)
    return value;

  if (TREE_CODE (value) == OVERLOAD)
    type = unknown_type_node;
  else
    type = TREE_TYPE (value);

  if (type == error_mark_node)
    return error_mark_node;

  /* First, detect a valid value with a complete type.  */
  if (COMPLETE_TYPE_P (type))
    return value;

  if (complete_type_or_else (type, value))
    return value;
  else
    return error_mark_node;
}