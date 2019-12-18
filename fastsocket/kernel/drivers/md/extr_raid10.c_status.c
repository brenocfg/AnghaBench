#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct seq_file {int dummy; } ;
struct TYPE_4__ {int near_copies; int raid_disks; int far_copies; scalar_t__ far_offset; } ;
struct r10conf {TYPE_3__* mirrors; TYPE_1__ geo; } ;
struct mddev {int chunk_sectors; scalar_t__ degraded; struct r10conf* private; } ;
struct TYPE_6__ {TYPE_2__* rdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void status(struct seq_file *seq, struct mddev *mddev)
{
	struct r10conf *conf = mddev->private;
	int i;

	if (conf->geo.near_copies < conf->geo.raid_disks)
		seq_printf(seq, " %dK chunks", mddev->chunk_sectors / 2);
	if (conf->geo.near_copies > 1)
		seq_printf(seq, " %d near-copies", conf->geo.near_copies);
	if (conf->geo.far_copies > 1) {
		if (conf->geo.far_offset)
			seq_printf(seq, " %d offset-copies", conf->geo.far_copies);
		else
			seq_printf(seq, " %d far-copies", conf->geo.far_copies);
	}
	seq_printf(seq, " [%d/%d] [", conf->geo.raid_disks,
					conf->geo.raid_disks - mddev->degraded);
	for (i = 0; i < conf->geo.raid_disks; i++)
		seq_printf(seq, "%s",
			      conf->mirrors[i].rdev &&
			      test_bit(In_sync, &conf->mirrors[i].rdev->flags) ? "U" : "_");
	seq_printf(seq, "]");
}