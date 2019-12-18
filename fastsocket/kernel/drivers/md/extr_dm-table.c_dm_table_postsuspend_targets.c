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
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  suspend_targets (struct dm_table*,int) ; 

void dm_table_postsuspend_targets(struct dm_table *t)
{
	if (!t)
		return;

	suspend_targets(t, 1);
}