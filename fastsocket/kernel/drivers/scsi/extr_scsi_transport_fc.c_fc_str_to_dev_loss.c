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
 int EINVAL ; 
 unsigned long UINT_MAX ; 
 unsigned long simple_strtoul (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fc_str_to_dev_loss(const char *buf, unsigned long *val)
{
	char *cp;

	*val = simple_strtoul(buf, &cp, 0);
	if ((*cp && (*cp != '\n')) || (*val < 0))
		return -EINVAL;
	/*
	 * Check for overflow; dev_loss_tmo is u32
	 */
	if (*val > UINT_MAX)
		return -EINVAL;

	return 0;
}