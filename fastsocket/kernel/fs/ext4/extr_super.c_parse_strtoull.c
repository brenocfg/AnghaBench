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
 int kstrtoull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  skip_spaces (char const*) ; 

__attribute__((used)) static int parse_strtoull(const char *buf,
		unsigned long long max, unsigned long long *value)
{
	int ret;

	ret = kstrtoull(skip_spaces(buf), 0, value);
	if (!ret && *value > max)
		ret = -EINVAL;
	return ret;
}