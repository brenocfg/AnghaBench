#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * tree ;
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_MAIN_VARIANT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * discover_unique_type (int /*<<< orphan*/ *) ; 
 TYPE_1__* splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_to_canon_type ; 
 int /*<<< orphan*/  type_to_consider (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree 
get_canon_type (tree type, bool see_thru_ptrs, bool see_thru_arrays)
{
  splay_tree_node result;
  /* Strip the *'s off.  */
  if (!type || !type_to_consider (type))
    return NULL;

  type = TYPE_MAIN_VARIANT (type);
  if (see_thru_arrays) 
    while (POINTER_TYPE_P (type) || TREE_CODE (type) == ARRAY_TYPE)
      type = TYPE_MAIN_VARIANT (TREE_TYPE (type));

  else if (see_thru_ptrs) 
    while (POINTER_TYPE_P (type))
	type = TYPE_MAIN_VARIANT (TREE_TYPE (type));

  result = splay_tree_lookup(type_to_canon_type, (splay_tree_key) type);
  
  if (result == NULL)
    return discover_unique_type (type);
  else return (tree) result->value;
}