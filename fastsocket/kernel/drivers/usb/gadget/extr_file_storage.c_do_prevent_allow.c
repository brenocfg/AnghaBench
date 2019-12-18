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
struct lun {int prevent_medium_removal; int /*<<< orphan*/  sense_data; } ;
struct fsg_dev {int* cmnd; struct lun* curlun; } ;
struct TYPE_2__ {int /*<<< orphan*/  removable; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SS_INVALID_COMMAND ; 
 int /*<<< orphan*/  SS_INVALID_FIELD_IN_CDB ; 
 int /*<<< orphan*/  fsync_sub (struct lun*) ; 
 TYPE_1__ mod_data ; 

__attribute__((used)) static int do_prevent_allow(struct fsg_dev *fsg)
{
	struct lun	*curlun = fsg->curlun;
	int		prevent;

	if (!mod_data.removable) {
		curlun->sense_data = SS_INVALID_COMMAND;
		return -EINVAL;
	}

	prevent = fsg->cmnd[4] & 0x01;
	if ((fsg->cmnd[4] & ~0x01) != 0) {		// Mask away Prevent
		curlun->sense_data = SS_INVALID_FIELD_IN_CDB;
		return -EINVAL;
	}

	if (curlun->prevent_medium_removal && !prevent)
		fsync_sub(curlun);
	curlun->prevent_medium_removal = prevent;
	return 0;
}