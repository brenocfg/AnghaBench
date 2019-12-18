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
typedef  int TREE_USED ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ lookup_label (scalar_t__) ; 
 scalar_t__ null_pointer_node ; 
 scalar_t__ pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 int /*<<< orphan*/  ptr_type_node ; 

tree
finish_label_address_expr (tree label)
{
  tree result;

  if (pedantic)
    pedwarn ("taking the address of a label is non-standard");

  if (label == error_mark_node)
    return error_mark_node;

  label = lookup_label (label);
  if (label == NULL_TREE)
    result = null_pointer_node;
  else
    {
      TREE_USED (label) = 1;
      result = build1 (ADDR_EXPR, ptr_type_node, label);
      /* The current function in not necessarily uninlinable.
	 Computed gotos are incompatible with inlining, but the value
	 here could be used only in a diagnostic, for example.  */
    }

  return result;
}