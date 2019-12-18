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
typedef  int /*<<< orphan*/  Dwarf_Die ;

/* Variables and functions */
 int E2BIG ; 
 int die_get_typename (int /*<<< orphan*/ *,char*,int) ; 
 char* dwarf_diename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int snprintf (char*,int,char*,...) ; 

int die_get_varname(Dwarf_Die *vr_die, char *buf, int len)
{
	int ret, ret2;

	ret = die_get_typename(vr_die, buf, len);
	if (ret < 0) {
		pr_debug("Failed to get type, make it unknown.\n");
		ret = snprintf(buf, len, "(unknown_type)");
	}
	if (ret > 0) {
		ret2 = snprintf(buf + ret, len - ret, "\t%s",
				dwarf_diename(vr_die));
		ret = (ret2 >= len - ret) ? -E2BIG : ret2 + ret;
	}
	return ret;
}