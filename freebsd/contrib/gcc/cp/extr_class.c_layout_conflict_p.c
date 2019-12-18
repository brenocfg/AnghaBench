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
typedef  TYPE_1__* splay_tree_node ;
typedef  int /*<<< orphan*/  splay_tree ;
struct TYPE_3__ {scalar_t__ key; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_subobject_offset ; 
 TYPE_1__* splay_tree_max (int /*<<< orphan*/ ) ; 
 int walk_subobject_offsets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
layout_conflict_p (tree type,
		   tree offset,
		   splay_tree offsets,
		   int vbases_p)
{
  splay_tree_node max_node;

  /* Get the node in OFFSETS that indicates the maximum offset where
     an empty subobject is located.  */
  max_node = splay_tree_max (offsets);
  /* If there aren't any empty subobjects, then there's no point in
     performing this check.  */
  if (!max_node)
    return 0;

  return walk_subobject_offsets (type, check_subobject_offset, offset,
				 offsets, (tree) (max_node->key),
				 vbases_p);
}