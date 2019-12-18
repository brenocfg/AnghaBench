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
struct fetch_type {char* name; int /*<<< orphan*/ * fetch; } ;
struct fetch_param {void* data; int /*<<< orphan*/  fn; } ;

/* Variables and functions */
 char* DEFAULT_FETCH_TYPE_STR ; 
 int EINVAL ; 
 size_t FETCH_MTD_retval ; 
 size_t FETCH_MTD_stack ; 
 unsigned long PARAM_MAX_STACK ; 
 int /*<<< orphan*/  fetch_stack_address ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strict_strtoul (char*,int,unsigned long*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static int parse_probe_vars(char *arg, const struct fetch_type *t,
			    struct fetch_param *f, bool is_return)
{
	int ret = 0;
	unsigned long param;

	if (strcmp(arg, "retval") == 0) {
		if (is_return)
			f->fn = t->fetch[FETCH_MTD_retval];
		else
			ret = -EINVAL;
	} else if (strncmp(arg, "stack", 5) == 0) {
		if (arg[5] == '\0') {
			if (strcmp(t->name, DEFAULT_FETCH_TYPE_STR) == 0)
				f->fn = fetch_stack_address;
			else
				ret = -EINVAL;
		} else if (isdigit(arg[5])) {
			ret = strict_strtoul(arg + 5, 10, &param);
			if (ret || param > PARAM_MAX_STACK)
				ret = -EINVAL;
			else {
				f->fn = t->fetch[FETCH_MTD_stack];
				f->data = (void *)param;
			}
		} else
			ret = -EINVAL;
	} else
		ret = -EINVAL;
	return ret;
}