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
 int PATH_MAX ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,char const*,char*) ; 
 int system (char*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int run_dir(const char *d, const char *perf)
{
	char cmd[3*PATH_MAX];

	snprintf(cmd, 3*PATH_MAX, "python %s/attr.py -d %s/attr/ -p %s %s",
		 d, d, perf, verbose ? "-v" : "");

	return system(cmd);
}