#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* partition_pair_p ;
typedef  TYPE_2__* coalesce_list_p ;
struct TYPE_5__ {int /*<<< orphan*/  map; TYPE_1__** list; scalar_t__ add_mode; } ;
struct TYPE_4__ {int second_partition; int cost; int first_partition; struct TYPE_4__* next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TDF_SLIM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int num_var_partitions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  partition_to_var (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void 
dump_coalesce_list (FILE *f, coalesce_list_p cl)
{
  partition_pair_p node;
  int x, num;
  tree var;

  if (cl->add_mode)
    {
      fprintf (f, "Coalesce List:\n");
      num = num_var_partitions (cl->map);
      for (x = 0; x < num; x++)
        {
	  node = cl->list[x];
	  if (node)
	    {
	      fprintf (f, "[");
	      print_generic_expr (f, partition_to_var (cl->map, x), TDF_SLIM);
	      fprintf (f, "] - ");
	      for ( ; node; node = node->next)
	        {
		  var = partition_to_var (cl->map, node->second_partition);
		  print_generic_expr (f, var, TDF_SLIM);
		  fprintf (f, "(%1d), ", node->cost);
		}
	      fprintf (f, "\n");
	    }
	}
    }
  else
    {
      fprintf (f, "Sorted Coalesce list:\n");
      for (node = cl->list[0]; node; node = node->next)
        {
	  fprintf (f, "(%d) ", node->cost);
	  var = partition_to_var (cl->map, node->first_partition);
	  print_generic_expr (f, var, TDF_SLIM);
	  fprintf (f, " : ");
	  var = partition_to_var (cl->map, node->second_partition);
	  print_generic_expr (f, var, TDF_SLIM);
	  fprintf (f, "\n");
	}
    }
}