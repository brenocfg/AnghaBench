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
struct mddev {int level; int new_level; int /*<<< orphan*/  new_layout; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALGORITHM_PARITY_N ; 
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* raid45_takeover_raid0 (struct mddev*,int) ; 
 void* raid5_takeover_raid1 (struct mddev*) ; 
 void* raid5_takeover_raid6 (struct mddev*) ; 
 void* setup_conf (struct mddev*) ; 

__attribute__((used)) static void *raid5_takeover(struct mddev *mddev)
{
	/* raid5 can take over:
	 *  raid0 - if there is only one strip zone - make it a raid4 layout
	 *  raid1 - if there are two drives.  We need to know the chunk size
	 *  raid4 - trivial - just use a raid4 layout.
	 *  raid6 - Providing it is a *_6 layout
	 */
	if (mddev->level == 0)
		return raid45_takeover_raid0(mddev, 5);
	if (mddev->level == 1)
		return raid5_takeover_raid1(mddev);
	if (mddev->level == 4) {
		mddev->new_layout = ALGORITHM_PARITY_N;
		mddev->new_level = 5;
		return setup_conf(mddev);
	}
	if (mddev->level == 6)
		return raid5_takeover_raid6(mddev);

	return ERR_PTR(-EINVAL);
}