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
struct raid1_info {struct md_rdev* rdev; } ;
struct r1conf {int raid_disks; scalar_t__ recovery_disabled; struct raid1_info* mirrors; } ;
struct mddev {scalar_t__ recovery_disabled; int degraded; struct r1conf* private; } ;
struct md_rdev {int raid_disk; int /*<<< orphan*/  flags; int /*<<< orphan*/  nr_pending; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  In_sync ; 
 int /*<<< orphan*/  Replacement ; 
 int /*<<< orphan*/  WantReplacement ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeze_array (struct r1conf*,int /*<<< orphan*/ ) ; 
 int md_integrity_register (struct mddev*) ; 
 int /*<<< orphan*/  print_conf (struct r1conf*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unfreeze_array (struct r1conf*) ; 

__attribute__((used)) static int raid1_remove_disk(struct mddev *mddev, struct md_rdev *rdev)
{
	struct r1conf *conf = mddev->private;
	int err = 0;
	int number = rdev->raid_disk;
	struct raid1_info *p = conf->mirrors + number;

	if (rdev != p->rdev)
		p = conf->mirrors + conf->raid_disks + number;

	print_conf(conf);
	if (rdev == p->rdev) {
		if (test_bit(In_sync, &rdev->flags) ||
		    atomic_read(&rdev->nr_pending)) {
			err = -EBUSY;
			goto abort;
		}
		/* Only remove non-faulty devices if recovery
		 * is not possible.
		 */
		if (!test_bit(Faulty, &rdev->flags) &&
		    mddev->recovery_disabled != conf->recovery_disabled &&
		    mddev->degraded < conf->raid_disks) {
			err = -EBUSY;
			goto abort;
		}
		p->rdev = NULL;
		synchronize_rcu();
		if (atomic_read(&rdev->nr_pending)) {
			/* lost the race, try later */
			err = -EBUSY;
			p->rdev = rdev;
			goto abort;
		} else if (conf->mirrors[conf->raid_disks + number].rdev) {
			/* We just removed a device that is being replaced.
			 * Move down the replacement.  We drain all IO before
			 * doing this to avoid confusion.
			 */
			struct md_rdev *repl =
				conf->mirrors[conf->raid_disks + number].rdev;
			freeze_array(conf, 0);
			clear_bit(Replacement, &repl->flags);
			p->rdev = repl;
			conf->mirrors[conf->raid_disks + number].rdev = NULL;
			unfreeze_array(conf);
			clear_bit(WantReplacement, &rdev->flags);
		} else
			clear_bit(WantReplacement, &rdev->flags);
		err = md_integrity_register(mddev);
	}
abort:

	print_conf(conf);
	return err;
}