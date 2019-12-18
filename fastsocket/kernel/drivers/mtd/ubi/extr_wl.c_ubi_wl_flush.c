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
struct ubi_device {scalar_t__ works_count; int /*<<< orphan*/  work_sem; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_wl (char*,scalar_t__) ; 
 int do_work (struct ubi_device*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int ubi_wl_flush(struct ubi_device *ubi)
{
	int err;

	/*
	 * Erase while the pending works queue is not empty, but not more than
	 * the number of currently pending works.
	 */
	dbg_wl("flush (%d pending works)", ubi->works_count);
	while (ubi->works_count) {
		err = do_work(ubi);
		if (err)
			return err;
	}

	/*
	 * Make sure all the works which have been done in parallel are
	 * finished.
	 */
	down_write(&ubi->work_sem);
	up_write(&ubi->work_sem);

	/*
	 * And in case last was the WL worker and it canceled the LEB
	 * movement, flush again.
	 */
	while (ubi->works_count) {
		dbg_wl("flush more (%d pending works)", ubi->works_count);
		err = do_work(ubi);
		if (err)
			return err;
	}

	return 0;
}