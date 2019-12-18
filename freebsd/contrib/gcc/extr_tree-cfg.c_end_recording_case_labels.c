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
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ *) ; 

void
end_recording_case_labels (void)
{
  htab_delete (edge_to_cases);
  edge_to_cases = NULL;
}