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
 int /*<<< orphan*/  prefixcmp (char const*,char*) ; 
 char const* prepend (char*,char const*) ; 

__attribute__((used)) static const char *cmd_to_page(const char *perf_cmd)
{
	if (!perf_cmd)
		return "perf";
	else if (!prefixcmp(perf_cmd, "perf"))
		return perf_cmd;
	else
		return prepend("perf-", perf_cmd);
}