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
struct ipath_devdata {int ipath_unit; int /*<<< orphan*/  user_dev; int /*<<< orphan*/  user_cdev; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int init_cdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipath_dev_err (struct ipath_devdata*,char*,int,...) ; 
 int /*<<< orphan*/  ipath_file_ops ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  user_cleanup () ; 
 int /*<<< orphan*/  user_count ; 
 int user_init () ; 
 int /*<<< orphan*/  user_setup ; 
 int /*<<< orphan*/  wildcard_cdev ; 
 int /*<<< orphan*/  wildcard_dev ; 

int ipath_user_add(struct ipath_devdata *dd)
{
	char name[10];
	int ret;

	if (atomic_inc_return(&user_count) == 1) {
		ret = user_init();
		if (ret < 0) {
			ipath_dev_err(dd, "Unable to set up user support: "
				      "error %d\n", -ret);
			goto bail;
		}
		ret = init_cdev(0, "ipath", &ipath_file_ops, &wildcard_cdev,
				&wildcard_dev);
		if (ret < 0) {
			ipath_dev_err(dd, "Could not create wildcard "
				      "minor: error %d\n", -ret);
			goto bail_user;
		}

		atomic_set(&user_setup, 1);
	}

	snprintf(name, sizeof(name), "ipath%d", dd->ipath_unit);

	ret = init_cdev(dd->ipath_unit + 1, name, &ipath_file_ops,
			&dd->user_cdev, &dd->user_dev);
	if (ret < 0)
		ipath_dev_err(dd, "Could not create user minor %d, %s\n",
			      dd->ipath_unit + 1, name);

	goto bail;

bail_user:
	user_cleanup();
bail:
	return ret;
}