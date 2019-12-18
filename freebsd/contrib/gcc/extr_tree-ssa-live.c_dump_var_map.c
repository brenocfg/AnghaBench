#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* var_map ;
struct TYPE_4__ {unsigned int num_partitions; int* compact_to_partition; scalar_t__* partition_to_var; int* partition_to_compact; int /*<<< orphan*/  var_partition; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 unsigned int num_ssa_names ; 
 int partition_find (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  partition_to_var (TYPE_1__*,int) ; 
 int /*<<< orphan*/  print_generic_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dump_var_map (FILE *f, var_map map)
{
  int t;
  unsigned x, y;
  int p;

  fprintf (f, "\nPartition map \n\n");

  for (x = 0; x < map->num_partitions; x++)
    {
      if (map->compact_to_partition != NULL)
	p = map->compact_to_partition[x];
      else
	p = x;

      if (map->partition_to_var[p] == NULL_TREE)
        continue;

      t = 0;
      for (y = 1; y < num_ssa_names; y++)
        {
	  p = partition_find (map->var_partition, y);
	  if (map->partition_to_compact)
	    p = map->partition_to_compact[p];
	  if (p == (int)x)
	    {
	      if (t++ == 0)
	        {
		  fprintf(f, "Partition %d (", x);
		  print_generic_expr (f, partition_to_var (map, p), TDF_SLIM);
		  fprintf (f, " - ");
		}
	      fprintf (f, "%d ", y);
	    }
	}
      if (t != 0)
	fprintf (f, ")\n");
    }
  fprintf (f, "\n");
}