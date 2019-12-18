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
 int /*<<< orphan*/ * allocated_bundle_states_chain ; 
 scalar_t__ bundle_states_num ; 
 int /*<<< orphan*/ * free_bundle_state_chain ; 

__attribute__((used)) static void
initiate_bundle_states (void)
{
  bundle_states_num = 0;
  free_bundle_state_chain = NULL;
  allocated_bundle_states_chain = NULL;
}