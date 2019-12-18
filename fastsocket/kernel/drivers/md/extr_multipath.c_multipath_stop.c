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
struct mpconf {struct mpconf* multipaths; int /*<<< orphan*/  pool; } ;
struct mddev {struct mpconf* private; int /*<<< orphan*/  queue; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_sync_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mpconf*) ; 
 int /*<<< orphan*/  md_unregister_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int multipath_stop (struct mddev *mddev)
{
	struct mpconf *conf = mddev->private;

	md_unregister_thread(&mddev->thread);
	blk_sync_queue(mddev->queue); /* the unplug fn references 'conf'*/
	mempool_destroy(conf->pool);
	kfree(conf->multipaths);
	kfree(conf);
	mddev->private = NULL;
	return 0;
}