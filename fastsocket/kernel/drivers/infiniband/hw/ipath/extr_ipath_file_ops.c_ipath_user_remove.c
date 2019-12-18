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
struct ipath_devdata {int /*<<< orphan*/  user_dev; int /*<<< orphan*/  user_cdev; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_cdev (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_cleanup () ; 
 int /*<<< orphan*/  user_count ; 
 int /*<<< orphan*/  user_setup ; 
 int /*<<< orphan*/  wildcard_cdev ; 
 int /*<<< orphan*/  wildcard_dev ; 

void ipath_user_remove(struct ipath_devdata *dd)
{
	cleanup_cdev(&dd->user_cdev, &dd->user_dev);

	if (atomic_dec_return(&user_count) == 0) {
		if (atomic_read(&user_setup) == 0)
			goto bail;

		cleanup_cdev(&wildcard_cdev, &wildcard_dev);
		user_cleanup();

		atomic_set(&user_setup, 0);
	}
bail:
	return;
}