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
typedef  int /*<<< orphan*/  var_map ;
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  tpa_p ;
typedef  int /*<<< orphan*/  conflict_graph ;
typedef  scalar_t__ coalesce_list_p ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ NO_BEST_COALESCE ; 
 int NO_PARTITION ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 int TPA_NONE ; 
 int /*<<< orphan*/  conflict_graph_conflict_p (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  conflict_graph_merge_regs (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  partition_to_var (int /*<<< orphan*/ ,int) ; 
 scalar_t__ pop_best_coalesce (scalar_t__,int*,int*) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tpa_find_tree (int /*<<< orphan*/ ,int) ; 
 int tpa_first_partition (int /*<<< orphan*/ ,int) ; 
 int tpa_next_partition (int /*<<< orphan*/ ,int) ; 
 int tpa_num_trees (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpa_remove_partition (int /*<<< orphan*/ ,int,int) ; 
 int var_to_partition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int var_union (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
coalesce_tpa_members (tpa_p tpa, conflict_graph graph, var_map map, 
		      coalesce_list_p cl, FILE *debug)
{
  int x, y, z, w;
  tree var, tmp;

  /* Attempt to coalesce any items in a coalesce list.  */
  if (cl)
    {
      while (pop_best_coalesce (cl, &x, &y) != NO_BEST_COALESCE)
        {
	  if (debug)
	    {
	      fprintf (debug, "Coalesce list: (%d)", x);
	      print_generic_expr (debug, partition_to_var (map, x), TDF_SLIM);
	      fprintf (debug, " & (%d)", y);
	      print_generic_expr (debug, partition_to_var (map, y), TDF_SLIM);
	    }

	  w = tpa_find_tree (tpa, x);
	  z = tpa_find_tree (tpa, y);
	  if (w != z || w == TPA_NONE || z == TPA_NONE)
	    {
	      if (debug)
		{
		  if (w != z)
		    fprintf (debug, ": Fail, Non-matching TPA's\n");
		  if (w == TPA_NONE)
		    fprintf (debug, ": Fail %d non TPA.\n", x);
		  else
		    fprintf (debug, ": Fail %d non TPA.\n", y);
		}
	      continue;
	    }
	  var = partition_to_var (map, x);
	  tmp = partition_to_var (map, y);
	  x = var_to_partition (map, var);
	  y = var_to_partition (map, tmp);
	  if (debug)
	    fprintf (debug, " [map: %d, %d] ", x, y);
	  if (x == y)
	    {
	      if (debug)
		fprintf (debug, ": Already Coalesced.\n");
	      continue;
	    }
	  if (!conflict_graph_conflict_p (graph, x, y))
	    {
	      z = var_union (map, var, tmp);
	      if (z == NO_PARTITION)
	        {
		  if (debug)
		    fprintf (debug, ": Unable to perform partition union.\n");
		  continue;
		}

	      /* z is the new combined partition. We need to remove the other
	         partition from the list. Set x to be that other partition.  */
	      if (z == x)
	        {
		  conflict_graph_merge_regs (graph, x, y);
		  w = tpa_find_tree (tpa, y);
		  tpa_remove_partition (tpa, w, y);
		}
	      else
	        {
		  conflict_graph_merge_regs (graph, y, x);
		  w = tpa_find_tree (tpa, x);
		  tpa_remove_partition (tpa, w, x);
		}

	      if (debug)
		fprintf (debug, ": Success -> %d\n", z);
	    }
	  else
	    if (debug)
	      fprintf (debug, ": Fail due to conflict\n");
	}
      /* If using a coalesce list, don't try to coalesce anything else.  */
      return;
    }

  for (x = 0; x < tpa_num_trees (tpa); x++)
    {
      while (tpa_first_partition (tpa, x) != TPA_NONE)
        {
	  int p1, p2;
	  /* Coalesce first partition with anything that doesn't conflict.  */
	  y = tpa_first_partition (tpa, x);
	  tpa_remove_partition (tpa, x, y);

	  var = partition_to_var (map, y);
	  /* p1 is the partition representative to which y belongs.  */
	  p1 = var_to_partition (map, var);
	  
	  for (z = tpa_next_partition (tpa, y); 
	       z != TPA_NONE; 
	       z = tpa_next_partition (tpa, z))
	    {
	      tmp = partition_to_var (map, z);
	      /* p2 is the partition representative to which z belongs.  */
	      p2 = var_to_partition (map, tmp);
	      if (debug)
		{
		  fprintf (debug, "Coalesce : ");
		  print_generic_expr (debug, var, TDF_SLIM);
		  fprintf (debug, " &");
		  print_generic_expr (debug, tmp, TDF_SLIM);
		  fprintf (debug, "  (%d ,%d)", p1, p2);
		}

	      /* If partitions are already merged, don't check for conflict.  */
	      if (tmp == var)
	        {
		  tpa_remove_partition (tpa, x, z);
		  if (debug)
		    fprintf (debug, ": Already coalesced\n");
		}
	      else
		if (!conflict_graph_conflict_p (graph, p1, p2))
		  {
		    int v;
		    if (tpa_find_tree (tpa, y) == TPA_NONE 
			|| tpa_find_tree (tpa, z) == TPA_NONE)
		      {
			if (debug)
			  fprintf (debug, ": Fail non-TPA member\n");
			continue;
		      }
		    if ((v = var_union (map, var, tmp)) == NO_PARTITION)
		      {
			if (debug)
			  fprintf (debug, ": Fail cannot combine partitions\n");
			continue;
		      }

		    tpa_remove_partition (tpa, x, z);
		    if (v == p1)
		      conflict_graph_merge_regs (graph, v, z);
		    else
		      {
			/* Update the first partition's representative.  */
			conflict_graph_merge_regs (graph, v, y);
			p1 = v;
		      }

		    /* The root variable of the partition may be changed
		       now.  */
		    var = partition_to_var (map, p1);

		    if (debug)
		      fprintf (debug, ": Success -> %d\n", v);
		  }
		else
		  if (debug)
		    fprintf (debug, ": Fail, Conflict\n");
	    }
	}
    }
}