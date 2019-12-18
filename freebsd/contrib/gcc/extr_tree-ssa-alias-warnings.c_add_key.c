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
struct tree_map {int /*<<< orphan*/  from; int /*<<< orphan*/  hash; int /*<<< orphan*/  to; } ;
typedef  int /*<<< orphan*/  htab_t ;
typedef  int /*<<< orphan*/  alloc_pool ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  NULL_TREE ; 
 void** htab_find_slot (int /*<<< orphan*/ ,struct tree_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer (int /*<<< orphan*/ ) ; 
 struct tree_map* pool_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_key (htab_t ht, tree t, alloc_pool references_pool)
{
  void **slot;
  struct tree_map *tp = pool_alloc (references_pool);

  tp->from = t;
  tp->to = NULL_TREE;
  tp->hash = htab_hash_pointer(tp->from);

  slot = htab_find_slot (ht, tp, INSERT);
  *slot = (void *) tp;
}