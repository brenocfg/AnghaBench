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

/* Variables and functions */
 int /*<<< orphan*/  NO_INSERT ; 
 int /*<<< orphan*/  TREE_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ htab_find_slot_with_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_to_runtime_map ; 

__attribute__((used)) static tree
lookup_type_for_runtime (tree type)
{
  tree *slot;

  slot = (tree *) htab_find_slot_with_hash (type_to_runtime_map, type,
					    TREE_HASH (type), NO_INSERT);

  /* We should have always inserted the data earlier.  */
  return TREE_VALUE (*slot);
}