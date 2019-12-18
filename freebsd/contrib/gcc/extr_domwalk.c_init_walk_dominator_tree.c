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
struct dom_walk_data {int /*<<< orphan*/ * block_data_stack; int /*<<< orphan*/ * free_block_data; } ;

/* Variables and functions */

void
init_walk_dominator_tree (struct dom_walk_data *walk_data)
{
  walk_data->free_block_data = NULL;
  walk_data->block_data_stack = NULL;
}