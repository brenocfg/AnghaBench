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
struct mddev {int degraded; int raid_disks; int layout; int new_level; int new_layout; int delta_disks; int /*<<< orphan*/ * pers; } ;

/* Variables and functions */
#define  ALGORITHM_LEFT_ASYMMETRIC 133 
 int ALGORITHM_LEFT_ASYMMETRIC_6 ; 
#define  ALGORITHM_LEFT_SYMMETRIC 132 
 int ALGORITHM_LEFT_SYMMETRIC_6 ; 
#define  ALGORITHM_PARITY_0 131 
 int ALGORITHM_PARITY_0_6 ; 
#define  ALGORITHM_PARITY_N 130 
#define  ALGORITHM_RIGHT_ASYMMETRIC 129 
 int ALGORITHM_RIGHT_ASYMMETRIC_6 ; 
#define  ALGORITHM_RIGHT_SYMMETRIC 128 
 int ALGORITHM_RIGHT_SYMMETRIC_6 ; 
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid5_personality ; 
 void* setup_conf (struct mddev*) ; 

__attribute__((used)) static void *raid6_takeover(struct mddev *mddev)
{
	/* Currently can only take over a raid5.  We map the
	 * personality to an equivalent raid6 personality
	 * with the Q block at the end.
	 */
	int new_layout;

	if (mddev->pers != &raid5_personality)
		return ERR_PTR(-EINVAL);
	if (mddev->degraded > 1)
		return ERR_PTR(-EINVAL);
	if (mddev->raid_disks > 253)
		return ERR_PTR(-EINVAL);
	if (mddev->raid_disks < 3)
		return ERR_PTR(-EINVAL);

	switch (mddev->layout) {
	case ALGORITHM_LEFT_ASYMMETRIC:
		new_layout = ALGORITHM_LEFT_ASYMMETRIC_6;
		break;
	case ALGORITHM_RIGHT_ASYMMETRIC:
		new_layout = ALGORITHM_RIGHT_ASYMMETRIC_6;
		break;
	case ALGORITHM_LEFT_SYMMETRIC:
		new_layout = ALGORITHM_LEFT_SYMMETRIC_6;
		break;
	case ALGORITHM_RIGHT_SYMMETRIC:
		new_layout = ALGORITHM_RIGHT_SYMMETRIC_6;
		break;
	case ALGORITHM_PARITY_0:
		new_layout = ALGORITHM_PARITY_0_6;
		break;
	case ALGORITHM_PARITY_N:
		new_layout = ALGORITHM_PARITY_N;
		break;
	default:
		return ERR_PTR(-EINVAL);
	}
	mddev->new_level = 6;
	mddev->new_layout = new_layout;
	mddev->delta_disks = 1;
	mddev->raid_disks += 1;
	return setup_conf(mddev);
}