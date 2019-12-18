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
struct mddev {int layout; int new_level; int new_layout; int delta_disks; int raid_disks; } ;

/* Variables and functions */
 int ALGORITHM_LEFT_ASYMMETRIC ; 
#define  ALGORITHM_LEFT_ASYMMETRIC_6 133 
 int ALGORITHM_LEFT_SYMMETRIC ; 
#define  ALGORITHM_LEFT_SYMMETRIC_6 132 
 int ALGORITHM_PARITY_0 ; 
#define  ALGORITHM_PARITY_0_6 131 
#define  ALGORITHM_PARITY_N 130 
 int ALGORITHM_RIGHT_ASYMMETRIC ; 
#define  ALGORITHM_RIGHT_ASYMMETRIC_6 129 
 int ALGORITHM_RIGHT_SYMMETRIC ; 
#define  ALGORITHM_RIGHT_SYMMETRIC_6 128 
 int /*<<< orphan*/  EINVAL ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* setup_conf (struct mddev*) ; 

__attribute__((used)) static void *raid5_takeover_raid6(struct mddev *mddev)
{
	int new_layout;

	switch (mddev->layout) {
	case ALGORITHM_LEFT_ASYMMETRIC_6:
		new_layout = ALGORITHM_LEFT_ASYMMETRIC;
		break;
	case ALGORITHM_RIGHT_ASYMMETRIC_6:
		new_layout = ALGORITHM_RIGHT_ASYMMETRIC;
		break;
	case ALGORITHM_LEFT_SYMMETRIC_6:
		new_layout = ALGORITHM_LEFT_SYMMETRIC;
		break;
	case ALGORITHM_RIGHT_SYMMETRIC_6:
		new_layout = ALGORITHM_RIGHT_SYMMETRIC;
		break;
	case ALGORITHM_PARITY_0_6:
		new_layout = ALGORITHM_PARITY_0;
		break;
	case ALGORITHM_PARITY_N:
		new_layout = ALGORITHM_PARITY_N;
		break;
	default:
		return ERR_PTR(-EINVAL);
	}
	mddev->new_level = 5;
	mddev->new_layout = new_layout;
	mddev->delta_disks = -1;
	mddev->raid_disks -= 1;
	return setup_conf(mddev);
}