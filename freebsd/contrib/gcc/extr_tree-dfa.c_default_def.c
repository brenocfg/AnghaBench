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
struct int_tree_map {int /*<<< orphan*/  to; int /*<<< orphan*/  uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  SSA_VAR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_defs ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 scalar_t__ htab_find_with_hash (int /*<<< orphan*/ ,struct int_tree_map*,int /*<<< orphan*/ ) ; 

tree 
default_def (tree var)
{
  struct int_tree_map *h, in;
  gcc_assert (SSA_VAR_P (var));
  in.uid = DECL_UID (var);
  h = (struct int_tree_map *) htab_find_with_hash (default_defs, &in,
                                                   DECL_UID (var));
  if (h)
    return h->to;
  return NULL_TREE;
}