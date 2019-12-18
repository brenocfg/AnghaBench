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

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 int /*<<< orphan*/  CDI_POST_DOMINATORS ; 
 int /*<<< orphan*/  build_omp_regions () ; 
 int /*<<< orphan*/  cleanup_tree_cfg () ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  dump_omp_region (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_omp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  free_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_omp_regions () ; 
 int /*<<< orphan*/  remove_exit_barriers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  root_omp_region ; 

__attribute__((used)) static unsigned int
execute_expand_omp (void)
{
  build_omp_regions ();

  if (!root_omp_region)
    return 0;

  if (dump_file)
    {
      fprintf (dump_file, "\nOMP region tree\n\n");
      dump_omp_region (dump_file, root_omp_region, 0);
      fprintf (dump_file, "\n");
    }

  remove_exit_barriers (root_omp_region);

  expand_omp (root_omp_region);

  free_dominance_info (CDI_DOMINATORS);
  free_dominance_info (CDI_POST_DOMINATORS);
  cleanup_tree_cfg ();

  free_omp_regions ();

  return 0;
}