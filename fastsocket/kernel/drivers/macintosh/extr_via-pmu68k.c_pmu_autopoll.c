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
struct adb_request {int /*<<< orphan*/  complete; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  PMU_ADB_CMD ; 
 int /*<<< orphan*/  PMU_ADB_POLL_OFF ; 
 int adb_dev_map ; 
 int pmu_adb_flags ; 
 int /*<<< orphan*/  pmu_fully_inited ; 
 int /*<<< orphan*/  pmu_poll () ; 
 int /*<<< orphan*/  pmu_request (struct adb_request*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int 
pmu_autopoll(int devs)
{
	struct adb_request req;

	if (!pmu_fully_inited) return -ENXIO;

	if (devs) {
		adb_dev_map = devs;
		pmu_request(&req, NULL, 5, PMU_ADB_CMD, 0, 0x86,
			    adb_dev_map >> 8, adb_dev_map);
		pmu_adb_flags = 2;
	} else {
		pmu_request(&req, NULL, 1, PMU_ADB_POLL_OFF);
		pmu_adb_flags = 0;
	}
	while (!req.complete)
		pmu_poll();
	return 0;
}