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
struct raid10_info {scalar_t__ recovery_disabled; struct md_rdev* replacement; struct md_rdev* rdev; } ;
struct TYPE_2__ {int raid_disks; } ;
struct r10conf {TYPE_1__ geo; struct raid10_info* mirrors; } ;
struct mddev {scalar_t__ recovery_disabled; struct r10conf* private; } ;
struct md_rdev {int raid_disk; int /*<<< orphan*/  flags; int /*<<< orphan*/  nr_pending; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  Replacement ; 
 int /*<<< orphan*/  WantReplacement ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ enough (struct r10conf*,int) ; 
 int md_integrity_register (struct mddev*) ; 
 int /*<<< orphan*/  print_conf (struct r10conf*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int raid10_remove_disk(struct mddev *mddev, struct md_rdev *rdev)
{
	struct r10conf *conf = mddev->private;
	int err = 0;
	int number = rdev->raid_disk;
	struct md_rdev **rdevp;
	struct raid10_info *p = conf->mirrors + number;

	print_conf(conf);
	if (rdev == p->rdev)
		rdevp = &p->rdev;
	else if (rdev == p->replacement)
		rdevp = &p->replacement;
	else
		return 0;

	if (test_bit(In_sync, &rdev->flags) ||
	    atomic_read(&rdev->nr_pending)) {
		err = -EBUSY;
		goto abort;
	}
	/* Only remove faulty devices if recovery
	 * is not possible.
	 */
	if (!test_bit(Faulty, &rdev->flags) &&
	    mddev->recovery_disabled != p->recovery_disabled &&
	    (!p->replacement || p->replacement == rdev) &&
	    number < conf->geo.raid_disks &&
	    enough(conf, -1)) {
		err = -EBUSY;
		goto abort;
	}
	*rdevp = NULL;
	synchronize_rcu();
	if (atomic_read(&rdev->nr_pending)) {
		/* lost the race, try later */
		err = -EBUSY;
		*rdevp = rdev;
		goto abort;
	} else if (p->replacement) {
		/* We must have just cleared 'rdev' */
		p->rdev = p->replacement;
		clear_bit(Replacement, &p->replacement->flags);
		smp_mb(); /* Make sure other CPUs may see both as identical
			   * but will never see neither -- if they are careful.
			   */
		p->replacement = NULL;
		clear_bit(WantReplacement, &rdev->flags);
	} else
		/* We might have just remove the Replacement as faulty
		 * Clear the flag just in case
		 */
		clear_bit(WantReplacement, &rdev->flags);

	err = md_integrity_register(mddev);

abort:

	print_conf(conf);
	return err;
}