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
 unsigned long long PAGE_ALIGN (unsigned long long) ; 
 unsigned long long RESOURCE_MAX ; 
 unsigned long long memparse (char*,char**) ; 
 unsigned long long simple_strtoull (char const*,char**,int) ; 

int res_counter_memparse_write_strategy(const char *buf,
					unsigned long long *res)
{
	char *end;

	/* return RESOURCE_MAX(unlimited) if "-1" is specified */
	if (*buf == '-') {
		*res = simple_strtoull(buf + 1, &end, 10);
		if (*res != 1 || *end != '\0')
			return -EINVAL;
		*res = RESOURCE_MAX;
		return 0;
	}

	/* FIXME - make memparse() take const char* args */
	*res = memparse((char *)buf, &end);
	if (*end != '\0')
		return -EINVAL;

	*res = PAGE_ALIGN(*res);
	return 0;
}