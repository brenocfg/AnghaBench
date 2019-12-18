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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  splay_tree ;

/* Variables and functions */
 int /*<<< orphan*/  BINFO_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  is_empty_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  record_subobject_offset ; 
 int /*<<< orphan*/  sizeof_biggest_empty_class ; 
 int /*<<< orphan*/  walk_subobject_offsets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
record_subobject_offsets (tree type,
			  tree offset,
			  splay_tree offsets,
			  bool is_data_member)
{
  tree max_offset;
  /* If recording subobjects for a non-static data member or a
     non-empty base class , we do not need to record offsets beyond
     the size of the biggest empty class.  Additional data members
     will go at the end of the class.  Additional base classes will go
     either at offset zero (if empty, in which case they cannot
     overlap with offsets past the size of the biggest empty class) or
     at the end of the class.

     However, if we are placing an empty base class, then we must record
     all offsets, as either the empty class is at offset zero (where
     other empty classes might later be placed) or at the end of the
     class (where other objects might then be placed, so other empty
     subobjects might later overlap).  */
  if (is_data_member
      || !is_empty_class (BINFO_TYPE (type)))
    max_offset = sizeof_biggest_empty_class;
  else
    max_offset = NULL_TREE;
  walk_subobject_offsets (type, record_subobject_offset, offset,
			  offsets, max_offset, is_data_member);
}