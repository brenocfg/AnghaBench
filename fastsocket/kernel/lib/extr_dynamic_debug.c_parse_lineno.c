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
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 unsigned int simple_strtoul (char const*,char**,int) ; 

__attribute__((used)) static inline int parse_lineno(const char *str, unsigned int *val)
{
	char *end = NULL;
	BUG_ON(str == NULL);
	if (*str == '\0') {
		*val = 0;
		return 0;
	}
	*val = simple_strtoul(str, &end, 10);
	return end == NULL || end == str || *end != '\0' ? -EINVAL : 0;
}