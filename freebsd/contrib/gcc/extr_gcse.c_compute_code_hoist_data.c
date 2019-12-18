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
 int /*<<< orphan*/  antloc ; 
 int /*<<< orphan*/  calculate_dominance_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comp ; 
 int /*<<< orphan*/  compute_code_hoist_vbeinout () ; 
 int /*<<< orphan*/  compute_local_properties (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compute_transpout () ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  expr_hash_table ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  transp ; 

__attribute__((used)) static void
compute_code_hoist_data (void)
{
  compute_local_properties (transp, comp, antloc, &expr_hash_table);
  compute_transpout ();
  compute_code_hoist_vbeinout ();
  calculate_dominance_info (CDI_DOMINATORS);
  if (dump_file)
    fprintf (dump_file, "\n");
}