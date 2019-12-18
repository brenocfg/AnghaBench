#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dm_target {TYPE_1__* type; } ;
struct dm_table {int num_targets; struct dm_target* targets; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* presuspend ) (struct dm_target*) ;int /*<<< orphan*/  (* postsuspend ) (struct dm_target*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dm_target*) ; 
 int /*<<< orphan*/  stub2 (struct dm_target*) ; 

__attribute__((used)) static void suspend_targets(struct dm_table *t, unsigned postsuspend)
{
	int i = t->num_targets;
	struct dm_target *ti = t->targets;

	while (i--) {
		if (postsuspend) {
			if (ti->type->postsuspend)
				ti->type->postsuspend(ti);
		} else if (ti->type->presuspend)
			ti->type->presuspend(ti);

		ti++;
	}
}