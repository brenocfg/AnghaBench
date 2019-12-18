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
struct r5conf {int raid_disks; scalar_t__ reshape_progress; scalar_t__ recovery_disabled; struct disk_info* disks; } ;
struct mddev {scalar_t__ recovery_disabled; struct r5conf* private; } ;
struct md_rdev {int raid_disk; int /*<<< orphan*/  flags; int /*<<< orphan*/  nr_pending; } ;
struct disk_info {struct md_rdev* replacement; struct md_rdev* rdev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 scalar_t__ MaxSector ; 
 int /*<<< orphan*/  Replacement ; 
 int /*<<< orphan*/  WantReplacement ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_failed (struct r5conf*) ; 
 int /*<<< orphan*/  print_raid5_conf (struct r5conf*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid5_remove_disk(struct mddev *mddev, struct md_rdev *rdev)
{
	struct r5conf *conf = mddev->private;
	int err = 0;
	int number = rdev->raid_disk;
	struct md_rdev **rdevp;
	struct disk_info *p = conf->disks + number;

	print_raid5_conf(conf);
	if (rdev == p->rdev)
		rdevp = &p->rdev;
	else if (rdev == p->replacement)
		rdevp = &p->replacement;
	else
		return 0;

	if (number >= conf->raid_disks &&
	    conf->reshape_progress == MaxSector)
		clear_bit(In_sync, &rdev->flags);

	if (test_bit(In_sync, &rdev->flags) ||
	    atomic_read(&rdev->nr_pending)) {
		err = -EBUSY;
		goto abort;
	}
	/* Only remove non-faulty devices if recovery
	 * isn't possible.
	 */
	if (!test_bit(Faulty, &rdev->flags) &&
	    mddev->recovery_disabled != conf->recovery_disabled &&
	    !has_failed(conf) &&
	    (!p->replacement || p->replacement == rdev) &&
	    number < conf->raid_disks) {
		err = -EBUSY;
		goto abort;
	}
	*rdevp = NULL;
	synchronize_rcu();
	if (atomic_read(&rdev->nr_pending)) {
		/* lost the race, try later */
		err = -EBUSY;
		*rdevp = rdev;
	} else if (p->replacement) {
		/* We must have just cleared 'rdev' */
		p->rdev = p->replacement;
		clear_bit(Replacement, &p->replacement->flags);
		smp_mb(); /* Make sure other CPUs may see both as identical
			   * but will never see neither - if they are careful
			   */
		p->replacement = NULL;
		clear_bit(WantReplacement, &rdev->flags);
	} else
		/* We might have just removed the Replacement as faulty-
		 * clear the bit just in case
		 */
		clear_bit(WantReplacement, &rdev->flags);
abort:

	print_raid5_conf(conf);
	return err;
}