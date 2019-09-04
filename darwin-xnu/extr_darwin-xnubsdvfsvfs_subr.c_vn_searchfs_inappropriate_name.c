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
typedef  int /*<<< orphan*/  bad_names ;

/* Variables and functions */
 scalar_t__ strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,scalar_t__) ; 

int vn_searchfs_inappropriate_name(const char *name, int len) {
	const char *bad_names[] = { "System" };
	int   bad_len[]   = { 6 };
	int  i;

	for(i=0; i < (int) (sizeof(bad_names) / sizeof(bad_names[0])); i++) {
		if (len == bad_len[i] && strncmp(name, bad_names[i], strlen(bad_names[i]) + 1) == 0) {
			return 1;
		}
	}

	// if we get here, no name matched
	return 0;
}