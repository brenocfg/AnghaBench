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
struct int_tree_map {unsigned int uid; int /*<<< orphan*/  to; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ htab_find_with_hash (int /*<<< orphan*/ ,struct int_tree_map*,unsigned int) ; 
 int /*<<< orphan*/  referenced_vars ; 

tree 
referenced_var_lookup (unsigned int uid)
{
  struct int_tree_map *h, in;
  in.uid = uid;
  h = (struct int_tree_map *) htab_find_with_hash (referenced_vars, &in, uid);
  gcc_assert (h || uid == 0);
  if (h)
    return h->to;
  return NULL_TREE;
}