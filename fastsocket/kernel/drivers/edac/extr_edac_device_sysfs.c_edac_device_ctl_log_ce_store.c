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
struct edac_device_ctl_info {int log_ce; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 scalar_t__ simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t edac_device_ctl_log_ce_store(struct edac_device_ctl_info
					*ctl_info, const char *data,
					size_t count)
{
	/* if parameter is zero, turn off flag, if non-zero turn on flag */
	ctl_info->log_ce = (simple_strtoul(data, NULL, 0) != 0);

	return count;
}