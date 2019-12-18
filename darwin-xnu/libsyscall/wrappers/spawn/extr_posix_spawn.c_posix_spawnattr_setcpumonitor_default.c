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
typedef  int /*<<< orphan*/  posix_spawnattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_POLICY_CPUMON_DEFAULTS ; 
 int posix_spawnattr_setcpumonitor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
posix_spawnattr_setcpumonitor_default(posix_spawnattr_t * __restrict attr)
{
	return (posix_spawnattr_setcpumonitor(attr, PROC_POLICY_CPUMON_DEFAULTS, 0));
}