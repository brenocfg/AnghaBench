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
 int /*<<< orphan*/  EXIT_BLOCK_PTR ; 
 int /*<<< orphan*/  remove_fake_predecessors (int /*<<< orphan*/ ) ; 

void
remove_fake_exit_edges (void)
{
  remove_fake_predecessors (EXIT_BLOCK_PTR);
}