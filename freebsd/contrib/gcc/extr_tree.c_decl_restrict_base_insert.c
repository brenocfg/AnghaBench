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
typedef  void* tree ;
struct tree_map {int /*<<< orphan*/  hash; void* to; void* from; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSERT ; 
 struct tree_map* ggc_alloc (int) ; 
 void** htab_find_slot_with_hash (int /*<<< orphan*/ ,struct tree_map*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer (void*) ; 
 int /*<<< orphan*/  restrict_base_for_decl ; 

void
decl_restrict_base_insert (tree from, tree to)
{
  struct tree_map *h;
  void **loc;

  h = ggc_alloc (sizeof (struct tree_map));
  h->hash = htab_hash_pointer (from);
  h->from = from;
  h->to = to;
  loc = htab_find_slot_with_hash (restrict_base_for_decl, h, h->hash, INSERT);
  *(struct tree_map **) loc = h;
}