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
struct multipath_info {TYPE_1__* rdev; } ;
struct mpconf {int raid_disks; struct multipath_info* multipaths; TYPE_2__* mddev; } ;
struct TYPE_4__ {scalar_t__ degraded; } ;
struct TYPE_3__ {int /*<<< orphan*/  bdev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_multipath_conf (struct mpconf *conf)
{
	int i;
	struct multipath_info *tmp;

	printk("MULTIPATH conf printout:\n");
	if (!conf) {
		printk("(conf==NULL)\n");
		return;
	}
	printk(" --- wd:%d rd:%d\n", conf->raid_disks - conf->mddev->degraded,
			 conf->raid_disks);

	for (i = 0; i < conf->raid_disks; i++) {
		char b[BDEVNAME_SIZE];
		tmp = conf->multipaths + i;
		if (tmp->rdev)
			printk(" disk%d, o:%d, dev:%s\n",
				i,!test_bit(Faulty, &tmp->rdev->flags),
			       bdevname(tmp->rdev->bdev,b));
	}
}