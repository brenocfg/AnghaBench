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
 int /*<<< orphan*/  COMPLETE_TYPE_P (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ complete_type (scalar_t__) ; 
 int /*<<< orphan*/  cxx_incomplete_type_diagnostic (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 

tree
complete_type_or_else (tree type, tree value)
{
  type = complete_type (type);
  if (type == error_mark_node)
    /* We already issued an error.  */
    return NULL_TREE;
  else if (!COMPLETE_TYPE_P (type))
    {
      cxx_incomplete_type_diagnostic (value, type, 0);
      return NULL_TREE;
    }
  else
    return type;
}