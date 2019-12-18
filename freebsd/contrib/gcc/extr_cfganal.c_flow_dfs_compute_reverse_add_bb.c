#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* depth_first_search_ds ;
typedef  TYPE_2__* basic_block ;
struct TYPE_6__ {int /*<<< orphan*/  index; } ;
struct TYPE_5__ {int /*<<< orphan*/  visited_blocks; int /*<<< orphan*/  sp; TYPE_2__** stack; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flow_dfs_compute_reverse_add_bb (depth_first_search_ds data, basic_block bb)
{
  data->stack[data->sp++] = bb;
  SET_BIT (data->visited_blocks, bb->index);
}