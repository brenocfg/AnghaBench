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
struct r5conf {int /*<<< orphan*/  plug; } ;
struct mddev {int /*<<< orphan*/ * to_remove; int /*<<< orphan*/ * plug; struct r5conf* private; TYPE_2__* queue; int /*<<< orphan*/  thread; } ;
struct TYPE_3__ {int /*<<< orphan*/ * congested_fn; } ;
struct TYPE_4__ {TYPE_1__ backing_dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_conf (struct r5conf*) ; 
 int /*<<< orphan*/  md_unregister_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plugger_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raid5_attrs_group ; 

__attribute__((used)) static int stop(struct mddev *mddev)
{
	struct r5conf *conf = mddev->private;

	md_unregister_thread(&mddev->thread);
	if (mddev->queue)
		mddev->queue->backing_dev_info.congested_fn = NULL;
	plugger_flush(&conf->plug); /* the unplug fn references 'conf'*/
	free_conf(conf);
	mddev->private = NULL;
	mddev->plug = NULL;
	mddev->to_remove = &raid5_attrs_group;
	return 0;
}