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
struct ubi_volume_desc {int mode; struct ubi_volume* vol; } ;
struct ubi_volume {int readers; int writers; int exclusive; TYPE_1__* ubi; int /*<<< orphan*/  vol_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  volumes_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 int UBI_EXCLUSIVE ; 
 int /*<<< orphan*/  dbg_err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_assert (int) ; 

__attribute__((used)) static int get_exclusive(struct ubi_volume_desc *desc)
{
	int users, err;
	struct ubi_volume *vol = desc->vol;

	spin_lock(&vol->ubi->volumes_lock);
	users = vol->readers + vol->writers + vol->exclusive;
	ubi_assert(users > 0);
	if (users > 1) {
		dbg_err("%d users for volume %d", users, vol->vol_id);
		err = -EBUSY;
	} else {
		vol->readers = vol->writers = 0;
		vol->exclusive = 1;
		err = desc->mode;
		desc->mode = UBI_EXCLUSIVE;
	}
	spin_unlock(&vol->ubi->volumes_lock);

	return err;
}