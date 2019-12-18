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
typedef  int /*<<< orphan*/  (* walk_use_def_chains_fn ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
typedef  int /*<<< orphan*/  tree ;
struct pointer_set_t {int dummy; } ;

/* Variables and functions */
 scalar_t__ PHI_NODE ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 struct pointer_set_t* pointer_set_create () ; 
 int /*<<< orphan*/  pointer_set_destroy (struct pointer_set_t*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  walk_use_def_chains_1 (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*),void*,struct pointer_set_t*,int) ; 

void
walk_use_def_chains (tree var, walk_use_def_chains_fn fn, void *data,
                     bool is_dfs)
{
  tree def_stmt;

  gcc_assert (TREE_CODE (var) == SSA_NAME);

  def_stmt = SSA_NAME_DEF_STMT (var);

  /* We only need to recurse if the reaching definition comes from a PHI
     node.  */
  if (TREE_CODE (def_stmt) != PHI_NODE)
    (*fn) (var, def_stmt, data);
  else
    {
      struct pointer_set_t *visited = pointer_set_create ();
      walk_use_def_chains_1 (var, fn, data, visited, is_dfs);
      pointer_set_destroy (visited);
    }
}