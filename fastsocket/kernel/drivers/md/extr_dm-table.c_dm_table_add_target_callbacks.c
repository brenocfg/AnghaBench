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
struct dm_target_callbacks {int /*<<< orphan*/  list; } ;
struct dm_table {int /*<<< orphan*/  target_callbacks; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dm_table_add_target_callbacks(struct dm_table *t, struct dm_target_callbacks *cb)
{
	list_add(&cb->list, &t->target_callbacks);
}