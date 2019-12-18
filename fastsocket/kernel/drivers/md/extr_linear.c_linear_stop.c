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
struct mddev {int /*<<< orphan*/ * private; int /*<<< orphan*/  queue; int /*<<< orphan*/  reconfig_mutex; } ;
struct linear_conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_sync_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct linear_conf*) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 struct linear_conf* rcu_dereference_protected (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int linear_stop (struct mddev *mddev)
{
	struct linear_conf *conf =
		rcu_dereference_protected(mddev->private,
					  lockdep_is_held(
						  &mddev->reconfig_mutex));

	/*
	 * We do not require rcu protection here since
	 * we hold reconfig_mutex for both linear_add and
	 * linear_stop, so they cannot race.
	 * We should make sure any old 'conf's are properly
	 * freed though.
	 */
	rcu_barrier();
	blk_sync_queue(mddev->queue); /* the unplug fn references 'conf'*/
	kfree(conf);
	mddev->private = NULL;

	return 0;
}