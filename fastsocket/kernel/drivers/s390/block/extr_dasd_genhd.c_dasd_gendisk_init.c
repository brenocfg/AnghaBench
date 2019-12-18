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

/* Variables and functions */
 int /*<<< orphan*/  DASD_MAJOR ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int register_blkdev (int /*<<< orphan*/ ,char*) ; 

int dasd_gendisk_init(void)
{
	int rc;

	/* Register to static dasd major 94 */
	rc = register_blkdev(DASD_MAJOR, "dasd");
	if (rc != 0) {
		pr_warning("Registering the device driver with major number "
			   "%d failed\n", DASD_MAJOR);
		return rc;
	}
	return 0;
}