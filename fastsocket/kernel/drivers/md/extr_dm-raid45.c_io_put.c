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
struct TYPE_2__ {int /*<<< orphan*/  suspendq; int /*<<< orphan*/  in_process; } ;
struct raid_set {TYPE_1__ io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 scalar_t__ io_ref (struct raid_set*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void io_put(struct raid_set *rs)
{
	/* Intel: rebuild data corrupter? */
	if (atomic_dec_and_test(&rs->io.in_process))
		wake_up(&rs->io.suspendq);
	else
		BUG_ON(io_ref(rs) < 0);
}