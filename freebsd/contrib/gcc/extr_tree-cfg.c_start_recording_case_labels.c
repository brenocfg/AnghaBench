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
 int /*<<< orphan*/ * edge_to_cases ; 
 int /*<<< orphan*/  edge_to_cases_cleanup ; 
 int /*<<< orphan*/  edge_to_cases_eq ; 
 int /*<<< orphan*/  edge_to_cases_hash ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * htab_create (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
start_recording_case_labels (void)
{
  gcc_assert (edge_to_cases == NULL);

  edge_to_cases = htab_create (37,
			       edge_to_cases_hash,
			       edge_to_cases_eq,
			       edge_to_cases_cleanup);
}