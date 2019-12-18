#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct TYPE_2__ {int /*<<< orphan*/  type; scalar_t__ hidden; } ;

/* Variables and functions */
 scalar_t__ DERIVED_FROM_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int current_class_depth ; 
 TYPE_1__* current_class_stack ; 
 int /*<<< orphan*/  current_class_type ; 
 scalar_t__ dependent_type_p (int /*<<< orphan*/ ) ; 

tree
currently_open_derived_class (tree t)
{
  int i;

  /* The bases of a dependent type are unknown.  */
  if (dependent_type_p (t))
    return NULL_TREE;

  if (!current_class_type)
    return NULL_TREE;

  if (DERIVED_FROM_P (t, current_class_type))
    return current_class_type;

  for (i = current_class_depth - 1; i > 0; --i)
    {
      if (current_class_stack[i].hidden)
	break;
      if (DERIVED_FROM_P (t, current_class_stack[i].type))
	return current_class_stack[i].type;
    }

  return NULL_TREE;
}