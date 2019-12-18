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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_HASH (int /*<<< orphan*/ *) ; 
 scalar_t__ htab_find_slot_with_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lang_eh_runtime_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tree_cons (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  type_to_runtime_map ; 

__attribute__((used)) static void
add_type_for_runtime (tree type)
{
  tree *slot;

  slot = (tree *) htab_find_slot_with_hash (type_to_runtime_map, type,
					    TREE_HASH (type), INSERT);
  if (*slot == NULL)
    {
      tree runtime = (*lang_eh_runtime_type) (type);
      *slot = tree_cons (type, runtime, NULL_TREE);
    }
}