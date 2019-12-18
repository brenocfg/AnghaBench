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
typedef  int /*<<< orphan*/  loop_vec_info ;

/* Variables and functions */
 int /*<<< orphan*/  REPORT_DETAILS ; 
 int /*<<< orphan*/  REPORT_UNVECTORIZED_LOOPS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vect_compute_data_refs_alignment (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vect_dump ; 
 scalar_t__ vect_print_dump_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
vect_analyze_data_refs_alignment (loop_vec_info loop_vinfo)
{
  if (vect_print_dump_info (REPORT_DETAILS))
    fprintf (vect_dump, "=== vect_analyze_data_refs_alignment ===");

  if (!vect_compute_data_refs_alignment (loop_vinfo))
    {
      if (vect_print_dump_info (REPORT_UNVECTORIZED_LOOPS))
	fprintf (vect_dump, 
		 "not vectorized: can't calculate alignment for data ref.");
      return false;
    }

  return true;
}