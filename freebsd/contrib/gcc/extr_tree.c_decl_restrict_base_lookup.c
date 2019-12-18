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
struct tree_map {int /*<<< orphan*/  to; int /*<<< orphan*/  from; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 struct tree_map* htab_find_with_hash (int /*<<< orphan*/ ,struct tree_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  restrict_base_for_decl ; 

tree
decl_restrict_base_lookup (tree from)
{
  struct tree_map *h;
  struct tree_map in;

  in.from = from;
  h = htab_find_with_hash (restrict_base_for_decl, &in,
			   htab_hash_pointer (from));
  return h ? h->to : NULL_TREE;
}