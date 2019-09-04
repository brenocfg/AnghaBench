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
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

bool doc_tombstone_should_ignore_name(const char *nameptr, int len)
{
	if (len == 0) {
		len = strlen(nameptr);
	}

	if (   strncmp(nameptr, "atmp", 4) == 0
		|| (len > 4 && strncmp(nameptr+len-4, ".bak", 4) == 0)
		|| (len > 4 && strncmp(nameptr+len-4, ".tmp", 4) == 0)) {
		return true;
	}

	return false;
}