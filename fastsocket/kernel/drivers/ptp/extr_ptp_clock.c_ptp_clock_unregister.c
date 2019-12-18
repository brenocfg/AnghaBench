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
struct ptp_clock {int defunct; int /*<<< orphan*/  clock; int /*<<< orphan*/  devid; scalar_t__ pps_source; int /*<<< orphan*/  tsev_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  posix_clock_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pps_unregister_source (scalar_t__) ; 
 int /*<<< orphan*/  ptp_class ; 
 int /*<<< orphan*/  ptp_cleanup_sysfs (struct ptp_clock*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

int ptp_clock_unregister(struct ptp_clock *ptp)
{
	ptp->defunct = 1;
	wake_up_interruptible(&ptp->tsev_wq);

	/* Release the clock's resources. */
	if (ptp->pps_source)
		pps_unregister_source(ptp->pps_source);
	ptp_cleanup_sysfs(ptp);
	device_destroy(ptp_class, ptp->devid);

	posix_clock_unregister(&ptp->clock);
	return 0;
}