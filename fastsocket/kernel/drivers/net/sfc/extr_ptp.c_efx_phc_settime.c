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
struct timespec {int dummy; } ;
struct ptp_clock_info {int dummy; } ;

/* Variables and functions */
 int efx_phc_adjtime (struct ptp_clock_info*,int /*<<< orphan*/ ) ; 
 int efx_phc_gettime (struct ptp_clock_info*,struct timespec*) ; 
 struct timespec timespec_sub (struct timespec const,struct timespec) ; 
 int /*<<< orphan*/  timespec_to_ns (struct timespec*) ; 

__attribute__((used)) static int efx_phc_settime(struct ptp_clock_info *ptp,
			   const struct timespec *e_ts)
{
	/* Get the current NIC time, efx_phc_gettime.
	 * Subtract from the desired time to get the offset
	 * call efx_phc_adjtime with the offset
	 */
	int rc;
	struct timespec time_now;
	struct timespec delta;

	rc = efx_phc_gettime(ptp, &time_now);
	if (rc != 0)
		return rc;

	delta = timespec_sub(*e_ts, time_now);

	rc = efx_phc_adjtime(ptp, timespec_to_ns(&delta));
	if (rc != 0)
		return rc;

	return 0;
}