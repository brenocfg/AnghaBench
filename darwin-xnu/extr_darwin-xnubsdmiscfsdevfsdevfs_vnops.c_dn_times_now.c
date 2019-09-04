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
typedef  int /*<<< orphan*/  uint32_t ;
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  devnode_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEVFS_ATTR_LOCK_SPIN () ; 
 int /*<<< orphan*/  DEVFS_ATTR_UNLOCK () ; 
 int /*<<< orphan*/  dn_times_locked (int /*<<< orphan*/ *,struct timeval*,struct timeval*,struct timeval*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 

void
dn_times_now(devnode_t * dnp, uint32_t just_changed_flags)
{
	struct timeval now;

	DEVFS_ATTR_LOCK_SPIN();
	microtime(&now);
	dn_times_locked(dnp, &now, &now, &now, just_changed_flags);
	DEVFS_ATTR_UNLOCK();
}