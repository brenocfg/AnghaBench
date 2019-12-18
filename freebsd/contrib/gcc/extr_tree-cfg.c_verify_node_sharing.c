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
typedef  int /*<<< orphan*/  htab_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 void** htab_find_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_node_can_be_shared (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
verify_node_sharing (tree * tp, int *walk_subtrees, void *data)
{
  htab_t htab = (htab_t) data;
  void **slot;

  if (tree_node_can_be_shared (*tp))
    {
      *walk_subtrees = false;
      return NULL;
    }

  slot = htab_find_slot (htab, *tp, INSERT);
  if (*slot)
    return (tree) *slot;
  *slot = *tp;

  return NULL;
}