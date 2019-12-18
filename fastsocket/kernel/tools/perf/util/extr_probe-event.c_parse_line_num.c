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
 scalar_t__ errno ; 
 int /*<<< orphan*/  semantic_error (char*,char const*) ; 
 int strtol (char*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_line_num(char **ptr, int *val, const char *what)
{
	const char *start = *ptr;

	errno = 0;
	*val = strtol(*ptr, ptr, 0);
	if (errno || *ptr == start) {
		semantic_error("'%s' is not a valid number.\n", what);
		return -EINVAL;
	}
	return 0;
}