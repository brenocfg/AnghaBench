#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  var_map ;
typedef  TYPE_1__* var_ann_t ;
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  root_var_p ;
struct TYPE_3__ {int out_of_ssa_tag; } ;

/* Variables and functions */
 int ROOT_VAR_NONE ; 
 scalar_t__ SSA_NAME ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  change_partition_var (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ create_temp (scalar_t__) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int num_var_partitions (int /*<<< orphan*/ ) ; 
 scalar_t__ partition_to_var (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_exprs (scalar_t__,char*,scalar_t__,char*,scalar_t__,char*) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ root_var (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  root_var_delete (int /*<<< orphan*/ ) ; 
 int root_var_first_partition (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  root_var_init (int /*<<< orphan*/ ) ; 
 int root_var_next_partition (int /*<<< orphan*/ ,int) ; 
 int root_var_num (int /*<<< orphan*/ ) ; 
 TYPE_1__* var_ann (scalar_t__) ; 
 int var_to_partition (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
assign_vars (var_map map)
{
  int x, i, num, rep;
  tree t, var;
  var_ann_t ann;
  root_var_p rv;

  rv = root_var_init (map);
  if (!rv) 
    return;

  /* Coalescing may already have forced some partitions to their root 
     variable. Find these and tag them.  */

  num = num_var_partitions (map);
  for (x = 0; x < num; x++)
    {
      var = partition_to_var (map, x);
      if (TREE_CODE (var) != SSA_NAME)
	{
	  /* Coalescing will already have verified that more than one
	     partition doesn't have the same root variable. Simply marked
	     the variable as assigned.  */
	  ann = var_ann (var);
	  ann->out_of_ssa_tag = 1;
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, "partition %d has variable ", x);
	      print_generic_expr (dump_file, var, TDF_SLIM);
	      fprintf (dump_file, " assigned to it.\n");
	    }

	}
    }

  num = root_var_num (rv);
  for (x = 0; x < num; x++)
    {
      var = root_var (rv, x);
      ann = var_ann (var);
      for (i = root_var_first_partition (rv, x);
	   i != ROOT_VAR_NONE;
	   i = root_var_next_partition (rv, i))
	{
	  t = partition_to_var (map, i);

	  if (t == var || TREE_CODE (t) != SSA_NAME)
	    continue;

	  rep = var_to_partition (map, t);
	  
	  if (!ann->out_of_ssa_tag)
	    {
	      if (dump_file && (dump_flags & TDF_DETAILS))
		print_exprs (dump_file, "", t, "  --> ", var, "\n");
	      change_partition_var (map, var, rep);
	      continue;
	    }

	  if (dump_file && (dump_flags & TDF_DETAILS))
	    print_exprs (dump_file, "", t, " not coalesced with ", var, 
			 "");

	  var = create_temp (t);
	  change_partition_var (map, var, rep);
	  ann = var_ann (var);

	  if (dump_file && (dump_flags & TDF_DETAILS))
	    {
	      fprintf (dump_file, " -->  New temp:  '");
	      print_generic_expr (dump_file, var, TDF_SLIM);
	      fprintf (dump_file, "'\n");
	    }
	}
    }

  root_var_delete (rv);
}