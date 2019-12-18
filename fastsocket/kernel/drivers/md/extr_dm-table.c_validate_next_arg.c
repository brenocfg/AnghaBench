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
struct dm_arg_set {unsigned int argc; } ;
struct dm_arg {unsigned int min; unsigned int max; char* error; } ;

/* Variables and functions */
 int EINVAL ; 
 char* dm_shift_arg (struct dm_arg_set*) ; 
 int sscanf (char const*,char*,unsigned int*,char*) ; 

__attribute__((used)) static int validate_next_arg(struct dm_arg *arg, struct dm_arg_set *arg_set,
			     unsigned *value, char **error, unsigned grouped)
{
	const char *arg_str = dm_shift_arg(arg_set);
	char dummy;

	if (!arg_str ||
	    (sscanf(arg_str, "%u%c", value, &dummy) != 1) ||
	    (*value < arg->min) ||
	    (*value > arg->max) ||
	    (grouped && arg_set->argc < *value)) {
		*error = arg->error;
		return -EINVAL;
	}

	return 0;
}