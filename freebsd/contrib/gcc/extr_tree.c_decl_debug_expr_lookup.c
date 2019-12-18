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
 int /*<<< orphan*/  debug_expr_for_decl ; 
 struct tree_map* htab_find_with_hash (int /*<<< orphan*/ ,struct tree_map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htab_hash_pointer (int /*<<< orphan*/ ) ; 

tree 
decl_debug_expr_lookup (tree from)
{
  struct tree_map *h, in;
  in.from = from;

  h = htab_find_with_hash (debug_expr_for_decl, &in, htab_hash_pointer (from));
  if (h)
    return h->to;
  return NULL_TREE;
}