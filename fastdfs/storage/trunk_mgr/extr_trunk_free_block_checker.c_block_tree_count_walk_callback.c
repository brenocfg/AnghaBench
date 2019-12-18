#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ count; } ;
struct TYPE_4__ {TYPE_1__ block_array; } ;
typedef  TYPE_2__ FDFSTrunksById ;

/* Variables and functions */

__attribute__((used)) static int block_tree_count_walk_callback(void *data, void *args)
{
	int *pcount;
	pcount = (int *)args;

	*pcount += ((FDFSTrunksById *)data)->block_array.count;
	return 0;
}