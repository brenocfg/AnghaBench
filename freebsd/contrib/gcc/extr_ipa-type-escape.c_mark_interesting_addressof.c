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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  splay_tree_value ;
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree_key ;
typedef  scalar_t__ bitmap ;
struct TYPE_3__ {scalar_t__ value; } ;

/* Variables and functions */
 scalar_t__ BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int TYPE_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_canon_type (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ipa_obstack ; 
 scalar_t__ ipa_type_escape_star_count_of_interesting_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  splay_tree_insert (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* splay_tree_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uid_to_addressof_down_map ; 
 int /*<<< orphan*/  uid_to_addressof_up_map ; 

__attribute__((used)) static void
mark_interesting_addressof (tree to_type, tree from_type)
{
  int from_uid;
  int to_uid;
  bitmap type_map;
  splay_tree_node result; 

  from_type = get_canon_type (from_type, false, false);
  to_type = get_canon_type (to_type, false, false);
  
  if (!from_type || !to_type)
    return;

  from_uid = TYPE_UID (from_type);
  to_uid = TYPE_UID (to_type);

  gcc_assert (ipa_type_escape_star_count_of_interesting_type (from_type) == 0);
  
  /* Process the Y into X map pointer.  */
  result = splay_tree_lookup (uid_to_addressof_down_map, 
			      (splay_tree_key) from_uid);
  
  if (result) 
    type_map = (bitmap) result->value;  
  else 
    {
      type_map = BITMAP_ALLOC (&ipa_obstack);
      splay_tree_insert (uid_to_addressof_down_map,
			 from_uid, 
			 (splay_tree_value)type_map);
    }
  bitmap_set_bit (type_map, TYPE_UID (to_type));
  
  /* Process the X into Y reverse map pointer.  */
  result = 
    splay_tree_lookup (uid_to_addressof_up_map, (splay_tree_key) to_uid);
  
  if (result) 
    type_map = (bitmap) result->value;  
  else 
    {
      type_map = BITMAP_ALLOC (&ipa_obstack);
      splay_tree_insert (uid_to_addressof_up_map,
			 to_uid, 
			 (splay_tree_value)type_map);
    }
  bitmap_set_bit (type_map, TYPE_UID (to_type));
}