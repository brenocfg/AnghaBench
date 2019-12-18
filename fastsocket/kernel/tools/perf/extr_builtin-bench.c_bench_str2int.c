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
 int BENCH_FORMAT_DEFAULT ; 
 int /*<<< orphan*/  BENCH_FORMAT_DEFAULT_STR ; 
 int BENCH_FORMAT_SIMPLE ; 
 int /*<<< orphan*/  BENCH_FORMAT_SIMPLE_STR ; 
 int BENCH_FORMAT_UNKNOWN ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bench_str2int(const char *str)
{
	if (!str)
		return BENCH_FORMAT_DEFAULT;

	if (!strcmp(str, BENCH_FORMAT_DEFAULT_STR))
		return BENCH_FORMAT_DEFAULT;
	else if (!strcmp(str, BENCH_FORMAT_SIMPLE_STR))
		return BENCH_FORMAT_SIMPLE;

	return BENCH_FORMAT_UNKNOWN;
}