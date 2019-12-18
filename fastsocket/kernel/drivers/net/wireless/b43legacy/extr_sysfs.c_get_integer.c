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
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t min (size_t,size_t) ; 
 int simple_strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int get_integer(const char *buf, size_t count)
{
	char tmp[10 + 1] = { 0 };
	int ret = -EINVAL;

	if (count == 0)
		goto out;
	count = min(count, (size_t)10);
	memcpy(tmp, buf, count);
	ret = simple_strtol(tmp, NULL, 10);
out:
	return ret;
}