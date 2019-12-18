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
struct option {int /*<<< orphan*/  long_name; int /*<<< orphan*/  short_name; } ;

/* Variables and functions */
 int OPT_SHORT ; 
 int OPT_UNSET ; 
 int error (char*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int opterror(const struct option *opt, const char *reason, int flags)
{
	if (flags & OPT_SHORT)
		return error("switch `%c' %s", opt->short_name, reason);
	if (flags & OPT_UNSET)
		return error("option `no-%s' %s", opt->long_name, reason);
	return error("option `%s' %s", opt->long_name, reason);
}