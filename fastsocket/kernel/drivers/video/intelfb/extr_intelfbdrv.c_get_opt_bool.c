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
 scalar_t__ OPT_EQUAL (char const*,char const*) ; 
 int simple_strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static __inline__ int get_opt_bool(const char *this_opt, const char *name,
				   int *ret)
{
	if (!ret)
		return 0;

	if (OPT_EQUAL(this_opt, name)) {
		if (this_opt[strlen(name)] == '=')
			*ret = simple_strtoul(this_opt + strlen(name) + 1,
					      NULL, 0);
		else
			*ret = 1;
	} else {
		if (OPT_EQUAL(this_opt, "no") && OPT_EQUAL(this_opt + 2, name))
			*ret = 0;
		else
			return 0;
	}
	return 1;
}