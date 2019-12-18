#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int total_vars; int nonpointer_vars; int unified_vars_static; int unified_vars_dynamic; int iterations; int num_edges; int num_implicit_edges; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int TDF_STATS ; 
 unsigned int VEC_length (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dump_flags ; 
 int /*<<< orphan*/  dump_solution_for_var (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__ stats ; 
 int /*<<< orphan*/  varinfo_t ; 
 int /*<<< orphan*/  varmap ; 

void
dump_sa_points_to_info (FILE *outfile)
{
  unsigned int i;

  fprintf (outfile, "\nPoints-to sets\n\n");

  if (dump_flags & TDF_STATS)
    {
      fprintf (outfile, "Stats:\n");
      fprintf (outfile, "Total vars:               %d\n", stats.total_vars);
      fprintf (outfile, "Non-pointer vars:          %d\n",
	       stats.nonpointer_vars);
      fprintf (outfile, "Statically unified vars:  %d\n",
	       stats.unified_vars_static);
      fprintf (outfile, "Dynamically unified vars: %d\n",
	       stats.unified_vars_dynamic);
      fprintf (outfile, "Iterations:               %d\n", stats.iterations);
      fprintf (outfile, "Number of edges:          %d\n", stats.num_edges);
      fprintf (outfile, "Number of implicit edges: %d\n",
	       stats.num_implicit_edges);
    }

  for (i = 0; i < VEC_length (varinfo_t, varmap); i++)
    dump_solution_for_var (outfile, i);
}