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
struct TYPE_2__ {int bsize; scalar_t__ bshift; scalar_t__ nsec; } ;
struct ub_lun {TYPE_1__ capacity; scalar_t__ changed; scalar_t__ readonly; } ;
struct ub_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ ub_sync_read_cap (struct ub_dev*,struct ub_lun*,TYPE_1__*) ; 
 scalar_t__ ub_sync_tur (struct ub_dev*,struct ub_lun*) ; 

__attribute__((used)) static void ub_revalidate(struct ub_dev *sc, struct ub_lun *lun)
{

	lun->readonly = 0;	/* XXX Query this from the device */

	lun->capacity.nsec = 0;
	lun->capacity.bsize = 512;
	lun->capacity.bshift = 0;

	if (ub_sync_tur(sc, lun) != 0)
		return;			/* Not ready */
	lun->changed = 0;

	if (ub_sync_read_cap(sc, lun, &lun->capacity) != 0) {
		/*
		 * The retry here means something is wrong, either with the
		 * device, with the transport, or with our code.
		 * We keep this because sd.c has retries for capacity.
		 */
		if (ub_sync_read_cap(sc, lun, &lun->capacity) != 0) {
			lun->capacity.nsec = 0;
			lun->capacity.bsize = 512;
			lun->capacity.bshift = 0;
		}
	}
}