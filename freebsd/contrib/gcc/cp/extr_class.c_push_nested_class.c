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
 scalar_t__ BOUND_TEMPLATE_TEMPLATE_PARM ; 
 scalar_t__ CLASS_TYPE_P (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_AGGR_TYPE (scalar_t__) ; 
 scalar_t__ NAMESPACE_DECL ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TEMPLATE_TYPE_PARM ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MAIN_DECL (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  pushclass (scalar_t__) ; 

void
push_nested_class (tree type)
{
  tree context;

  /* A namespace might be passed in error cases, like A::B:C.  */
  if (type == NULL_TREE
      || type == error_mark_node
      || TREE_CODE (type) == NAMESPACE_DECL
      || ! IS_AGGR_TYPE (type)
      || TREE_CODE (type) == TEMPLATE_TYPE_PARM
      || TREE_CODE (type) == BOUND_TEMPLATE_TEMPLATE_PARM)
    return;

  context = DECL_CONTEXT (TYPE_MAIN_DECL (type));

  if (context && CLASS_TYPE_P (context))
    push_nested_class (context);
  pushclass (type);
}