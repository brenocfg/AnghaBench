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
struct TYPE_2__ {scalar_t__ names_used; int /*<<< orphan*/  access; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  current_access_specifier ; 
 size_t current_class_depth ; 
 int /*<<< orphan*/  current_class_name ; 
 TYPE_1__* current_class_stack ; 
 int /*<<< orphan*/  current_class_type ; 
 int /*<<< orphan*/  poplevel_class () ; 
 int /*<<< orphan*/  splay_tree_delete (scalar_t__) ; 

void
popclass (void)
{
  poplevel_class ();

  current_class_depth--;
  current_class_name = current_class_stack[current_class_depth].name;
  current_class_type = current_class_stack[current_class_depth].type;
  current_access_specifier = current_class_stack[current_class_depth].access;
  if (current_class_stack[current_class_depth].names_used)
    splay_tree_delete (current_class_stack[current_class_depth].names_used);
}