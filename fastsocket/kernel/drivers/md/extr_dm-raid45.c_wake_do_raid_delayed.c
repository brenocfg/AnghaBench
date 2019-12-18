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
struct TYPE_2__ {int /*<<< orphan*/  dws_do_raid; int /*<<< orphan*/  wq; } ;
struct raid_set {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void wake_do_raid_delayed(struct raid_set *rs, unsigned long delay)
{
	queue_delayed_work(rs->io.wq, &rs->io.dws_do_raid, delay);
}