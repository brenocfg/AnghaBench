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
struct line {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_ALL ; 
 int /*<<< orphan*/  INIT_ONE ; 
 int setup_one_line (struct line*,int,char*,int /*<<< orphan*/ ,char**) ; 
 int simple_strtoul (char*,char**,int /*<<< orphan*/ ) ; 

int line_setup(struct line *lines, unsigned int num, char *init,
	       char **error_out)
{
	int i, n, err;
	char *end;

	if (*init == '=') {
		/*
		 * We said con=/ssl= instead of con#=, so we are configuring all
		 * consoles at once.
		 */
		n = -1;
	}
	else {
		n = simple_strtoul(init, &end, 0);
		if (*end != '=') {
			*error_out = "Couldn't parse device number";
			return -EINVAL;
		}
		init = end;
	}
	init++;

	if (n >= (signed int) num) {
		*error_out = "Device number out of range";
		return -EINVAL;
	}
	else if (n >= 0) {
		err = setup_one_line(lines, n, init, INIT_ONE, error_out);
		if (err)
			return err;
	}
	else {
		for(i = 0; i < num; i++) {
			err = setup_one_line(lines, i, init, INIT_ALL,
					     error_out);
			if (err)
				return err;
		}
	}
	return n == -1 ? num : n;
}