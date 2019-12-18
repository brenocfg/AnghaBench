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
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  dt_version_t ;

/* Variables and functions */
 scalar_t__ DT_VERSION_MAJOR (int /*<<< orphan*/ ) ; 
 scalar_t__ DT_VERSION_MICRO (int /*<<< orphan*/ ) ; 
 scalar_t__ DT_VERSION_MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,scalar_t__,scalar_t__,...) ; 

char *
dt_version_num2str(dt_version_t v, char *buf, size_t len)
{
	uint_t M = DT_VERSION_MAJOR(v);
	uint_t m = DT_VERSION_MINOR(v);
	uint_t u = DT_VERSION_MICRO(v);

	if (u == 0)
		(void) snprintf(buf, len, "%u.%u", M, m);
	else
		(void) snprintf(buf, len, "%u.%u.%u", M, m, u);

	return (buf);
}