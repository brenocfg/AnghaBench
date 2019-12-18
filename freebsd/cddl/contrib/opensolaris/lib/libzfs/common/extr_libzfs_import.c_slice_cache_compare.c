#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* rn_name; } ;
typedef  TYPE_1__ rdsk_node_t ;

/* Variables and functions */
 int strcmp (char const*,char const*) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static int
slice_cache_compare(const void *arg1, const void *arg2)
{
	const char  *nm1 = ((rdsk_node_t *)arg1)->rn_name;
	const char  *nm2 = ((rdsk_node_t *)arg2)->rn_name;
	char *nm1slice, *nm2slice;
	int rv;

	/*
	 * slices zero and two are the most likely to provide results,
	 * so put those first
	 */
	nm1slice = strstr(nm1, "s0");
	nm2slice = strstr(nm2, "s0");
	if (nm1slice && !nm2slice) {
		return (-1);
	}
	if (!nm1slice && nm2slice) {
		return (1);
	}
	nm1slice = strstr(nm1, "s2");
	nm2slice = strstr(nm2, "s2");
	if (nm1slice && !nm2slice) {
		return (-1);
	}
	if (!nm1slice && nm2slice) {
		return (1);
	}

	rv = strcmp(nm1, nm2);
	if (rv == 0)
		return (0);
	return (rv > 0 ? 1 : -1);
}