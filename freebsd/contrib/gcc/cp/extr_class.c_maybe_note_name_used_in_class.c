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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  splay_tree_value ;
typedef  int /*<<< orphan*/  splay_tree_key ;
typedef  scalar_t__ splay_tree ;
struct TYPE_2__ {scalar_t__ names_used; } ;

/* Variables and functions */
 scalar_t__ TYPE_BEING_DEFINED (int /*<<< orphan*/ ) ; 
 int current_class_depth ; 
 TYPE_1__* current_class_stack ; 
 int /*<<< orphan*/  current_class_type ; 
 scalar_t__ innermost_scope_kind () ; 
 scalar_t__ lookup_member (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sk_class ; 
 int /*<<< orphan*/  splay_tree_compare_pointers ; 
 int /*<<< orphan*/  splay_tree_insert (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ splay_tree_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
maybe_note_name_used_in_class (tree name, tree decl)
{
  splay_tree names_used;

  /* If we're not defining a class, there's nothing to do.  */
  if (!(innermost_scope_kind() == sk_class
	&& TYPE_BEING_DEFINED (current_class_type)))
    return;

  /* If there's already a binding for this NAME, then we don't have
     anything to worry about.  */
  if (lookup_member (current_class_type, name,
		     /*protect=*/0, /*want_type=*/false))
    return;

  if (!current_class_stack[current_class_depth - 1].names_used)
    current_class_stack[current_class_depth - 1].names_used
      = splay_tree_new (splay_tree_compare_pointers, 0, 0);
  names_used = current_class_stack[current_class_depth - 1].names_used;

  splay_tree_insert (names_used,
		     (splay_tree_key) name,
		     (splay_tree_value) decl);
}