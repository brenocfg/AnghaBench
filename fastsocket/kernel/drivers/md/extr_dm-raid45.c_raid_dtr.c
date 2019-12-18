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
struct TYPE_4__ {int /*<<< orphan*/  raid_devs; } ;
struct TYPE_3__ {int /*<<< orphan*/  wq; } ;
struct raid_set {TYPE_2__ set; TYPE_1__ io; } ;
struct dm_target {struct raid_set* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  context_free (struct raid_set*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void raid_dtr(struct dm_target *ti)
{
	struct raid_set *rs = ti->private;

	destroy_workqueue(rs->io.wq);
	context_free(rs, rs->set.raid_devs);
}