#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* var_map ;
typedef  TYPE_2__* var_ann_t ;
typedef  scalar_t__ tree ;
struct TYPE_10__ {int /*<<< orphan*/  (* types_compatible_p ) (scalar_t__,scalar_t__) ;} ;
struct TYPE_9__ {scalar_t__ symbol_mem_tag; } ;
struct TYPE_8__ {int /*<<< orphan*/  var_partition; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DECL_FROM_INLINE (scalar_t__) ; 
 scalar_t__ DECL_IGNORED_P (scalar_t__) ; 
 int NO_PARTITION ; 
 scalar_t__ PARM_DECL ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ RESULT_DECL ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ SSA_NAME_OCCURS_IN_ABNORMAL_PHI (scalar_t__) ; 
 scalar_t__ SSA_NAME_VAR (scalar_t__) ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (scalar_t__) ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 scalar_t__ default_def (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ get_alias_set (scalar_t__) ; 
 TYPE_6__ lang_hooks ; 
 int partition_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ partition_to_var (TYPE_1__*,int) ; 
 int partition_union (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  register_ssa_partition (TYPE_1__*,scalar_t__,int) ; 
 int /*<<< orphan*/  replace_ssa_name_symbol (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__) ; 
 TYPE_2__* var_ann (scalar_t__) ; 

__attribute__((used)) static void
copy_rename_partition_coalesce (var_map map, tree var1, tree var2, FILE *debug)
{
  int p1, p2, p3;
  tree root1, root2;
  tree rep1, rep2;
  var_ann_t ann1, ann2, ann3;
  bool ign1, ign2, abnorm;

  gcc_assert (TREE_CODE (var1) == SSA_NAME);
  gcc_assert (TREE_CODE (var2) == SSA_NAME);

  register_ssa_partition (map, var1, false);
  register_ssa_partition (map, var2, true);

  p1 = partition_find (map->var_partition, SSA_NAME_VERSION (var1));
  p2 = partition_find (map->var_partition, SSA_NAME_VERSION (var2));

  if (debug)
    {
      fprintf (debug, "Try : ");
      print_generic_expr (debug, var1, TDF_SLIM);
      fprintf (debug, "(P%d) & ", p1);
      print_generic_expr (debug, var2, TDF_SLIM);
      fprintf (debug, "(P%d)", p2);
    }

  gcc_assert (p1 != NO_PARTITION);
  gcc_assert (p2 != NO_PARTITION);

  rep1 = partition_to_var (map, p1);
  rep2 = partition_to_var (map, p2);
  root1 = SSA_NAME_VAR (rep1);
  root2 = SSA_NAME_VAR (rep2);

  ann1 = var_ann (root1);
  ann2 = var_ann (root2);

  if (p1 == p2)
    {
      if (debug)
	fprintf (debug, " : Already coalesced.\n");
      return;
    }

  /* Don't coalesce if one of the variables occurs in an abnormal PHI.  */
  abnorm = (SSA_NAME_OCCURS_IN_ABNORMAL_PHI (rep1)
	    || SSA_NAME_OCCURS_IN_ABNORMAL_PHI (rep2));
  if (abnorm)
    {
      if (debug)
	fprintf (debug, " : Abnormal PHI barrier.  No coalesce.\n");
      return;
    }

  /* Partitions already have the same root, simply merge them.  */
  if (root1 == root2)
    {
      p1 = partition_union (map->var_partition, p1, p2);
      if (debug)
	fprintf (debug, " : Same root, coalesced --> P%d.\n", p1);
      return;
    }

  /* Never attempt to coalesce 2 difference parameters.  */
  if (TREE_CODE (root1) == PARM_DECL && TREE_CODE (root2) == PARM_DECL)
    {
      if (debug)
        fprintf (debug, " : 2 different PARM_DECLS. No coalesce.\n");
      return;
    }

  if ((TREE_CODE (root1) == RESULT_DECL) != (TREE_CODE (root2) == RESULT_DECL))
    {
      if (debug)
        fprintf (debug, " : One root a RESULT_DECL. No coalesce.\n");
      return;
    }

  ign1 = TREE_CODE (root1) == VAR_DECL && DECL_IGNORED_P (root1);
  ign2 = TREE_CODE (root2) == VAR_DECL && DECL_IGNORED_P (root2);

  /* Never attempt to coalesce 2 user variables unless one is an inline 
     variable.  */
  if (!ign1 && !ign2)
    {
      if (DECL_FROM_INLINE (root2))
        ign2 = true;
      else if (DECL_FROM_INLINE (root1))
	ign1 = true;
      else 
	{
	  if (debug)
	    fprintf (debug, " : 2 different USER vars. No coalesce.\n");
	  return;
	}
    }

  /* Don't coalesce if there are two different memory tags.  */
  if (ann1->symbol_mem_tag
      && ann2->symbol_mem_tag
      && ann1->symbol_mem_tag != ann2->symbol_mem_tag)
    {
      if (debug)
	fprintf (debug, " : 2 memory tags. No coalesce.\n");
      return;
    }

  /* If both values have default defs, we can't coalesce.  If only one has a 
     tag, make sure that variable is the new root partition.  */
  if (default_def (root1))
    {
      if (default_def (root2))
	{
	  if (debug)
	    fprintf (debug, " : 2 default defs. No coalesce.\n");
	  return;
	}
      else
        {
	  ign2 = true;
	  ign1 = false;
	}
    }
  else if (default_def (root2))
    {
      ign1 = true;
      ign2 = false;
    }

  /* Don't coalesce if the two variables aren't type compatible.  */
  if (!lang_hooks.types_compatible_p (TREE_TYPE (root1), TREE_TYPE (root2)))
    {
      if (debug)
	fprintf (debug, " : Incompatible types.  No coalesce.\n");
      return;
    }

  /* Don't coalesce if the aliasing sets of the types are different.  */
  if (POINTER_TYPE_P (TREE_TYPE (root1))
      && POINTER_TYPE_P (TREE_TYPE (root2))
      && get_alias_set (TREE_TYPE (TREE_TYPE (root1)))
          != get_alias_set (TREE_TYPE (TREE_TYPE (root2))))
    {
      if (debug)
	fprintf (debug, " : 2 different aliasing sets. No coalesce.\n");
      return;
    }


  /* Merge the two partitions.  */
  p3 = partition_union (map->var_partition, p1, p2);

  /* Set the root variable of the partition to the better choice, if there is 
     one.  */
  if (!ign2)
    replace_ssa_name_symbol (partition_to_var (map, p3), root2);
  else if (!ign1)
    replace_ssa_name_symbol (partition_to_var (map, p3), root1);

  /* Update the various flag widgitry of the current base representative.  */
  ann3 = var_ann (SSA_NAME_VAR (partition_to_var (map, p3)));
  if (ann1->symbol_mem_tag)
    ann3->symbol_mem_tag = ann1->symbol_mem_tag;
  else
    ann3->symbol_mem_tag = ann2->symbol_mem_tag;

  if (debug)
    {
      fprintf (debug, " --> P%d ", p3);
      print_generic_expr (debug, SSA_NAME_VAR (partition_to_var (map, p3)), 
			  TDF_SLIM);
      fprintf (debug, "\n");
    }
}