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
 int /*<<< orphan*/ * cgraph_varpool_first_unanalyzed_node ; 
 int /*<<< orphan*/ * cgraph_varpool_last_needed_node ; 
 int /*<<< orphan*/ * cgraph_varpool_nodes_queue ; 

void
cgraph_varpool_reset_queue (void)
{
  cgraph_varpool_last_needed_node = NULL;
  cgraph_varpool_nodes_queue = NULL;
  cgraph_varpool_first_unanalyzed_node = NULL;
}