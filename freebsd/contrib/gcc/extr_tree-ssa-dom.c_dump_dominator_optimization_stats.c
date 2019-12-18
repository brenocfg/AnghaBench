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
struct TYPE_2__ {long num_exprs_considered; int /*<<< orphan*/  num_copy_prop; int /*<<< orphan*/  num_const_prop; int /*<<< orphan*/  num_re; int /*<<< orphan*/  num_stmts; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PERCENT (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  avail_exprs ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  htab_statistics (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ opt_stats ; 

void
dump_dominator_optimization_stats (FILE *file)
{
  long n_exprs;

  fprintf (file, "Total number of statements:                   %6ld\n\n",
	   opt_stats.num_stmts);
  fprintf (file, "Exprs considered for dominator optimizations: %6ld\n",
           opt_stats.num_exprs_considered);

  n_exprs = opt_stats.num_exprs_considered;
  if (n_exprs == 0)
    n_exprs = 1;

  fprintf (file, "    Redundant expressions eliminated:         %6ld (%.0f%%)\n",
	   opt_stats.num_re, PERCENT (opt_stats.num_re,
				      n_exprs));
  fprintf (file, "    Constants propagated:                     %6ld\n",
	   opt_stats.num_const_prop);
  fprintf (file, "    Copies propagated:                        %6ld\n",
	   opt_stats.num_copy_prop);

  fprintf (file, "\nHash table statistics:\n");

  fprintf (file, "    avail_exprs: ");
  htab_statistics (file, avail_exprs);
}